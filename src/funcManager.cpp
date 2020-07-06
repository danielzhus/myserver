#include "funcManager.h"


FuncManager::FuncManager(Server *server)
{
    this->server = server;
}

// 单例模式
FuncManager& FuncManager::instance(Server *server)
{
    static FuncManager *fm = new FuncManager(server);
    return *fm;
}

void FuncManager::setFunc(string funcName, bFunc func)
{
    m_funcs[funcName] = func;
}