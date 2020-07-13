#include "funcManager.h"

// 单例模式
FuncManager* FuncManager::instance()
{
    static FuncManager *fm = new FuncManager();
    return fm;
}

void FuncManager::setFunc(string funcName, bFunc func)
{
    m_funcs[funcName] = func;
}