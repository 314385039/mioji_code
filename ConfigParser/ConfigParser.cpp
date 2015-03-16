#include "ConfigParser.hpp"

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

ifstream& ConfigParser::openfileRead(ifstream& is, const string& filename)
{
    is.close();
    is.clear();
    is.open(filename.c_str());

    return is;
}

ofstream& ConfigParser::openfileWrite(ofstream& os, const string& filename)
{
    os.close();
    os.clear();
    os.open(filename.c_str(), ofstream::out);
    return os;
}

//去掉字符串首尾空格
void ConfigParser::trim(string& s)
{
    if (s.empty())
        return;
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    return;
}

//以delim分割字符串str，分割好的结果保存到vec中去
void ConfigParser::split(const string& str, const string& delim, vector<string>& vec)
{
    int beg = 0, end;
    do
    {
        string word = "";
        end = str.find(delim, beg);
        if (end == -1)
        {
            word = str.substr(beg); 
        }
        else
        {
            word = str.substr(beg, end - beg);
        }
        vec.push_back(word);
        beg = end + 1;
        if (beg == str.size() || beg == 0)
            break;
    }while (1);
}


CONFIGRES ConfigParser::read(const string& filepath)
{
    CONFIGRES results;
    ifstream is; 
    if (!openfileRead(is, filepath)) 
    {
        cout << "open configFile " << filepath << " failed!" << endl;
        return results;
    }
    string line = "";
    string cur_key = "";    //标记当前key
    while (getline(is, line))
    {
        trim(line);  //去掉首尾空格
        if (line[0] == '[')
        {
            //添加key
            int beg = 1, end = 0;
            if ((end = line.find(']')) != -1)
            {
                cur_key = line.substr(beg, end - beg);
                map<string, string> temp_value;
                results[cur_key] = temp_value;
            }
            else
            {
                continue;    //此行不符合格式要求，直接跳过
            }
        }
        else if (line.find('=') != -1 && cur_key != "")
        {
            string key = line.substr(0, line.find('='));
            trim(key);
            string value = line.substr(line.find('=') + 1);
            trim(value);
            if (key == "")
                continue;
            results[cur_key][key] = value;
        }
        else        //不符合要求的行，直接跳过
        {
            continue;
        }
    }

    return results;
}


ostream& operator << (ostream& out, const map<string, string>& smap)
{
    string str = "{";
    if (smap.size() >= 1)
    {
        for (map<string, string>::const_iterator mit = smap.begin(); mit != smap.end(); ++mit)
        {
            str += mit->first + ":" + mit->second + ",";
        }
        str.erase(str.find_last_of(","), 1);
    }
    str += "}";

    out << str;
    return out;
}

ostream& operator << (ostream& out, const CONFIGRES& config)
{
    out << "{";
    if (config.size() >= 1)
    {
        for (CONFIGRES::const_iterator cit = config.begin(); cit != config.end(); ++ cit)
        {
            out << cit->first << ":" << (cit->second) << ",";
        }
        out << "\b";
    }
    out << "}";

    return out;
}














