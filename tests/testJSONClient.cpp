#include "json.h"
#include <zmq.hpp>
#include <iostream>
#include <string>


Json::Value getJSonMsg(
        const std::string& from,
        const std::string& to,
        const std::string& msg)
{
    Json::Value root;
    root["timestamp"] = "now";

    Json::Value payload;
    payload["from"] = from;
    payload["to"] = to;
    payload["msg"] = msg;

    root["payload"] = payload;

    Json::Value topRoot;

    topRoot[0] = root;

    return topRoot;
}


int sendMsg(const std::string& wireMsg, zmq::socket_t& socket)
{
    zmq::message_t zmqMsg(wireMsg.size());
    memcpy(reinterpret_cast<void*>(zmqMsg.data()), wireMsg.c_str(), wireMsg.size());
    return socket.send(zmqMsg);
}

int recvMsg(zmq::message_t& zmqReply, zmq::socket_t& socket)
{

    return socket.recv(&zmqReply);
}


int main(int argc, char** argv)
{
    if(argc < 4) {
        std::cout << "not enough arguments req: <from> <to> <msg>" << std::endl;
        return 0;
    }

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    const char* connStr = "tcp://localhost:5554";

    // connect to the server

    socket.connect(connStr);
    std::cout << "connected to server at:" << connStr << std::endl;

    Json::Value msg = getJSonMsg(argv[1], argv[2], argv[3]);

    Json::FastWriter writer;
    std::string wireMsg = writer.write(msg);

    std::cout << "wireMsg:" << wireMsg << std::endl;

    try {
        int rc = sendMsg(wireMsg, socket);
        std::cout << "sendMsg rc:" << rc << std::endl;

        zmq::message_t zmqReply;
        rc = recvMsg(zmqReply, socket);
        std::cout << "recvMsg rc:" << rc << " msg size:" << zmqReply.size() << std::endl;

        if(zmqReply.size() > 0) {
            Json::CharReaderBuilder builder;
            Json::CharReader* reader = builder.newCharReader();
            std::string errs;

            Json::Value reply;
            bool ret = reader->parse(
                    reinterpret_cast<const char*>(zmqReply.data()),
                    reinterpret_cast<const char*>(zmqReply.data())+zmqReply.size(),
                    &reply,
                    &errs);

            if(ret == false) {
                std::cout << "parse ret:" << ret << " errs:" << errs << std::endl;
                return 0;
            }

            Json::StyledWriter styledWriter;
            std::cout << styledWriter.write(reply) << std::endl;

            delete reader;
        }
    }
    catch(std::exception& e) {
        std::cout << "exception msg:" << e.what() << std::endl;
    }

    return 0;
}


