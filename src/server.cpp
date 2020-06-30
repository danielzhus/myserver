#include <serverConfig.h>
#include <boost/asio.hpp>
#include <iostream>
#include <logSys.h>

using namespace std;
using boost::asio::ip::tcp;

void handler(const boost::system::error_code& error)
{
    if (!error)
    {
        // 连接成功
    }
}

int main(int argc, char *argv[])
{
    // 初始化日志
    initSysLog();
    LOG(INFO, "*****************server init*****************");
    
    // 初始化全局配置
    GlobalConfig& gc = GlobalConfig::instance();
    gc.initConfig("./config/config");

    // 配置服务器
    boost::asio::io_service io_service; // 主服务
    tcp::endpoint endpoint(tcp::v4(), gc.getPort()); //配置监听端口
    tcp::acceptor acceptor(io_service, endpoint); // 端口监听器
    tcp::socket skt(io_service);
    acceptor.async_accept(skt, handler);

    // 服务运行
    LOG(INFO, "*****************server finish*****************");
    io_service.run();

    return 0;
}