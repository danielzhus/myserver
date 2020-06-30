/**
*  封装log4cxx便于项目打印log
*  @author daniel
*  @since  2020-6-30
*/

#ifndef _LOGSYS_H_
#define _LOGSYS_H_

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

enum LogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    _C_LEVEL_COUNT
};

static const int LOG4CXX_LEVEL_INT[_C_LEVEL_COUNT] = { 
    log4cxx::Level::TRACE_INT,
    log4cxx::Level::DEBUG_INT,
    log4cxx::Level::INFO_INT,
    log4cxx::Level::WARN_INT,
    log4cxx::Level::ERROR_INT,
    log4cxx::Level::FATAL_INT,
};

log4cxx::LoggerPtr logger;

void initSysLog()
{
    log4cxx::PropertyConfigurator::configureAndWatch("./config/logger.log4cxx");
    logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("fa"));
}

bool levelIsValid(int level)
{
    if (level < _C_LEVEL_COUNT)
    {
        return true;
    }

    return false;
}

#define LOG(level, msg) \
    if (levelIsValid(level)) \
    {   \
        ::log4cxx::LevelPtr lvptr = ::log4cxx::Level::toLevel(LOG4CXX_LEVEL_INT[level]); \           
        LOG4CXX_LOG(logger, lvptr, msg); \
    } \ 
    else \
    { \
        LOG4CXX_DEBUG(logger, msg); \
    }

#define LOG_TRACE(msg) LOG4CXX_TRACE(logger, msg);
#define LOG_DEBUG(msg) LOG4CXX_DEBUG(logger, msg);
#define LOG_INFO(msg) LOG4CXX_INFO(logger, msg);
#define LOG_WARN(msg) LOG4CXX_WARN(logger, msg);
#define LOG_ERROR(msg) LOG4CXX_ERROR(logger, msg);
#define LOG_FATAL(msg) LOG4CXX_FATAL(logger, msg);
    
#endif // _LOGSYS_H_