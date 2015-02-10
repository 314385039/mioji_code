#include "Thread.h"
#include <assert.h>

Thread::Thread()
    :m_tid(0),
     m_isStarted(false)
{
}

Thread::Thread(const ThreadFunc& callback)
    :m_tid(0),
     m_isStarted(false),
     m_callback(callback)
{
}

Thread::~Thread()
{
    //这里是为了保证线程安全，如果没有join，线程仍然开启，就自行回收资源
    if (m_isStarted)
        pthread_detach(m_tid);
}

void Thread::start()
{
    pthread_create(&m_tid, NULL, threadFunc, this);
}

void* Thread::threadFunc(void* arg)
{
    Thread* pt = static_cast<Thread*>(arg);
    assert(pt->m_callback);
    pt->m_callback();   //调用线程逻辑

    return NULL;
}

void Thread::join()
{
    pthread_join(m_tid, NULL);
}
