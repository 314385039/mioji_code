#include "Condition.h"
#include "MutexLock.h"

Condition::Condition(MutexLock& mutex)
    :m_mutex(mutex)
{
    pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition()
{
    pthread_cond_destroy(&m_cond);
}

void Condition::wait()
{
    //wait前必须lock
    //注意：这里的assert存在bug，不能添加这句话,当频繁切换线程的时候这里存在问题
    //assert(m_mutex.isLocked());
    pthread_cond_wait(&m_cond, m_mutex.getMutexPtr());
}

void Condition::notify()
{
    pthread_cond_signal(&m_cond);
}

void Condition::notifyALL()
{
    pthread_cond_broadcast(&m_cond);
}
