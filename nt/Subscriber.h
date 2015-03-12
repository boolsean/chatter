#ifndef INCLUDED_SUBSCRIBER_H
#define INCLUDED_SUBSCRIBER_H

#include <zmq.hpp>
#include <map>

class SubscriberEventHandler;

class Subscriber {
public:
    Subscriber(zmq::context_t& context);
    ~Subscriber();

    bool startListening();
    bool addSubscription(const std::string& filter);
    bool setEventHandler(SubscriberEventHandler* handler);


protected:
    SubscriberEventHandler* _handler;
    zmq::socket_t _subscriber;

private:

};


class SubscriberEventHandler
{
public:
    virtual bool onMsg(zmq::message_t msg) = 0;
    virtual bool onConnected() = 0;
};


#endif
