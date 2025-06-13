#pragma once
/*****************************************************************//**
 * \file   AsioIOServicePool.h
 * \brief  添加ASIO IOContext Pool 结构，让多个io_context跑在不同的线程中
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
	// 使用 round-robin 的方式返回一个 io_service
	asio::io_context& GetIOService();

	void Stop();
private:
	AsioIOServicePool(std::size_t size = 2 /*std::thread::hardware_concurrency()*/);	//默认线程

	std::vector<IOService> _ioServices;		//ioc_context

	std::vector<WorkPtr> _works;

	std::vector<std::thread> _threads;

	std::size_t _nextIOService;
};

