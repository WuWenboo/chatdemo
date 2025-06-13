#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(asio::io_context& ioc, unsigned short& port)
	:_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) {

}

void CServer::Start()
{
	auto self = shared_from_this();
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);
	//接收新连接
	
	//_acceptor.async_accept(_socket, [self](beast::error_code ec) {
	//	try {
	//		if (ec) {	//出错这放弃这个连接，接续监听新连接
	//			self->Start();
	//			return;
	//		}
	//		//处理新连接，创建HttpConnection类管理新连接
	//		std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
	//		//继续监听
	//		self->Start();
	//	}
	//	catch (std::exception& exp) {	//网络异常关闭
	//		std::cout << "exception is " << exp.what() << std::endl;
	//		self->Start();
	//	}
	//	});
	_acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec) {
		try {
			//出错则放弃这个连接，继续监听新链接
			if (ec) {
				self->Start();
				return;
			}

			//处理新链接，创建HpptConnection类管理新连接
			new_con->Start();
			//继续监听
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
		});
}
