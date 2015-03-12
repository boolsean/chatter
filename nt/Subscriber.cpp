#include "Subscriber.h"


Subscriber::Subscriber(zmq::context_t& context)
    :   _handler(NULL),
    _subscriber(context, ZMQ_SUB)
{
}

Subscriber::~Subscriber()
{
}

bool Subscriber::startListening()
{
    return true;
}

bool Subscriber::addSubscription(const std::string& filter)
{
    return true;
}

bool Subscriber::setEventHandler(SubscriberEventHandler* handler)
{
    if(handler == NULL)
        return false;

    _handler = handler;
    return true;
}

