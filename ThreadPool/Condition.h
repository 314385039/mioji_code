#ifndef _CONDITION_H_
#define _CONDITION_H_ 

#include <pthread.h>
#include "NonCopyable.h"

class MutexLock;

class Condition : NonCopyable
{
    public:
        Condition(MutexLock &mutex);
        ~Condition();

        void wait();
        void notify();
        void notifyALL();
    private:
        pthread_cond_t  m_cond;
        MutexLock& m_mutex;
};

#endif  /*_CONDITION_H_*/
