#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    /*
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

    //测试read_mod2
    cout << "--------------------------" << endl;
    vector<string> vstr = config.read_mod2("conf.ini");
    cout << vstr;

    //测试write
    config.write(vstr, "output.ini");
    */

    vector<string> vec;
    ConfigParser::split("1|PEK|20155555|2", "|", vec);
    for (int i = 0; i != vec.size(); ++i)
    {
        cout << "wa" << vec[i] << endl;
    }
    
    return 0;
}
