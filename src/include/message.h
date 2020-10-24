#pragma once
#include <string>
/**
 * @brief  Class define a message
 * 
 */
class message
{
public:
    /**
     * @brief Construct a new message object
     * 
     * @param topic  topics string
     * @param value  message string
     */
    message(std::string topic, std::string value) : topic(topic), msg(value){};
    /**
     * @brief Get the Message object
     * 
     * @return std::string 
     */
    std::string getMessage();
    /**
     * @brief Get the Topic object
     * 
     * @return std::string 
     */
    std::string getTopic();

private:
    std::string msg;
    std::string topic;
};
