#ifndef JSON_RPC_H
#define JSON_RPC_H
#include <CJsonObject/CJsonObject.hpp>
#include <ErrorDef.h>
class JsonRpcRequest
{
public:
    // 可支持多种构造函数
    JsonRpcRequest(const std::string& json);
    JsonRpcRequest(const neb::CJsonObject& rpcData);
    JsonRpcRequest(const JsonRpcRequest& rpcData);

    std::string toString();

    virtual ~JsonRpcRequest();
private:
    int                 m_nJsonRpcVersion;
    int                 m_nSeq;
    std::string         m_strMethod;
    neb::CJsonObject    m_params;
};

// 响应对象必须包含 result 或 error 字段，但两个字段不能同时存在
class JsonRpcResponse
{
public:
    JsonRpcResponse();
    JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error, int version = 2);
    void setResult(const neb::CJsonObject& result);
    void setError(const JError& error);
    void setSql(int seq);
    std::string toString();
private:
    int                 m_nJsonRpcVersion;
    int                 m_nSeq;
    neb::CJsonObject    m_result;
    JError              m_error;
};

#endif // JSON_RPC_H