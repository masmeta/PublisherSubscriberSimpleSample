#include <iostream>
#include <stdio.h>
#include <string.h>
#include "broker.h"
#include "message.h"
#include "publisher.h"
#include "subscriber.h"
#include "version.h"

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option>\n"
              << "Optional option:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-v,--version\t\tShow software version\n"
              << std::endl;
}

static void show_version(std::string name)
{
    std::cout << "Software version: " << VERSION << std::endl;
}

int main(int argc, char *argv[])
{
    //Parsing argument
    if (argc >= 3)
    {
        show_usage(argv[0]);
        return EXIT_SUCCESS;
    }
    // help display
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        show_usage(argv[0]);
        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
    {
        show_version(argv[0]);
        return EXIT_SUCCESS;
    }
    else
    {
        show_usage(argv[0]);
        return EXIT_SUCCESS;
    }

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

    return EXIT_SUCCESS;
}