#include "RedisMgr.h"
#include "ConfigMgr.h"



RedisMgr::RedisMgr() {
	auto& gCfgMgr = ConfigMgr::Inst();
	auto host = gCfgMgr["Redis"]["Host"];
	auto port = gCfgMgr["Redis"]["Port"];
	auto pwd = gCfgMgr["Redis"]["Password"];
	_con_pool.reset(new RedisConPool(5, host.c_str(), std::stoi(port.c_str()), pwd.c_str()));
}
RedisMgr::~RedisMgr()
{
	Close();
}
 
//获取key对应的value
bool RedisMgr::Get(const std::string& key, std::string& value)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "GET %s", key.c_str());
	if (_reply == NULL) {
		std::cout << "[ GET " << key << " ] failed" << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	if (_reply->type != REDIS_REPLY_STRING) {
		std::cout << "[ GET " << key << " ] failed" << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	value = _reply->str;
	freeReplyObject(_reply);

	std::cout << "Succeed to execute command [ GET " << key << " ]" << std::endl;
	return true;
}
//设置key和value
bool RedisMgr::Set(const std::string& key, const std::string& value) {
	//执行redis命令行
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "SET %s %s", key.c_str(), value.c_str());

	//如果返回NULL则说明执行失败
	if (NULL == _reply)
	{
		std::cout << "Execut command [ SET " << key << " " << value << " ] failure !" << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	//如果执行失败则释放连接
	if (!(_reply->type == REDIS_REPLY_STATUS && (strcmp(_reply->str, "OK") == 0 || strcmp(_reply->str, "ok") == 0)))
	{
		std::cout << "Execut command [ SET " << key << " " << value << " ] failure !2" << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	//执行成功 释放redisCommand执行后返回的refisReply所占用的内存
	freeReplyObject(_reply);
	std::cout << "Execut command [ SET " << key << " " << value << " ] success ! " << std::endl;
}
//密码认证
bool RedisMgr::Auth(const std::string& password)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "AUTH %s", password.c_str());
	if (_reply->type == REDIS_REPLY_ERROR) {
		std::cout << "认证失败" << std::endl;
		//执行失败 释放redisCommand 执行后返回的redisReply所占的内存
		freeReplyObject(_reply);
		return false;
	}
	else {
		//执行成功 释放redisCommand 执行后返回的redisReply所占用的内存
		freeReplyObject(_reply);
		std::cout << "认证成功" << std::endl;
		return true;
	}
}

//左侧push
bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "LPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == _reply)
	{
		std::cout << "Execut command [ PUSH " << key << " " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
		std::cout << "Execut command [ LPUSH " << key << " " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	std::cout << "Execut command [ LPUSH " << key << " " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//左侧pop
bool RedisMgr::LPop(const std::string& key, std::string& value) {
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "LPop %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ LPOP " << key << " ] success !" << std::endl;
	freeReplyObject(_reply);
	return true;
}

//右侧push
bool RedisMgr::RPush(const std::string& key, const std::string& value) {
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == _reply)
	{
		std::cout << "Execut Command [ RPUSH " << key << " " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	if (_reply->type != REDIS_REPLY_INTEGER || _reply->integer <= 0) {
		std::cout << "Execut command [ RPUSH " << key << " " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}

	std::cout << "Execut command [ PUSH " << key << " " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//右侧pop
bool RedisMgr::RPop(const std::string& key, std::string& value) {
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "RPOP %s ", key.c_str());
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	value = _reply->str;
	std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//HSet 二级缓存
bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;

}

bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	const char* argv[4];
	std::size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;
	auto _reply = (redisReply*)redisCommandArgv(connect, 4, argv, argvlen);
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//HGet
std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return "";
	}
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();
	auto _reply = (redisReply*)redisCommandArgv(connect, 3, argv, argvlen);
	if (_reply == nullptr || _reply->type == REDIS_REPLY_NIL) {
		freeReplyObject(_reply);
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		return "";
	}

	std::string value = _reply->str;
	freeReplyObject(_reply);
	std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
	return value;
}
//Del
bool RedisMgr::Del(const std::string& key)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "DEL %s", key.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//判断键值是否存在
bool RedisMgr::ExistsKey(const std::string& key)
{
	auto connect = _con_pool->getConnection();
	if (connect == nullptr) {
		return false;
	}
	auto _reply = (redisReply*)redisCommand(connect, "exists %s", key.c_str());
	if (_reply == nullptr || _reply->type != REDIS_REPLY_INTEGER || _reply->integer == 0) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		freeReplyObject(_reply);
		return false;
	}
	std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
	freeReplyObject(_reply);
	return true;
}
//关闭
void RedisMgr::Close()
{
	//redisFree(_connect);
	_con_pool->Close();
}