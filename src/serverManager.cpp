#include "serverManager.h"
#include "session.h"
#include "CJsonObject/CJsonObject.hpp"
#include "logSys.h"
#include "common.h"

// 单例模式
ServerManager* ServerManager::instance()
{
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
        return;
    }

    LOG_DEBUG(boost::format("request: %1%, origin: %2%") % request % getIpPortBySession(session));
    string functionName;
	neb::CJsonObject param;
    if (reqJson.Get("function", functionName))
    {
        std::map<string, bFunc>::const_iterator iter = m_funcs.find(functionName);
        if (m_funcs.end() != iter)
        {
            // 调用处理函数
			reqJson.Get("param", param);
            if (param.IsEmpty() || !param.IsArray())
	        {
		        LOG_INFO("参数格式不正确");
                neb::CJsonObject error;
                genErrorMsg(1, "param format error!", error);
                session->sendData(neb::CJsonObject(), error);
                return;
	        }
			iter->second(param, session);
        }
        else
        {
            LOG_INFO("not find function!");
        }
        
    }
    else
    {
        LOG_INFO("request function is empty!");
    }    
}
