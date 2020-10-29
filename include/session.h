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

class Session : public boost::enable_shared_from_this<Session>
{   
public:
    Session() = delete;
    Session(boost::asio::io_service& ios);
    tcp::socket& getSocket();

    void recvData();
    void read_handler(boost::system::error_code ec, size_t bytes_transferred);

    void sendData(neb::CJsonObject response, neb::CJsonObject error);

private:
    tcp::socket m_socket;                       // socket
	boost::shared_ptr< boost::asio::io_service::strand >  m_strand;
    boost::array<char, BUFFER_SIZE> m_buffer;
};
using session_ptr = boost::shared_ptr<Session>;

#endif // _SESSION_H_
