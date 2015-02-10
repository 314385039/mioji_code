#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_ 

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class MutexLock : NonCopyable
{
    friend class MutexLockGuard;
    public:
        MutexLock();
        ~MutexLock();

        pthread_mutex_t* getMutexPtr() { return &m_mutex; }
        bool isLocked() const { return m_isLocked; }
    private:
        //定义为私有，防止收工调用,只允许下面的自动锁类来调用
        void lock();
        void unlock();
    private:
        pthread_mutex_t m_mutex;
        bool m_isLocked;
};


inline MutexLock::MutexLock()
    :m_isLocked(false)
{
    pthread_mutex_init(&m_mutex, NULL); 
}

inline MutexLock::~MutexLock()
{
    //确保这里已经解锁
    assert(m_isLocked == false);
    pthread_mutex_destroy(&m_mutex);
}

inline void MutexLock::lock()
{
    pthread_mutex_lock(&m_mutex);
    m_isLocked = true;
}

inline void MutexLock::unlock()
{
    m_isLocked = false;
    pthread_mutex_unlock(&m_mutex);
}

class MutexLockGuard
{
    public:
        MutexLockGuard(MutexLock &mutex);
        ~MutexLockGuard();
    private:
        MutexLock &m_mutex;
};

inline MutexLockGuard::MutexLockGuard(MutexLock& mutex)
    :m_mutex(mutex)
{
    m_mutex.lock(); 
}

inline MutexLockGuard::~MutexLockGuard()
{
    m_mutex.unlock();
}

//MutexLockGuard(m_mutex);
//帮助在编译期间发现错误
#define MutexLockGuard(m) "ERROR"

#endif  /*_MUTEXLOCK_H_*/



