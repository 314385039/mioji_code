#include <iostream>
#include <string>
#include <vector>
#include "MyRedis.h"

using namespace std;

int main(int argc, const char *argv[])
{
    MyRedis* mr = new MyRedis();
    string res;

    mr->set("name", "liuyuan");
    mr->get("name", res);
    mr->get("1", res);
    cout << res << endl;
    mr->get("2", res);
    cout << res << endl;
    mr->get("3", res);
    cout << res << endl;

    delete mr;
    
    return 0;
}
