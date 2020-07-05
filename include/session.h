#ifndef _SESSION_H_
#define _SESSION_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string.h>

using namespace std;
using boost::asio::ip::tcp;

class Session : public boost::enable_shared_from_this<Session>
{   
public:
    Session() = delete;
    Session(boost::asio::io_service& ios);
    tcp::socket& getSocket();

    void communicationInit();
    void write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred);
    void read_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred);

private:
    tcp::socket m_socket;                       // socket
    boost::shared_ptr<std::string> m_buffer;
};
using session_ptr = boost::shared_ptr<Session>;

#endif // _SESSION_H_