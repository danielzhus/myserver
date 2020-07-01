#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/asio.hpp>
#include <string.h>

using namespace std;
using boost::asio::ip::tcp;

class Server
{
  public:
    Server(string ip, int port);

    // 不允许拷贝
    Server(const Server &) = delete;
    Server(const Server &&) = delete;
    void accept_handler(const boost::system::error_code &error, tcp::socket socket);
    void run();

    void operator=(const Server &) = delete;
  private:
    boost::asio::io_service m_service;          // 主服务
    tcp::endpoint m_endpoint;                   // 配置监听端口
    tcp::acceptor m_acceptor;                   // 端口监听器
    tcp::socket m_socket;                       // socket
};

#endif // _SERVER_H_