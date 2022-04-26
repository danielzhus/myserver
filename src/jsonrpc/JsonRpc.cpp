#include "JsonRpc.h"
#include "ErrorDef.h"
#include "JsonRpcCommon.h"

namespace jsonrpc
{
    JsonRpcRequest::JsonRpcRequest(const std::string& json)
    {
        if (json.empty())
        {
            m_error.m_nErrorID = JSON_RPC_ERROR_PARSE_ERROR;
            m_error.m_strErrorMsg = "json is null";
            return;
        }

        neb::CJsonObject reqJson(json);
        JsonToRequest(reqJson);
    }
    JsonRpcRequest::JsonRpcRequest(neb::CJsonObject& rpcData)
    {
        JsonToRequest(rpcData);
    }

    JsonRpcRequest::JsonRpcRequest(const JsonRpcRequest& rpcData)
    {
        this->m_nJsonRpcVersion = rpcData.m_nJsonRpcVersion;
        this->m_strMethod = rpcData.m_strMethod;
        this->m_params = rpcData.m_params;
        this->m_nSeq = rpcData.m_nSeq;
        this->m_error = rpcData.m_error;
    }

    void JsonRpcRequest::JsonToRequest(neb::CJsonObject& rpcData)
    {
        if (rpcData.IsEmpty())
        {
            m_error.m_nErrorID = JSON_RPC_ERROR_PARSE_ERROR;
            m_error.m_strErrorMsg = "json is null";
            return;
        }

        if ((!rpcData.IsNull("jsonrpc") || !rpcData.Get("jsonrpc", m_nJsonRpcVersion)) ||
            (!rpcData.IsNull("method") || !rpcData.Get("method", m_strMethod)) ||
            (!rpcData.IsNull("params") || !rpcData.Get("params", m_params)) ||
            (!rpcData.IsNull("id") || !rpcData.Get("id", m_nSeq)))
        {
            m_error.m_nErrorID = JSON_RPC_ERROR_PARSE_ERROR;
            m_error.m_strErrorMsg = "jsonrpc 格式错误";
            return;
        }
    }

    JsonRpcRequest::~JsonRpcRequest()
    {
        
    }

    std::string JsonRpcRequest::toJsonString()
    {
        neb::CJsonObject reqJson;
        reqJson.Add("jsonrpc", m_nJsonRpcVersion);
        reqJson.Add("method", m_strMethod);
        reqJson.Add("params", m_params);
        reqJson.Add("id", m_nSeq);

        if(!reqJson.IsEmpty())
        {
            return reqJson.ToString();
        }
        return "";
    }

    JsonRpcResponse::JsonRpcResponse() : IJsonRpc(2, 0)
    {
    }

    // 这里记录一个知识点，派生类初始化列表不可以直接初始化父类成员
    // 如果要在初始化列表中初始化（比如const成员），可以在父类函数中写初始化列表
    // 在派生类构造函数初始化列表中调用父类初始化函数
    // 当然也可以在函数体中赋值，但是这就等于初始化了一次，又赋值了一次
    JsonRpcResponse::JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error, int version) 
                                    : IJsonRpc(version, seq),
                                    m_result(result)
                        
    {
        m_error = error;
    }

    JsonRpcResponse::~JsonRpcResponse()
    {}

    void JsonRpcResponse::setResult(const neb::CJsonObject& result, int seq)
    {
        if (result.IsEmpty())
        {
            return;
        }

        m_result = result;
        m_nSeq = seq;
    }

    void JsonRpcResponse::setError(const JError& error, int seq)
    {
        m_error = error;
        m_nSeq = seq;
    }

    std::string JsonRpcResponse::toJsonString()
    {
        neb::CJsonObject respJson;
        respJson.Add("jsonrpc", m_nJsonRpcVersion);
        if (m_error.isSuccess())
        {
            respJson.Add("result", m_result);
        }
        else
        {
            neb::CJsonObject errorJson;
            genErrorJson(m_error, errorJson);
            respJson.Add("error", errorJson);
        }
        respJson.Add("id", m_nSeq);

        if(!respJson.IsEmpty())
        {
            return respJson.ToString();
        }
        return "";
    }
}