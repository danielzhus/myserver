#ifndef _SESSION_H_
#define _SESSION_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string.h>
#include "CJsonObject/CJsonObject.hpp"

using namespace std;
using boost::asio::ip::tcp;

#define BUFFER_SIZE 1024 * 64

namespace jsonrpc 
{
    class JsonRpcRequest;
    class JsonRpcResponse;
}

class Session : public boost::enable_shared_from_this<Session>
{   
public:
    Session() = delete;
    virtual ~Session();
    Session(boost::asio::io_service& ios);
    tcp::socket& getSocket();

    void recvData();
    void read_handler(boost::system::error_code ec, size_t bytes_transferred, boost::shared_ptr<boost::array<char, BUFFER_SIZE> > buffer);

    void sendData(const jsonrpc::JsonRpcResponse& response);

private:
    tcp::socket m_socket;                       // socket
	boost::shared_ptr< boost::asio::io_service::strand >  m_handleStrand;
    boost::shared_ptr< boost::asio::io_service::strand >  m_emitStrand;
};
using session_ptr = boost::shared_ptr<Session>;

#endif // _SESSION_H_
