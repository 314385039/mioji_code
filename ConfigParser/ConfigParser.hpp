#ifndef _CONFIGPARSER_HPP_
#define _CONFIGPARSER_HPP_ 
//liuyuan
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef map< string, map<string, string> > CONFIG;

class ConfigParser
{
    //friend ostream& operator << (ostream& out, const CONFIG& config);
    public:
        ConfigParser();
        ~ConfigParser();
        static ifstream& openfileRead(ifstream& is, const string& filename);
        static ofstream& openfileWrite(ofstream& os, const string& filename);
        //去掉字符串首位空白符
        static void trim(string& s);
        //切割字符串
        static void split(const string& str, const string& delim, vector<string>& vec);

        //读取标准格式配置文件，返回值为map<string, map<string, string> >
        CONFIG read(const string& filepath);
        //传入一个CONFIG格式的数据，写入文件filename中，如果写入成功返回true
        bool write(const CONFIG& content, const string& filepath);
    private:
};

//重载输出操作符
ostream& operator << (ostream& out, const map<string, string>& smap);
ostream& operator << (ostream& out, const CONFIG& config);

#endif  /*_CONFIGPARSER_HPP_*/
