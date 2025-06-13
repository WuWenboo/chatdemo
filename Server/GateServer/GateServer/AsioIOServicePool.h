#pragma once
/*****************************************************************//**
 * \file   AsioIOServicePool.h
 * \brief  ���ASIO IOContext Pool �ṹ���ö��io_context���ڲ�ͬ���߳���
 * 
 * \author 86187
 * \date   March 2025
 *********************************************************************/
#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"

namespace asio = boost::asio;

class AsioIOServicePool : public Singleton<AsioIOServicePool>
{
	friend Singleton<AsioIOServicePool>;
public:
	using IOService = boost::asio::io_context;
	using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;

	~AsioIOServicePool();

	AsioIOServicePool(const AsioIOServicePool&) = delete;

	AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;
	// ʹ�� round-robin �ķ�ʽ����һ�� io_service
	asio::io_context& GetIOService();

	void Stop();
private:
	AsioIOServicePool(std::size_t size = 2 /*std::thread::hardware_concurrency()*/);	//Ĭ���߳�

	std::vector<IOService> _ioServices;		//ioc_context

	std::vector<WorkPtr> _works;

	std::vector<std::thread> _threads;

	std::size_t _nextIOService;
};

