#include "chatmessage.h"

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <map>

std::map<std::string, gdm::ChatMessage> dest2Msgs;


int main(int argc, char** argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    short portNo = 5555;
    std::ostringstream oss;
    oss << "tcp://*:";
    oss << portNo;

    std::cout << "binding to port:" << portNo << std::endl;
    socket.bind(oss.str().c_str());

    while(true) {
        zmq::message_t request;

        std::string from;
        std::string to;
        std::string msg;
        gdm::ChatMessage cm("", "", "");

        try {
            socket.recv(&request);
            std::cout << "data:" << (const char*) request.data() << std::endl;

            cm = gdm::ChatMessage::getChatMessage((const char*)request.data(), request.size());

            from = cm.getFrom();
            to = cm.getTo();
            msg = cm.getMsg();

            std::cout << "Received msg:" << cm.getRawBuffer() << std::endl;
        }
        catch(std::exception& e) {
            std::cout << "exception:" << e.what() << std::endl;
        }

        if(!to.empty()) {
            std::cout << "insert to pending map to:" << to << " msg:" << msg << std::endl;
            dest2Msgs[to] = cm;
        }

        gdm::ChatMessage respCM(from, "", "ACK");
        std::map<std::string, gdm::ChatMessage>::iterator it = dest2Msgs.find(from);
        if(it != dest2Msgs.end()) {
            respCM = it->second;
            dest2Msgs.erase(it);
        }

        zmq::message_t reply(respCM.getRawSize());
        memcpy(reinterpret_cast<void*>(reply.data()), respCM.getRawBuffer(), respCM.getRawSize());
        socket.send(reply);
    }

    return true;
}


