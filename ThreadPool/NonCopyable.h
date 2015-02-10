#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_ 

class NonCopyable
{
    public:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable&);
        void operator=(const NonCopyable&);
};

#endif  /*_NONCOPYABLE_H_*/
