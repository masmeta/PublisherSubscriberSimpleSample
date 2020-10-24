#pragma once
#include "message.h"
#include <iostream>
#include "broker.h"
/**
 * @brief Publisher pattern
 * 
 */
class publisher
{
public:
    /**
     * @brief Construct a new publisher object
     *
     */
    publisher();
    /**
     * @brief Destroy the publisher object
     *
     */
    ~publisher();
    /**
     * @brief  Send message on server
     *
     * @param newMessage a message
     * @param myServer  a server  where publish
     */
    void send(const message &newMessage, broker &myServer);
};
