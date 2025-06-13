#include "AsioIOServicePool.h"
#include <iostream>

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	:_ioServices(size), _works(size), _nextIOService(0)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		_works.emplace_back(std::make_unique<Work>(boost::asio::make_work_guard(_ioServices[i])));
	}

	//遍历多个io_service, 创建多个线程， 每个线程内部启动io_service
	for (std::size_t i = 0; i < _ioServices.size(); ++i) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool() {
	Stop();
	std::cout << "AsioIOServicePool destruct" << std::endl;
}

asio::io_context& AsioIOServicePool::GetIOService()
{
	auto& service = _ioServices[_nextIOService++ % _ioServices.size()];
	return service;
}

void AsioIOServicePool::Stop() {
	// 先停止所有 io_context
	for (auto& service : _ioServices) {
		service.stop();
	}

	// 释放所有 work_guard，让 io_context 退出 run()
	_works.clear();

	for (auto& t : _threads) {
		if (t.joinable()) {
			t.join();
		}
	}
}
