#include "ServerManager.h"
#include "Session.h"
#include "Common.h"
#include "CJsonObject/CJsonObject.hpp"
#include "utils/LogSys.h"
#include "jsonrpc/JsonRpc.h"
#include <memory>

// 单例模式
ServerManager* ServerManager::instance()
{
    // magic static
    static ServerManager *fm = new ServerManager();
    return fm;
}

void ServerManager::setFunc(string funcName, bFunc func)
{
    m_funcs[funcName] = func;
}

void ServerManager::handleReq(string request, session_ptr session)
{
    neb::CJsonObject reqJson(request);
    if (reqJson.IsEmpty())
    {
        LOG_INFO("request is empty");
        JError error;
        error.setErrorID(JSON_RPC_ERROR_INVALID_REQUEST);
        error.setErrorMsg("request is empty");
        jsonrpc::JsonRpcResponse response(-1, neb::CJsonObject(), error);
        session->sendData(response);
        return;
    }

    LOG_DEBUG(FMT("request: {}, origin: {}", request, getIpPortBySession(session)));
    std::shared_ptr<jsonrpc::JsonRpcRequest> jRequest = std::make_shared<jsonrpc::JsonRpcRequest>(request);
    const JError& error = jRequest->getError();
    if (error.isSuccess())
    {
        std::map<string, bFunc>::const_iterator iter = m_funcs.find(jRequest->getMethodName());
        if (m_funcs.end() != iter)
        {
			iter->second(jRequest, session);
        }
        else
        {
            JError error;
            error.setErrorID(JSON_RPC_ERROR_METHOD_NOT_FOUND);
            error.setErrorMsg("method not found");
            jsonrpc::JsonRpcResponse response(jRequest->getSeq(), neb::CJsonObject(), error);
            session->sendData(response);
        }
    }
    else
    {
        LOG_INFO(FMT("errorID : {}, errorMsg : {}", error.m_nErrorID, error.m_strErrorMsg));
        jsonrpc::JsonRpcResponse response(jRequest->getSeq(), neb::CJsonObject(), error);
        session->sendData(response);
    }
}
