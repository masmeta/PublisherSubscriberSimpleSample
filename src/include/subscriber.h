#pragma once
#include "message.h"
#include <queue> // std::queue
#include <string>
#include <vector>
#include <iostream>
/**
 * @brief  Subscriber pattern
 * 
 */
class subscriber
{
public:
    /**
     * @brief Construct a new subscriber object
     * 
     */
    subscriber();
    /**
     * @brief Destroy the subscriber object
     * 
     */
    ~subscriber();
    /**
     * @brief Display message with a topic
     * 
     */
    void print();
    /**
     * @brief  Add new topic to listen
     * 
     * @param newTopic  std:: string
     */
    void listen(std::string newTopic);
    /**
     * @brief  List of topics
     * 
     */
    std::vector<std::string> topics;
    /**
     * @brief Queue of messages  with all topics
     * 
     */
    std::queue<message> msgQueue;
};
