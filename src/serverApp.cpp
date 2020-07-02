#include "serverConfig.h"
#include "logSys.h"
#include "server.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    // 初始化日志
    initSysLog();
    LOG(INFO, "*****************server init*****************");
    
    // 初始化全局配置
    GlobalConfig& gc = GlobalConfig::instance();
    gc.initConfig("./config/config");

    // 配置服务器
    Server server(gc.getIp(), gc.getPort());

    // 服务运行
    LOG(INFO, "*****************server finish*****************");
    server.run();

    return 0;
}
