#include "server.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

Server::Server(string ip, int port):m_endpoint(tcp::v4(), port), m_acceptor(m_service, m_endpoint), m_socket(m_service)
{
    boost::system::error_code error;
    sock_ptr sock(new tcp::socket(m_service));
    m_acceptor.async_accept(m_socket, boost::bind(&Server::accept_handler, this, error, sock));
}

void Server::accept_handler(const boost::system::error_code &error, sock_ptr socket)
{
    if (!error)
    {
        // 连接成功
    }
}

void Server::run()
{
    m_service.run();
}
