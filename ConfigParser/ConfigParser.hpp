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
        static void trim(string& s);
        static void split(const string& str, const char* delim, vector<string>& vec);
        CONFIG read(const string& filepath);
    private:
};

ostream& operator << (ostream& out, const map<string, string>& smap);
ostream& operator << (ostream& out, const CONFIG& config);

#endif  /*_CONFIGPARSER_HPP_*/
