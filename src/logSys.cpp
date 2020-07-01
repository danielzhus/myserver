#include <logSys.h>

void initSysLog()
{
    log4cxx::PropertyConfigurator::configureAndWatch("./config/logger.log4cxx");
}

bool levelIsValid(int level)
{
    if (level < _C_LEVEL_COUNT)
    {
        return true;
    }

    return false;
}