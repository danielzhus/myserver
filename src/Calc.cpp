#include "Calc.h"
#include "jsonrpc/JsonRpc.h"
#include "ServerManager.h"
#include "utils/LogSys.h"

void regeist()
{
	ServerManager::instance()->setFunc("add", _add);
	ServerManager::instance()->setFunc("sub", _sub);
	ServerManager::instance()->setFunc("mul", _mul);
	ServerManager::instance()->setFunc("div", _div);
}

void _add(request_ptr request, session_ptr session)
{
	const neb::CJsonObject& param = request->getParams();
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
	
	jsonrpc::JsonRpcResponse response(request->getSeq(), resp);
	session->sendData(response);
}

void _sub(request_ptr request, session_ptr session)
{
	const neb::CJsonObject& param = request->getParams();
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

	jsonrpc::JsonRpcResponse response(request->getSeq(), resp);
	session->sendData(response);
}

void _mul(request_ptr request, session_ptr session)
{
	const neb::CJsonObject& param = request->getParams();
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

	jsonrpc::JsonRpcResponse response(request->getSeq(), resp);
	session->sendData(response);
}

void _div(request_ptr request, session_ptr session)
{
	const neb::CJsonObject& param = request->getParams();
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

	jsonrpc::JsonRpcResponse response(request->getSeq(), resp);
	session->sendData(response);
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
