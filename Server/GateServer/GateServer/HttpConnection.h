#pragma once
/*****************************************************************//**
 * \file   HttpConnection.h
 * \brief  ����http���Ӻͽ��������ַ����������׸�LogicSystem�ദ��
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;

	HttpConnection(asio::io_context& ioc);
	
	void Start();		//����������д�¼�

	tcp::socket& GetSocket() {
		return _socket;
	}

private:
	void CheckDeadline();	//����Ƿ�ʱ

	void WriteResponse();	//Ӧ����

	void PreParseGetParam();	//����url

	void HandleReq();		//��������

	tcp::socket _socket;	
	
	beast::flat_buffer _buffer{ 8192 };		////_buffer��������������
	
	http::request<http::dynamic_body> _request;		//_request������������
	
	http::response<http::dynamic_body> _response;		//_response������Ӧ�ͻ���
	
	asio::steady_timer _deadline{		//_deadline��������ʱ���ж������Ƿ�ʱ��ֵ
		_socket.get_executor(),			//_socket������
		std::chrono::seconds(60)
	};

	std::string _get_url;

	std::unordered_map<std::string, std::string> _get_params;
};

