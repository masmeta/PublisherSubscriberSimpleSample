#include "publisher.h"

publisher::publisher()
{
}

publisher::~publisher()
{
}

void publisher::send(const message& newMessage,broker& myServer)
{
    myServer.receive(newMessage);
}
