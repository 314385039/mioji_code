#include "ThreadPool.h"

using namespace std;

//指定队列大小和线程池大小
ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
    :m_isStarted(false),
     m_poolSize(poolSize),
     m_queueSize(queueSize),
     m_spaceExist(m_mutex),
     m_taskExist(m_mutex)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::start()
{
    if (m_isStarted)
        return;
    m_isStarted = true;
    //开启线程
    for (size_t i = 0; i != m_poolSize; ++i)
    {
        m_threads.push_back(std::unique_ptr<Thread>(new Thread(bind(&ThreadPool::runInThread, this))));
    }
    for (size_t i = 0; i != m_poolSize; ++i)
    {
        m_threads[i]->start();
    }

}

void ThreadPool::runInThread()
{
    //当线程池关闭时，这个县城可以自动退出
    while (m_isStarted)
    {
        Task task(getTask());
        if (task)
        {
            task();     //执行真正的任务
        }
    }
}

void ThreadPool::addTask(const Task& task)
{
    //定义一个自动锁，锁住队列锁
    MutexLockGuard lock(m_mutex);

    //这里如果队列满了，主线程会阻塞
    while (m_queue.size() >= m_queueSize)   //如果队列满了，生产者等待
        m_spaceExist.wait();

    m_queue.push(task);
    m_taskExist.notify();     //每生产一个任务，就通知消费者有任务了
}

ThreadPool::Task ThreadPool::getTask()
{
    MutexLockGuard lock(m_mutex);
    //如果队列为空而且线程池开启，此处线程便会阻塞
    //注意这里的线程逻辑，这里的m_taskExist条件变量在等待的时候。如果被信号激活，有两种情况：
    //一种是抢到锁，正常运行，一种是没有抢到锁阻塞，如果没有抢到锁遇到阻塞情况，等到它抢到锁的时候，有可能线程池已经关闭了或者虽然得到了锁，但是队列里面已经没有任务了，如果是这两种情况，继续往后进行就会出错，所以这里用while循环，即使抢到了锁，也还要判断队列是否有任务，线程池是否开启，如果开启，while直接过去，如果不满足要求，while继续执行wait又一次的释放锁，阻塞等待
    //如果有线程在等待，那么队列一定为空！所以如果此时stop，队列肯定空,此时会不会出现在stop的瞬间加入任务的情况呢？不会！因为stop和addtask都是人为控制的。如果队列里面有数据，那么stop之后，线程执行完当前任务就会去再次判断线程池是否开启，如果关闭，线程就退出了，不会去继续拿任务，此时stop也会清空queue
    while (m_queue.empty() && m_isStarted)
        m_taskExist.wait();

    Task task;
    if (!m_queue.empty())
    {
        task = m_queue.front();
        m_queue.pop();
        m_spaceExist.notify();     //每次拿出一个任务，就通知生产者有空位了
    }

    return task;
}

void ThreadPool::stop()
{
    if (m_isStarted == false)
        return ;

    {
        MutexLockGuard lock(m_mutex);
        m_isStarted = false;
        m_taskExist.notifyALL();
    }

    //等待所有线程结束
    for (size_t i = 0; i != m_poolSize; ++i)
    {
        m_threads[i]->join();    
    }

    while (!m_queue.empty())
    {
        m_queue.pop();
    }

    m_threads.clear();
}








