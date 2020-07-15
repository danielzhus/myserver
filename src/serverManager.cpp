#include "serverManager.h"

// 单例模式
ServerManager* ServerManager::instance()
{
    static ServerManager *fm = new ServerManager();
    return fm;
}

void ServerManager::setFunc(string funcName, bFunc func)
{
    m_funcs[funcName] = func;
}