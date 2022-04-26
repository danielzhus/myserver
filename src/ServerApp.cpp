#include "ServerConfig.h"
#include "utils/LogSys.h"
#include "Server.h"
#include "ServerManager.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Tip: ./server ../config/config" << endl;
        return 0;
    }

    // 初始化日志系统
    initSysLog();
    LOG(INFO, "*****************server init*****************");
    
    // 初始化全局配置
    GlobalConfig& gc = GlobalConfig::instance();
    gc.initConfig(argv[1]);

    // 配置服务器
    Server server(gc.getIp(), gc.getPort());
    server.init();

    // 服务运行
    LOG(INFO, "*****************server finish*****************");
    server.run();

    return 0;
}
