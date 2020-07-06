#include "server.h"
#include <logSys.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <iostream>

Server::Server(string ip, int port):m_service(), m_endpoint(tcp::v4(), port), m_acceptor(m_service, m_endpoint){}

void Server::init()
{
    // 目前只做等待连接处理
    wait_connect();
}

void Server::wait_connect()
{
    boost::system::error_code error;
    session_ptr session(new Session(m_service));
    m_acceptor.async_accept(session->getSocket(), boost::bind(&Server::accept_handler, this, error, session));
}

void Server::accept_handler(const boost::system::error_code &error, session_ptr session)
{
    if (!error)
    {
        // 连接成功
        LOG_INFO(boost::format("[连接成功 %1%:%2%]") % session->getSocket().remote_endpoint().address() % session->getSocket().remote_endpoint().port());
        
        // 连接成功快速返回不占用服务器资源
        wait_connect();
        session->communicationInit();
    }
}

void Server::run()
{
    m_service.run();
}
