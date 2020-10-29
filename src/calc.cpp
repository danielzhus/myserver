#include "calc.h"
#include "serverManager.h"
#include "logSys.h"

void regeist()
{
	ServerManager::instance()->setFunc("add", _add);
	ServerManager::instance()->setFunc("sub", _sub);
	ServerManager::instance()->setFunc("mul", _mul);
	ServerManager::instance()->setFunc("div", _div);
}

void _add(neb::CJsonObject param, session_ptr session)
{
	int paramSize = param.GetArraySize();
	if (paramSize != 2)
	{
		LOG_ERROR("参数格式不正确");
		return;
	}

	double summand, addend;
	param.Get(0, summand);
	param.Get(1, addend);

	double ret = add(summand, addend);
	neb::CJsonObject resp;
	resp.Add("sum", ret);
	session->sendData(resp, neb::CJsonObject());
}

void _sub(neb::CJsonObject param, session_ptr session)
{
	int paramSize = param.GetArraySize();
	if (paramSize != 2)
	{
		LOG_ERROR("参数格式不正确");
		return;
	}

	double summand, addend;
	param.Get(0, summand);
	param.Get(1, addend);

	double ret = sub(summand, addend);
	neb::CJsonObject resp;
	resp.Add("sub", ret);
	session->sendData(resp, neb::CJsonObject());
}

void _mul(neb::CJsonObject param, session_ptr session)
{
		int paramSize = param.GetArraySize();
	if (paramSize != 2)
	{
		LOG_ERROR("参数格式不正确");
		return;
	}

	double summand, addend;
	param.Get(0, summand);
	param.Get(1, addend);

	double ret = mul(summand, addend);
	neb::CJsonObject resp;
	resp.Add("mul", ret);
	session->sendData(resp, neb::CJsonObject());
}

void _div(neb::CJsonObject param, session_ptr session)
{
	int paramSize = param.GetArraySize();
	if (paramSize != 2)
	{
		LOG_ERROR("参数格式不正确");
		return;
	}

	double summand, addend;
	param.Get(0, summand);
	param.Get(1, addend);

	double ret = div(summand, addend);
	neb::CJsonObject resp;
	resp.Add("div", ret);
	session->sendData(resp, neb::CJsonObject());
}

double add(double value1, double value2)
{
    return value1 + value2;
}


double sub(double value1, double value2)
{
	return value1 - value2;
}

double mul(double value1, double value2)
{
	return value1 * value2;
}

double div(double value1, double value2)
{
	return value1 / value2;
}
