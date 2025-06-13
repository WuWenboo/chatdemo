#pragma once
/*****************************************************************//**
 * \file   LogicSystem.h
 * \brief  ����get��post����
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;	//�ص�

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;

public:
	~LogicSystem();
	
	bool HandleGet(std::string path, std::shared_ptr<HttpConnection> con);	//����get

	bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);

	void RegGet(std::string url, HttpHandler handler);

	void RegPost(std::string url, HttpHandler handler);
private:
	LogicSystem();
	
	//_post_handlers��_get_handlers�ֱ���post�����get����Ļص�����map��keyΪ·�ɣ�valueΪ�ص�������
	std::map<std::string, HttpHandler> _post_handlers;

	std::map<std::string, HttpHandler> _get_handlers;
};

