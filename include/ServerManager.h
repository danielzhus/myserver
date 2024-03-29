#ifndef _FUNC_MANAGER_H_
#define _FUNC_MANAGER_H_

#include "Server.h"
#include <functional>
#include "CJsonObject/CJsonObject.hpp"

namespace jsonrpc
{
    class JsonRpcRequest;
}

class Session;
using request_ptr = std::shared_ptr<jsonrpc::JsonRpcRequest>;
using session_ptr = boost::shared_ptr<Session>;
typedef std::function<void(request_ptr, session_ptr)> bFunc;

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
