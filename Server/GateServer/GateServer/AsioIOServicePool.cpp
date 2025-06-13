#include "AsioIOServicePool.h"
#include <iostream>

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	:_ioServices(size), _works(size), _nextIOService(0)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		_works.emplace_back(std::make_unique<Work>(boost::asio::make_work_guard(_ioServices[i])));
	}

	//�������io_service, ��������̣߳� ÿ���߳��ڲ�����io_service
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
	// ��ֹͣ���� io_context
	for (auto& service : _ioServices) {
		service.stop();
	}

	// �ͷ����� work_guard���� io_context �˳� run()
	_works.clear();

	for (auto& t : _threads) {
		if (t.joinable()) {
			t.join();
		}
	}
}
