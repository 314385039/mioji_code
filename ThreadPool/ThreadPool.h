#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_ 

#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"
#include <vector>
#include <functional>
#include <memory>
#include <queue>

class Thread;

class ThreadPool : private NonCopyable
{
    public:
        typedef std::function<void ()> Task;

        ThreadPool(size_t queueSize, size_t poolSize);
        ~ThreadPool();

        void start();   //开启线程池
        void stop();    //关闭线程池
        
        void addTask(const Task& task);     //手动添加任务
    private:
        Task getTask();
        void runInThread();

    private:
        bool m_isStarted;
        std::vector< std::unique_ptr<Thread> > m_threads;
        size_t m_queueSize; //队列大小
        size_t m_poolSize;  //线程池大笑
        std::queue<Task> m_queue;   //任务队列
        mutable MutexLock m_mutex;  //队列锁
        Condition m_spaceExist;
        Condition m_taskExist;
};

#endif  /*_THREADPOOL_H_*/
