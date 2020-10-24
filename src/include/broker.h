#pragma once
#include "message.h"
#include "subscriber.h"
#include <string>
#include <queue>
#include <vector>
/**
 * @brief Message broker service.
 * 
 */
class broker
{
public:
    /**
     * @brief  Forward message by topic
     * 
     */
    void forward();
    /**
    * @brief  Subscribe on topics in message broker
    *
    * @param subscribe  subscriber
    */
    void subscribe(subscriber *subscribe);
    /**
     * @brief  Receive a message from publisher
     * 
     * @param newMessage a message with text and topic
     */
    void receive(const message &newMessage);

private:
    /**
     * @brief Queue of message
     * 
     */
    std::queue<message> msgQueue;
    /**
     * @brief List of subscriber for a message broker 
     * 
     */
    std::vector<subscriber *> subscriberList;
};
