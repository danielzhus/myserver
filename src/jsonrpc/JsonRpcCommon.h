#ifndef JSON_RPC_COMMON_H
#define JSON_RPC_COMMON_H
#include <string>
#include "CJsonObject/CJsonObject.hpp"

class JError;
namespace jsonrpc
{
    void genErrorJson(const JError& error, neb::CJsonObject& res);
}
#endif // JSON_RPC_COMMON_H