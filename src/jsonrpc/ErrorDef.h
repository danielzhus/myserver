#ifndef _ERROR_DEF_H_
#define _ERROR_DEF_H_
#include "utils/type.h"
#include <string>
#include <vector>

enum {
    JSON_RPC_ERROR_PARSE_ERROR = -32700,        //语法解析错误
    JSON_RPC_ERROR_INVALID_REQUEST = -32600,    // 无效请求
    JSON_RPC_ERROR_METHOD_NOT_FOUND = -32601,   // 找不到方法
    JSON_RPC_ERROR_INVAIL_PARAMS = -32602,      // 无效的参数
    JSON_RPC_ERROR_INTERNAL = -32603,           // 内部错误
};

class JError
{
public:
    JError():m_nErrorID(0){}
    void setErrorID(r_int32 errorID) { m_nErrorID = errorID; }
    void setErrorMsg(std::string errorMsg) { m_strErrorMsg = errorMsg; }
    void setErrorData(const std::vector<char>&& errorData) { m_vData = errorData; }

    bool isSuccess() const
    {
        return m_nErrorID == 0;
    }

    bool operator!() const
    {
        return !isSuccess();
    }

    void operator=(const JError& error)
    {
        this->m_nErrorID = error.m_nErrorID;
        this->m_strErrorMsg = error.m_strErrorMsg;
    }

    r_int32             m_nErrorID;     // 错误ID（上面是默认的几种错误）
    std::string         m_strErrorMsg;  // 错误信息
    std::vector<char>   m_vData;        // 错误附带数据
};
#endif // _ERROR_DEF_H_