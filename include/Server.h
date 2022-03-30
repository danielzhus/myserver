#ifndef _SERVER_H_
#define _SERVER_H_

#include "Session.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <map>

using namespace std;
using boost::asio::ip::tcp;
using sock_ptr = boost::shared_ptr<tcp::socket>;

class Server
{
  public:
    Server(string ip, int port);

    // 不允许拷贝
    Server(const Server &) = delete;
    Server(const Server &&) = delete;
    void operator=(const Server &) = delete;
    // 注册连接回调
    void init();    
    // 服务运行
    void run();
  private:
    // 注册连接等待回调
    void wait_connect();
    // accept处理
    void accept_handler(const boost::system::error_code &error, session_ptr session);
 
  private:
    boost::asio::io_service m_service;          // 主服务
    tcp::endpoint m_endpoint;                   // 配置监听端口
    tcp::acceptor m_acceptor;                   // 端口监听器
	boost::shared_ptr< boost::asio::io_service::work > m_work;
	boost::thread_group m_threads;			// 线程池
};

#endif // _SERVER_H_
