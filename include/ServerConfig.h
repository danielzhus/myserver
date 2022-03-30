/**
*  服务读取配置文件相关函数
*  @author daniel
*  @since  2020-6-30
*/
#ifndef _SERVERCONFIG_H_
#define _SERVERCONFIG_H_

#include <string>
#include <map>

class GlobalConfig
{
public:
    GlobalConfig() = default;
    // 禁止拷贝构造
    GlobalConfig(const GlobalConfig &) = delete;
    // 禁止move
    GlobalConfig(const GlobalConfig &&) = delete;
    // 禁止复制
    void operator=(const GlobalConfig &) = delete;
    
    static GlobalConfig& instance();

    void initConfig(const std::string& configFileName);
    std::string getIp();
    int getPort();
    int getPthreadNum();
    std::string& getOtherConfig(const std::string& key);
private:
    int m_nPort;
    int m_nPthreadNum;
    std::string m_strIp;
    std::map<std::string, std::string> otherConfig;
};

#endif // _SERVERCONFIG_H_