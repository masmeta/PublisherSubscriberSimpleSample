#include "subscriber.h"

subscriber::subscriber()
{
}

subscriber::~subscriber()
{
}

void subscriber::print()
{
    while(!msgQueue.empty())
    {
        message msg = msgQueue.front();
        msgQueue.pop();
        std::cout << msg.getMessage() << std::endl;
    }
}

void subscriber::listen(std::string newTopic)
{
    topics.push_back(newTopic);
}
