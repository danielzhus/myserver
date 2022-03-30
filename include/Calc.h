#ifndef _CALC_H_
#define _CALC_H_
// 测试服务基本运算
#include <boost/shared_ptr.hpp>
#include "CJsonObject/CJsonObject.hpp"

class Session;
using session_ptr = boost::shared_ptr<Session>;

void regeist();
void _add(neb::CJsonObject param, session_ptr session);
void _sub(neb::CJsonObject param, session_ptr session);
void _mul(neb::CJsonObject param, session_ptr session);
void _div(neb::CJsonObject param, session_ptr session);

double add(double value1, double value2);
double sub(double value1, double value2);
double mul(double value1, double value2);
double div(double value1, double value2);

#endif // _CALC_H_
