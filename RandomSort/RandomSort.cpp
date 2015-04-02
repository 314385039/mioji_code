#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

bool cmp(int a, int b)
{
    struct timeval start;
    gettimeofday(&start, NULL);
    srand(start.tv_usec);
    int i = rand();
    //cout << i << endl;
    return i%2;
}

void printvec(const vector<int>& vec)
{
    for (int i = 0; i != vec.size(); ++i)
    {
        cout << vec[i] << " ";
    }
}

int main(int argc, const char *argv[])
{
    vector<int> vec;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(i);
    }
    printvec(vec);
    sort(vec.begin(), vec.end(), cmp);
    cout << "-------------------------------" << endl;
    printvec(vec);

    return 0;
}



