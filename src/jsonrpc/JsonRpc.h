#ifndef JSON_RPC_H
#define JSON_RPC_H
#include <CJsonObject/CJsonObject.hpp>
#include <ErrorDef.h>
namespace jsonrpc
{
    /**
     * @brief jsonRpc接口类，维护版本号和seq以及一些通用操作
     */
    class IJsonRpc
    {
    public:
        /**
         * @brief 纯虚函数，将结构直接转换成json串
         * 
         * @return json串
         */
        virtual std::string toJsonString() = 0;
    protected:
        int                 m_nJsonRpcVersion;
        int                 m_nSeq;
    };

    /**
     * @brief rpc请求结构
     */
    class JsonRpcRequest : public IJsonRpc
    {
    public:
        /**
         * @brief 提供多种构造方式，可以通过json，CJsonObject以及拷贝构造 
         */
        JsonRpcRequest(const std::string& json);
        JsonRpcRequest(const neb::CJsonObject& rpcData);
        JsonRpcRequest(const JsonRpcRequest& rpcData);

        virtual std::string toJsonString() = 0;

        virtual ~JsonRpcRequest();
    private:
        std::string         m_strMethod;
        neb::CJsonObject    m_params;
    };

    /**
     * @brief rpc响应结构
     * 响应对象必须包含 result 或 error 字段，但两个字段不能同时存在
     */
    class JsonRpcResponse : public IJsonRpc
    {
    public:
        /**
         * @brief 构造一个响应结构，提供默认构造后赋值，以及直接构造的方式
         * 
         */
        JsonRpcResponse();
        JsonRpcResponse(int seq, const neb::CJsonObject& result, const JError& error, int version = 2);
        virtual ~JsonRpcResponse();
        void setResult(const neb::CJsonObject& result);
        void setError(const JError& error);
        void setSeq(int seq);
        virtual std::string toJsonString() = 0;
    private:
        neb::CJsonObject    m_result;
        JError              m_error;
    };
}

#endif // JSON_RPC_H