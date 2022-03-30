#ifndef _FUNC_MANAGER_H_
#define _FUNC_MANAGER_H_

#include "Server.h"
#include<boost/function.hpp>
#include "CJsonObject/CJsonObject.hpp"

class Session;
using session_ptr = boost::shared_ptr<Session>;
typedef boost::function<void(neb::CJsonObject, session_ptr)> bFunc;

class ServerManager
{
public:
    ServerManager() = default;
    // 禁止拷贝构造
    ServerManager(const ServerManager &) = delete;
    // 禁止move
    ServerManager(const ServerManager &&) = delete;
    // 禁止复制
    void operator=(const ServerManager &) = delete;

    static ServerManager* instance();
    void setFunc(string funcName, bFunc func);
    void handleReq(string request, session_ptr session);
private:
    std::map<string, bFunc> m_funcs;            // 注册接口
};

#endif // _FUNC_MANAGER_H_
