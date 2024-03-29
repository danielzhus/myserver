#ifndef JSON_RPC_H
#define JSON_RPC_H
#include "ErrorDef.h"
#include "CJsonObject/CJsonObject.hpp"

namespace jsonrpc
{
    /**
     * @brief jsonRpc接口类，维护版本号和seq以及一些通用操作
     */
    class JsonRpc
    {
    public:
        JsonRpc(){}
        JsonRpc(int rpcVersion, int seq):m_nJsonRpcVersion(rpcVersion), m_nSeq(seq) {}

        JError getError() { return m_error; }
        /**
         * @brief 纯虚函数，将结构直接转换成json串
         * 
         * @return json串
         */

        int getSeq() { return m_nSeq; }
        virtual std::string toJsonString() const = 0;
    protected:
        int                 m_nJsonRpcVersion;
        int                 m_nSeq;
        JError              m_error;
    };

    /**
     * @brief rpc请求结构
     */
    class JsonRpcRequest : public JsonRpc
    {
    public:
        /**
         * @brief 提供多种构造方式，可以通过json，CJsonObject以及拷贝构造 
         */
        JsonRpcRequest(const std::string& json);
        JsonRpcRequest(neb::CJsonObject& rpcData);
        JsonRpcRequest(const JsonRpcRequest& rpcData);

        std::string getMethodName() const;
        const neb::CJsonObject& getParams() const;

        virtual std::string toJsonString() const;

        virtual ~JsonRpcRequest();
    private:
        void JsonToRequest(neb::CJsonObject& rpcData);
        std::string         m_strMethod;
        neb::CJsonObject    m_params;
    };

    /**
     * @brief rpc响应结构
     * 响应对象必须包含 result 或 error 字段，但两个字段不能同时存在
     */
    class JsonRpcResponse : public JsonRpc
    {
    public:
        /**
         * @brief 构造一个响应结构，提供默认构造后赋值，以及直接构造的方式
         * 
         */
        JsonRpcResponse();
        JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error = JError(), int version = 2);
        virtual ~JsonRpcResponse();
        void setResult(const neb::CJsonObject& result, int seq);
        void setError(const JError& error, int seq);
        virtual std::string toJsonString() const;
    private:
        neb::CJsonObject    m_result;
    };
}

#endif // JSON_RPC_H