#pragma once
/*****************************************************************//**
 * \file   MysqlMgr.h
 * \brief  π‹¿ÌmysqlDao
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"
#include "MysqlDao.h"

class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();

	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);

	bool CheckEmail(const std::string& name, const std::string& email);
	
	bool UpdatePassword(const std::string& name, const std::string& email);
	
	bool CheckPassword(const std::string& name, const std::string& pwd, UserInfo& userInfo);
private:
	MysqlMgr();
	
	MysqlDao _dao;
};

