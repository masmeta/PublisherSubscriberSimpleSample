#include <iostream>
#include "broker.h"
#include "message.h"
#include "publisher.h"
#include "subscriber.h"

int main()
{
    subscriber firstSub;
    subscriber secondSub;

    publisher firstPub;
    publisher SecondPub;

    broker myServer;

    message msg("firstTopic", "I print the first message on the topic");
    message msg1("firstTopic", "I print the second message on the topic");
    message msg2("secondTopic", "I print the first message on the second topic");
    message msg3("secondTopic", "I print the second message on the topic");

    firstSub.listen("firstTopic");
    secondSub.listen("firstTopic");
    secondSub.listen("secondTopic");

    myServer.subscribe(&firstSub);
    myServer.subscribe(&secondSub);

    firstPub.send(msg, myServer);
    firstPub.send(msg1, myServer);

    SecondPub.send(msg2, myServer);
    SecondPub.send(msg3, myServer);

    myServer.forward();

    std::cout << "--[First subscriber print]--" << std::endl;
    firstSub.print();
    std::cout << "--[Second subscriber print]--" << std::endl;
    secondSub.print();
}