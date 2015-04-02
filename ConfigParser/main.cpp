#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    ConfigParser config;
    CONFIG result = config.read("conf.ini");
    
    //测试read
    cout << result["ssasasa"]["ddd"] << "hello" << endl;
    cout << "result[sad] = " << result["sad"] << endl;
    cout << "result[basic][num] = " << result["basic"]["num"] << endl;
    cout << "result[basic] = " << result["basic"] << endl;;
    cout << "result = " << result << endl;

    //测试split
    vector<string> vec;
    cout << result["basic"]["users"] << endl;
    string a = " " ;
    ConfigParser::split(result["basic"]["usrs"], a , vec);
    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    
    //测试write
    config.write(result, "output.ini");

    return 0;
}
