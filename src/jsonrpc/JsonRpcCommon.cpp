#include "JsonRpcCommon.h"
#include "ErrorDef.h"
namespace jsonrpc
{
    void genErrorJson(const JError& error, neb::CJsonObject& res)
    {
        res.Clear();
        res.Add("code", error.m_nErrorID);
        res.Add("message", error.m_strErrorMsg);

        std::string errorData;
        const char* hex = "0123456789abcdef";
        char oneByte[3];
        for (auto v : error.m_vData)
        {
            sprintf(oneByte, "%c%c", hex[v >> 4], hex[v & 0xf]);
            errorData += std::string(oneByte);
        }
        res.Add("data", errorData);
    }
}