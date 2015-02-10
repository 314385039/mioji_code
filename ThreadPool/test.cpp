#include "ThreadPool.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#include <functional>

#define POOLSIZE 10
#define QUEUESIZE 10 

using namespace std;

void fuc(int i)
{
    cout << i << endl;
    sleep(1);
}

int main(int argc, const char *argv[])
{
    ThreadPool tp(QUEUESIZE, POOLSIZE);
    tp.start(); 
    sleep(3);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i != 10; ++i)
    {
        function<void ()> task = bind(fuc, i);
        tp.addTask(task);
    }
    tp.stop();
    gettimeofday(&end, NULL);
    
    int delttime = (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
    cout << "添加任务结束" << endl;
    cout << "一共耗时" << delttime << "us" << endl;

    getchar();
    return 0;
}
