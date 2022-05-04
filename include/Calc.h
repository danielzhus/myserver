#ifndef _CALC_H_
#define _CALC_H_
// 测试服务基本运算
#include <boost/shared_ptr.hpp>
#include "CJsonObject/CJsonObject.hpp"

namespace jsonrpc
{
    class JsonRpcRequest;
}

using request_ptr = std::shared_ptr<jsonrpc::JsonRpcRequest>;

class Session;
using session_ptr = boost::shared_ptr<Session>;

void regeist();
void _add(request_ptr request, session_ptr session);
void _sub(request_ptr request, session_ptr session);
void _mul(request_ptr request, session_ptr session);
void _div(request_ptr request, session_ptr session);

double add(double value1, double value2);
double sub(double value1, double value2);
double mul(double value1, double value2);
double div(double value1, double value2);

#endif // _CALC_H_
