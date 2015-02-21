#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>


int main(int argc, char** argv) {
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

        // wait for next request from client
        std::cout << "waiting for client on port:" << portNo
            << "..." << std::endl;
        socket.recv(&request);
        std::cout << "Received Hello" << std::endl;

        sleep(1);

        zmq::message_t reply(5);
        memcpy((void*)reply.data(), "World", 5);
        socket.send(reply);

    }

    return true;
}


