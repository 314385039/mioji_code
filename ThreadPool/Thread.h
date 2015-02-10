#ifndef _THREAD_H_
#define _THREAD_H_ 

#include "NonCopyable.h"
#include <functional>
#include <pthread.h>

class Thread : private NonCopyable
{
    public:
        typedef std::function<void ()> ThreadFunc;

        Thread();
        explicit Thread(const ThreadFunc& callback);
        ~Thread();

        void start();
        void join();
    private:
        static void* threadFunc(void*);

        pthread_t m_tid;
        bool m_isStarted;
        ThreadFunc m_callback;
};

#endif  /*_THREAD_H_*/
