#include "MyRedis.h"
#include <iostream>
#include <sstream>

using namespace std;

MyRedis::MyRedis(const string& addr){
    if (!setAddr(addr))
    {
        cerr << "[ERROR]:MyRedis::MyRedis() init error!" << endl;
    }
}

MyRedis::~MyRedis(){
    if (m_redis_cnn){
        redisFree(m_redis_cnn);
        m_redis_cnn = NULL;
    }
}

bool MyRedis::setAddr(const std::string& addr){
    int pos;
    if ((pos = addr.find(":")) == std::string::npos){
        cerr<<"[ERROR]:MyRedis::setAddr() error addr->"<<addr<<endl;
        return false;
    }
    //cout << addr << endl;
    //cout << pos << endl;
    m_ip = addr.substr(0,pos);
    m_port = atoi(addr.substr(pos+1).c_str());
    return reConnect();
}

bool MyRedis::reConnect(){
    //cerr<<"Connecting MyRedis"<<endl;
    if (m_redis_cnn){
        redisFree(m_redis_cnn);
        m_redis_cnn = NULL;
    }
    m_redis_cnn = redisConnect(m_ip.c_str(), m_port);
    if (m_redis_cnn==NULL){
        cerr<<"[ERROR]:Redis Connect return NULL"<<endl;
        return false;
    }
    if (m_redis_cnn->err){
        cerr<<"[ERROR]:Redis Connect failed [" << m_redis_cnn->err << "] [" << m_redis_cnn->errstr << "]"<<endl;
        redisFree(m_redis_cnn);
        return false;
    }
    return true;
}

//liuyuan
bool MyRedis::setex(const std::string& key, int timeout, const std::string& val)
{
    redisReply* r = (redisReply*)redisCommand(m_redis_cnn, "SETEX %s %d %s", key, timeout, val);
    if (r==NULL){
        if (reConnect()){
            r = (redisReply*)redisCommand(m_redis_cnn, "SETEX %s %d %s", key.c_str(), timeout, val.c_str());
        }else{
            cerr<<"[MyRedis::setex] failed->"<<key<<endl;
            pthread_mutex_unlock(&m_mutex_locker);
            return false;
        }
    }
    if (r==NULL){
        cerr<<"[MyRedis::setex] failed->"<<key<<endl;
        pthread_mutex_unlock(&m_mutex_locker);
        return false;
    }
    if(!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)){  
        cerr<<"[MyRedis::setex] failed->"<<key<<endl;
        freeReplyObject(r);
        pthread_mutex_unlock(&m_mutex_locker);
        return false;
    }
    freeReplyObject(r);
    return true;
}

bool MyRedis::set(const std::string& key,const std::string& val){
    redisReply* r = (redisReply*)redisCommand(m_redis_cnn, "SET %s %s", key.c_str(), val.c_str());
    if (r==NULL){
        if (reConnect()){
            r = (redisReply*)redisCommand(m_redis_cnn, "SET %s %s", key.c_str(), val.c_str());
        }else{
            cerr<<"[MyRedis::set] failed->"<<key<<endl;
            pthread_mutex_unlock(&m_mutex_locker);
            return false;
        }
    }
    if (r==NULL){
        cerr<<"[MyRedis::set] failed->"<<key<<endl;
        pthread_mutex_unlock(&m_mutex_locker);
        return false;
    }
    if(!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)){  
        cerr<<"[MyRedis::set] failed->"<<key<<endl;
        freeReplyObject(r);
        pthread_mutex_unlock(&m_mutex_locker);
        return false;
    }
    freeReplyObject(r);
    return true;
}

bool MyRedis::get(const std::string& key,std::string& val){
    val = "";
    if (key.length()==0){
        cerr<<"null key"<<endl;
        return false;
    }
    redisReply* r = (redisReply*)redisCommand(m_redis_cnn, "GET %s", key.c_str());
    if (r==NULL){
        if (reConnect()){
            r = (redisReply*)redisCommand(m_redis_cnn, "GET %s", key.c_str());
        }else{
            cerr<<"[MyRedis::get] failed->"<<key<<endl;
            return false;
        }
    }
    if (r==NULL){
        cerr<<"[MyRedis::get] failed->"<<key<<endl;
        return false;
    }

    if(r->type != REDIS_REPLY_STRING){ 
        if (r->type != REDIS_REPLY_NIL){
            cerr<<"[MyRedis::get] failed->"<<key<<endl;
            freeReplyObject(r);
            return false;
        }else{
            freeReplyObject(r);
            return true;
        }
    }    

    val = r->str;
    freeReplyObject(r);
    return true;
}


bool MyRedis::mget(const std::vector<std::string>& keys, std::vector<std::string>& vals){
    string cmd = "mget";
    vals.clear();
    int i;
    for (i=0;i<keys.size();i++){
        cmd += (" "+keys[i]);
    }

    redisReply* r = (redisReply*)redisCommand(m_redis_cnn, cmd.c_str());
    if (r==NULL){
        if (reConnect()){
            r = (redisReply*)redisCommand(m_redis_cnn, cmd.c_str());
        }else{
            cerr<<"[MyRedis::mget] failed->"<<cmd<<endl;
            return false;
        }
    }
    if (r==NULL){
        cerr<<"[MyRedis::mget] failed->"<<cmd<<endl;
        return false;
    }
    if(r->type != REDIS_REPLY_ARRAY){ 
        cerr<<"[MyRedis::mget] failed->"<<cmd<<endl;
        freeReplyObject(r);
        return false;
    }
    for (i=0;i<r->elements;i++){
        redisReply* childReply = r->element[i];
        if (childReply->type == REDIS_REPLY_STRING){
            vals.push_back(childReply->str);
        }else if (childReply->type == REDIS_REPLY_NIL){
            vals.push_back("");
        }
    }

    freeReplyObject(r);


    if (vals.size()!=keys.size()){
        vals.clear();
        cerr<<"[ERROR]:MyRedis::mget() keys' size not match vals'->"<<cmd<<endl;
    }
    return true;
}






