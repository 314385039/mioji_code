#ifndef __MY_REDIS_H__
#define __MY_REDIS_H__

#include <vector>
#include <string>
#include <hiredis/hiredis.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


class MyRedis{
public:
	MyRedis(const std::string& addr = "127.0.0.1:6379");
	~MyRedis();
	bool setAddr(const std::string& addr);
	bool get(const std::string& key,std::string& val);		//get
	bool mget(const std::vector<std::string>& keys,std::vector<std::string>& vals);		//mget
	bool set(const std::string& key,const std::string& val);
    bool setex(const std::string& key, int timeout, const std::string& val);
private:
	redisReply* doCMD(const char* key);
	bool reConnect();
private:
	redisContext* m_redis_cnn;
	std::string m_ip;
	int m_port;
	pthread_mutex_t m_mutex_locker;
};




#endif	//__MY_REDIS_H__
