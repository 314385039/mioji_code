#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include "json/json.h"

using namespace std;

int main(void)
{
    std::string strValue = "{\"key1\":\"value1\",\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}";
    cout << "string is " << strValue << endl;

    //reader反序列化json对象
    Json::Reader reader;
    Json::Value value;

    //将json字符串strvalue反序列化，保存到json对象中
    if (reader.parse(strValue, value))
    {
        //成员值用asString()函数可转化成字符串
        std::string out = value["key1"].asString();
        std::cout << out << std::endl;
        //value对象也能接受数组格式
        const Json::Value arrayObj = value["array"];
        for (int i=0; i<arrayObj.size(); i++)
        {
            out = arrayObj[i]["key2"].asString();
            std::cout << out;
            std::cout << std::endl;
        }
    }

    cout << "===================================" << endl;

    //构建json对象
    Json::Value value1, value2, value3;
    value1["name1"] = "liuyuan";
    value1["age1"] = 25;
    //size(),获取大小
    cout << value1.size() << endl;
    value2["name2"] = "zhangyang";
    value2["age2"] = 28;
    //value既可以下标操作成为map也可以append操作成为vector
    value3.append(value1);
    value3.append(value2);
    cout << value3[0]["name1"].asString() << endl;
    //注意这里int类型可以asString,但是string类型不能asInt
    cout << value3[0]["age1"].asString() << endl;
    cout << value3[0]["age1"].asInt() << endl;
    //这里错误，已经变为array的value不能再变成map
    //value3["3"] = "ddd";

    //支持类似python的各种形式之间的来回赋值
    value2["hello"] = value3;
    cout << "value2 = " << value2.toStyledString() << endl;
    value1 = value2["hello"];
    cout << "value1" << value1.toStyledString() << endl;

    cout << "===================================" << endl;
    
    //序列化JSON
    //格式序列化整个json对象
    cout << value3.toStyledString() << endl;
    //格式序列化json对象(结果同上)
    Json::StyledWriter jsw;
    cout << jsw.write(value3) << endl;
    //快速序列化整个json对象
    Json::FastWriter jfw;
    cout << jfw.write(value3) << endl;
    //格式序列化到流对象中 
    Json::StyledStreamWriter jssw;
    jssw.write(cout, value3);
    

    
    return 0;
}













