#include "serverConfig.h"
#include "logSys.h"
#include <iostream>
#include <fstream>

using namespace std;
#define DEFAULT_CONFIG_FILE "./config/config"

// 单例模式
GlobalConfig& GlobalConfig::instance()
{
    static GlobalConfig *gc = new GlobalConfig();
    return *gc;
}

void GlobalConfig::initConfig(const std::string& configFileName)
{
    std::string fileName;
    if(configFileName.empty())
    {
        fileName = DEFAULT_CONFIG_FILE;
    }
    else
    {
        fileName = configFileName;
    }

    // 打开文件
    ifstream configFile(configFileName, ios::in);
    if (!configFile.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
    }

    LOG_INFO("initConfig");
    // 按行读取配置
    std::string buf;
    while(getline(configFile, buf))
    {
    	LOG_INFO(boost::format("%1%") % buf);
        size_t index = buf.find(":");
        if (index == string::npos)
        {
            continue;
        }   
        
        // 获取key & value
        std::string key = buf.substr(0, index);
        std::string value = buf.substr(index + 1, buf.length() - index - 1);
        if (key == "ip")
        {
            m_strIp = value;
        }
        else if(key == "port")
        {
            m_nPort = atoi(value.c_str());
        }
        else if (key == "threadNum")
        {
            m_nPthreadNum = atoi(value.c_str());
        }
        else // 其他的配置都放在map里面
        {
            otherConfig[key] = value;
        }
    }
    configFile.close();
}

std::string GlobalConfig::getIp()
{
    return m_strIp;
}
int GlobalConfig::getPort()
{
    return m_nPort;
}
int GlobalConfig::getPthreadNum()
{
    return m_nPthreadNum;
}

std::string& GlobalConfig::getOtherConfig(const std::string& key)
{
    return otherConfig[key];
}
