#include "session.h"
#include "logSys.h"
#include "funcManager.h"
#include <boost/bind.hpp>
#include <boost/format.hpp>

Session::Session(boost::asio::io_service& ios):m_socket(ios){}

tcp::socket& Session::getSocket()
{
    return m_socket;
}

void Session::communicationInit()
{
    m_socket.async_read_some(boost::asio::buffer(m_buffer),
          boost::bind(&Session::read_handler, shared_from_this(), _1, _2));
}

void Session::read_handler(boost::system::error_code ec, size_t bytes_transferred)
{
    if (ec)
    {
        LOG(ERROR, boost::format("Read error %1%") % ec.message());
        return;
    }
    else // 读到信息
    {
        communicationInit();
        std::string req = "";
        req = std::string(m_buffer.begin(), m_buffer.begin() + bytes_transferred - 1);
        LOG(INFO, boost::format("Read data %1%; size = %2%") % req % bytes_transferred);

        // 处理请求
        //FuncManager::instance()->handleReq(string);
    }
}