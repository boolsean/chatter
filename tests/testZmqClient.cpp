#include <zmq.hpp>
#include <string>
#include <iostream>
#include <sstream>



int main(int argc, char** argv) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);


    short portNo = 5555;
    std::ostringstream oss;
    oss << "tcp://localhost:";
    oss << portNo;

    std::cout << "Connecting to server port:" << portNo << std::endl;
    socket.connect(oss.str().c_str());

    for (int i = 0; i < 3; i++) {
        std::string msg("Hello");
        zmq::message_t request(msg.size()+1);
        memcpy((void*)request.data(), msg.c_str(), msg.size());
        std::cout << msg << std::endl;
        socket.send(request);

        // get reply
        zmq::message_t reply;
        socket.recv(&reply);
        char buf[6] = {0};
        memcpy(buf, reply.data(), reply.size());
        std::cout << "Received msg:[" << i << "] " << buf
            << std::endl;
    }

    return 0;
}
