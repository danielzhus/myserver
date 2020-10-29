// 提供程序需要用的通用函数

#ifndef _COMMON_H_
#define _COMMON_H_
#include <boost/shared_ptr.hpp>
#include <string.h>
#include "CJsonObject/CJsonObject.hpp"

class Session;
using session_ptr = boost::shared_ptr<Session>;

std::string getIpPortBySession(const session_ptr session);
void genErrorMsg(int errorId, std::string errorMsg, neb::CJsonObject res);

#endif // _COMMON_H_