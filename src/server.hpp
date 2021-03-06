#ifndef __SERVER__
#define __SERVER__

#include "connection_pool.hpp"

#include <string>
#include <boost/asio.hpp>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>


namespace sioux {
	class request_handler;
	class server {
		
	public:
		server(const std::string &address, const std::string &port );
		void run( std::size_t thread_count = 1 );

	private:
		void start();
		void run_thread();
		void accept_handler( const boost::system::error_code &ec );

		boost::asio::io_service 					m_ioService;
		boost::asio::ip::tcp::acceptor 				m_acceptor;
		std::shared_ptr< request_handler > 			m_requestHandler;
		connection_pool								m_connectionPool;
		boost::shared_ptr< connection > 			m_incomingConnection;
		boost::thread_group							m_workerThreads;
	};
}

#endif
