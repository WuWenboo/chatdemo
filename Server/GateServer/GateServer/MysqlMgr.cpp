#include "MysqlMgr.h"

MysqlMgr::~MysqlMgr() {

}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return _dao.RegUser(name, email, pwd);
}

bool MysqlMgr::CheckEmail(const std::string& name, const std::string& email)
{
	return _dao.CheckEmail(name, email);
}

bool MysqlMgr::UpdatePassword(const std::string& name, const std::string& pwd)
{
	return _dao.UpdatePassword(name, pwd);
}

MysqlMgr::MysqlMgr() {

}

bool MysqlMgr::CheckPassword(const std::string& name, const std::string& pwd, UserInfo& userInfo)
{
	return _dao.CheckPassword(name, pwd, userInfo);
}
