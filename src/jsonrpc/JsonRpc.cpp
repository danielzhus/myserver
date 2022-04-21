#include "JsonRpc.h"
#include "CJsonObject/CJsonObject.hpp"
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
    JsonRpcRequest::JsonRpcRequest(const neb::CJsonObject& rpcData)
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

    void JsonRpcRequest::JsonToRequest(const neb::CJsonObject& rpcData)
    {
        if (reqJson.IsEmpty())
        {
            m_error.m_nErrorID = JSON_RPC_ERROR_PARSE_ERROR;
            m_error.m_strErrorMsg = "json is null";
            return;
        }

        JError error;
        if ((!reqJson.GetKey("jsonrpc") || !reqJson.Get("jsonrpc", m_nJsonRpcVersion)) ||
            (!reqJson.GetKey("method" || !reqJson.Get"method", m_strMethod)) ||
            (!reqJson.GetKey("params") || !reqJson.Get("params", m_params)) ||
            (!reqJson.GetKey("id") || !reqJson.Get("id", m_nSeq)))
        {
            error.m_nErrorID = JSON_RPC_ERROR_PARSE_ERROR;
            error.m_strErrorMsg = "jsonrpc 格式错误";
            return;
        }
    }

    JsonRpcRequest::~JsonRpcRequest()
    {
        
    }

    std::string JsonRpcRequest::toString()
    {
        neb::CJsonObject reqJson;
        reqJson.Add("jsonrpc", m_nJsonRpcVersion);
        reqJson.Add("method", m_strMeghod);
        reqJson.Add("params", m_params);
        reqJson.Add("id", m_nSeq);

        if(!reqJson.IsEmpty())
        {
            return reqJson.ToString();
        }
        return "";
    }

    JsonRpcResponse::JsonRpcResponse() : m_nJsonRpcVersion(2), m_nSeq(0)
    {
    }

    JsonRpcResponse::JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error, int version) 
                                    : m_nJsonRpcVersion(version),
                                    : m_nSeq(seq),
                                    : m_result(result),
                                    : m_error(error)
                        
    {

    }

    JsonRpcResponse::~JsonRpcResponse()
    {}

    void JsonRpcResponse::setResult(const neb::CJsonObject& result, int seq)
    {
        if (reqJson.IsEmpty())
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

    std::string JsonRpcResponse::toString()
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