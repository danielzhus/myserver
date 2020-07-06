#ifndef _CALC_H_
#define _CALC_H_
// 测试服务基本运算
template <typename T>
class Calc
{
public:
    // 解析并返回结果
    void _add(string req, string resp);
    void _sub(string req, string resp);
    void _mul(string req, string resp);
    void _div(string req, string resp);
private:
    // 实现
    T add(T value1, T value2);
    T sub(T value1, T value2);
    T mul(T value1, T value2);
    T div(T value1, T value2);
};

#endif // _CALC_H_