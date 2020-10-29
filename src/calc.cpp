#include "calc.h"
#include "serverManager.h"
#include "logSys.h"

void regist()
{
	ServerManager::instance()->setFunc("add", _add);
	ServerManager::instance()->setFunc("sub", _sub);
	ServerManager::instance()->setFunc("mul", _mul);
	ServerManager::instance()->setFunc("div", _div);
}

void _add(neb::CJsonObject param, session_ptr session)
{
	if (!param.IsArray())
	{
		LOG_INFO("参数格式不正确");
	}
}

void _sub(neb::CJsonObject param, session_ptr session)
{

}
void _mul(neb::CJsonObject param, session_ptr session)
{
}

void _div(neb::CJsonObject param, session_ptr session)
{

}
