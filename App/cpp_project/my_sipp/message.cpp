#include "sipp.hpp"
#include "message.hpp"

struct KeywordMap {
    const char *keyword;
    MessageCompType type;
};

int SendingMessage::numComponents()
{
    return messageComponents.size();
}

SendingMessage::SendingMessage(scenario *msg_scenario, char *const_src, bool skip_sanity)
{

}

struct MessageComponent *SendingMessage::getComponent(int i) {
    return messageComponents[i];
}

bool SendingMessage::isAck()
{
    return ack;
}
bool SendingMessage::isCancel()
{
    return cancel;
}
bool SendingMessage::isResponse()
{
    return response;
}
char *SendingMessage::getMethod()
{
    return method;
}
int SendingMessage::getCode()
{
    return code;
}



