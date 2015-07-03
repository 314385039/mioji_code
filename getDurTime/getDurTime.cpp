#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

using namespace std;

int main(int argc, const char *argv[])
{
    struct timeval start, end;  //建立保存时间的结构体
    gettimeofday(&start, NULL); //获取当前时间
    sleep(3);
    gettimeofday(&end, NULL);

    //tv_usec单位是秒，tv_usec单位是微秒，这样算出来结果就是毫秒
    int delttime = (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec);
    cout << "总共耗时：" << delttime << endl;
    return 0;
}
