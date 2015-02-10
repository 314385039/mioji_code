#ifndef _CONFIGPARSER_HPP_
#define _CONFIGPARSER_HPP_ 
//liuyuan
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef map< string, map<string, string> > CONFIGRES;

class ConfigParser
{
    //friend ostream& operator << (ostream& out, const CONFIGRES& config);
    public:
        ConfigParser();
        ~ConfigParser();
        static ifstream& openfileRead(ifstream& is, const string& filename);
        static ofstream& openfileWrite(ofstream& os, const string& filename);
        //去掉字符串首位空白符
        static void trim(string& s);
        //切割字符串
        static void split(const string& str, const string& delim, vector<string>& vec);

        CONFIGRES read(const string& filepath);
    private:
};

//重载输出操作符
ostream& operator << (ostream& out, const map<string, string>& smap);
ostream& operator << (ostream& out, const CONFIGRES& config);

#endif  /*_CONFIGPARSER_HPP_*/
