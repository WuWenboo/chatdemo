#pragma once
/*****************************************************************//**
 * \file   CServer.h
 * \brief  Á¬½ÓClient¶Ë
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(asio::io_context& ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor _acceptor;
	asio::io_context& _ioc;
	tcp::socket _socket;
};

