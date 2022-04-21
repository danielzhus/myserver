#include <JsonRpc.h>
#include <JsonRpcCommon.h>


namespace jsonrpc
{
    JsonRpcRequest::JsonRpcRequest(const std::string& json)
    {
        if (json.empty())
        {
            LOG_INFO("请求为空!")
            return;
        }

        neb::CJsonObject reqJson(json);
        if (reqJson.IsEmpty())
        {
            LOG_INFO("request is empty");
            return;
        }
    }
    JsonRpcRequest::JsonRpcRequest(const neb::CJsonObject& rpcData)
    {

    }

    JsonRpcRequest::JsonRpcRequest(const JsonRpcRequest& rpcData)
    {

    }

    JsonRpcRequest::~JsonRpcRequest()
    {
        
    }

    std::string JsonRpcRequest::toString()
    {

    }

    JsonRpcResponse::JsonRpcResponse()
    {

    }

    JsonRpcResponse::JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error, int version = 2)
    {

    }

    JsonRpcResponse::~JsonRpcResponse()
    {}

    void JsonRpcResponse::setResult(const neb::CJsonObject& result)
    {

    }

    void JsonRpcResponse::setError(const JError& error)
    {

    }

    void JsonRpcResponse::setSeq(int seq)
    {

    }

    std::string JsonRpcResponse::toString()
    {

    }
}