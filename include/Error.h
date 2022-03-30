#ifndef _ERROR_H_
#define _ERROR_H_
#include <string>
#include "CJsonObject/CJsonObject.hpp"
struct Error
{
    int errorID;
    std::string ErrorMsg;

    Error():errorID(0){}

    bool isEmpty()
    {
        if (0 == errorID)
        {
            return true;
        }
        return false;
    }

    void getError(neb::CJsonObject& error)
    {
        error.Clear();
        error.Add("ErrorID", errorID);
        error.Add("ErrorMsg", ErrorMsg);
    }
};

enum
{
};



#endif // _ERROR_H_