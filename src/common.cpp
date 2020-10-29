#include "common.h"
#include "session.h"
#include "stdlib.h"
#include "CJsonObject/CJsonObject.hpp"

string getIpPortBySession(const session_ptr session)
{
    boost::asio::ip::address ip = session->getSocket().remote_endpoint().address();
    int port = session->getSocket().remote_endpoint().port();
    char strPort[10] = {0};
    sprintf(strPort, "%d", port);
    if (ip.is_v4())
    {
        return ip.to_string() + ":" + strPort;
    }
    else if (ip.is_v6())
    {
        return "[" + ip.to_string() + "]:" + strPort;
    }
    return "";
}

void genErrorMsg(int errorId, std::string errorMsg, neb::CJsonObject res)
{
    res.Clear();
    res.Add("ErrorID", errorId);
    res.Add("ErrorMsg", errorMsg);
}