#ifndef _FUNC_MANAGER_H_
#define _FUNC_MANAGER_H_

#include "server.h"
#include<boost/function.hpp>

typedef boost::function<void(string)> bFunc;

class FuncManager
{
public:
    FuncManager() = default;
    // 禁止拷贝构造
    FuncManager(const FuncManager &) = delete;
    // 禁止move
    FuncManager(const FuncManager &&) = delete;
    // 禁止复制
    void operator=(const FuncManager &) = delete;

    static FuncManager* instance();
    void setFunc(string funcName, bFunc func);
private:
    std::map<string, bFunc> m_funcs;            // 注册接口
};

#endif // _FUNC_MANAGER_H_