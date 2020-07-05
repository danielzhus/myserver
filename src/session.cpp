#include "session.h"
#include "logSys.h"
#include <boost/bind.hpp>
#include <iostream>

Session::Session(boost::asio::io_service& ios):m_socket(ios), m_buffer(new std::string()){}

tcp::socket& Session::getSocket()
{
    return m_socket;
}

void Session::communicationInit()
{
    m_socket.async_read_some(boost::asio::buffer(*m_buffer),
          boost::bind(&Session::read_handler, shared_from_this(), m_buffer, _1, _2));
}

void Session::write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred)
{

}

void Session::read_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout << *pstr << std::endl;
    }
}