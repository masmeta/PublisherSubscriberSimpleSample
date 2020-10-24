#include "broker.h"

void broker::forward()
{
    while (!msgQueue.empty())
    {
        message tmpMsg = msgQueue.front();
        msgQueue.pop();
        for (int i = 0; i < subscriberList.size(); i++)
        {
            for (std::vector<std::string>::iterator topic = subscriberList.at(i)->topics.begin(); topic != subscriberList.at(i)->topics.end(); ++topic)
            {
                std::string stopic = *topic;
                if (stopic.compare(tmpMsg.getTopic()) == 0)
                    subscriberList.at(i)->msgQueue.push(tmpMsg);
            }
        }
    }
}

void broker::subscribe(subscriber *subscribe)
{
    subscriberList.push_back(subscribe);
}

void broker::receive(const message &newMessage)
{
    msgQueue.push(newMessage);
}
