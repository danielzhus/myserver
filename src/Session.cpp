#include "Session.h"
#include "utils/LogSys.h"
#include "ServerManager.h"
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include "jsonrpc/JsonRpc.h"

Session::Session(boost::asio::io_service& ios):m_socket(ios), 
                                                m_handleStrand(new boost::asio::io_service::strand(ios)),
                                                m_emitStrand(new boost::asio::io_service::strand(ios)){}

Session::~Session()
{
    LOG(TRACE, boost::format("clear Session"));
}

tcp::socket& Session::getSocket()
{
    return m_socket;
}

void Session::recvData()
{
    boost::shared_ptr<boost::array<char, BUFFER_SIZE> > buffer(new boost::array<char, BUFFER_SIZE>());
    m_socket.async_read_some(boost::asio::buffer(*buffer),
          boost::bind(&Session::read_handler, shared_from_this(), _1, _2, buffer));
}

void Session::read_handler(boost::system::error_code ec, size_t bytes_transferred, boost::shared_ptr<boost::array<char, BUFFER_SIZE> > buffer)
{
    if (ec)
    {
        LOG(TRACE, boost::format("Read error %1%") % ec.message());
        return;
    }
    else // 读到信息
    {
        std::string req = "";
        req = std::string(buffer->begin(), buffer->begin() + bytes_transferred);
        LOG(INFO, boost::format("Read data %1%; size = %2%") % req % bytes_transferred);

        // 处理请求(抛出去)
        m_handleStrand->post(boost::bind(&ServerManager::handleReq, ServerManager::instance(), req, shared_from_this()));
    }
    recvData();
}

void Session::sendData(const jsonrpc::JsonRpcResponse& response)
{
    const string& resultStr = response.toJsonString();
    m_socket.write_some(boost::asio::buffer(resultStr, resultStr.size()));
}
