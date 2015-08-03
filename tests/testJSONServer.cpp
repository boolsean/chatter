#include "json.h"

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <list>
#include <map>

typedef std::list<Json::Value>                  Jsons;
typedef Jsons::iterator                         JsonsItr;
typedef Jsons::const_iterator                   JsonsConstItr;

typedef std::map<std::string, Jsons>            NameToJsonsMap;
typedef NameToJsonsMap::iterator                NameToJsonsMapItr;
typedef NameToJsonsMap::const_iterator          NameToJsonsMapConstItr;


NameToJsonsMap                                  pendingMsgs;


Json::Value getJsonMsg(const zmq::message_t& msg)
{
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errs;

    bool ret = reader->parse(
            reinterpret_cast<const char*>(msg.data()),
            reinterpret_cast<const char*>(msg.data())+msg.size(),
            &root,
            &errs);

    if(ret == false) {
        std::cout << "parse ret:" << ret << " errs:" << errs << std::endl;
    }

    return root;
}


bool getPendingMsg(const std::string& name, Json::Value& msg)
{
    NameToJsonsMapItr itr = pendingMsgs.find(name);
    if(itr != pendingMsgs.end()) {
        Jsons& msgs = itr->second;
        int i = 0;
        for(JsonsConstItr msgItr = msgs.begin(); msgItr != msgs.end(); msgItr++, i++) {
            msg[i] = *msgItr;
        }
        pendingMsgs.erase(itr);
        std::cout << "checkForPendingMsgs found msg:" << msg << std::endl;
        return true;
    }

    return false;
}


bool addPendingMsg(const Json::Value& msg)
{
    std::string toStr = msg[0]["payload"]["to"].asString();
    if(toStr.empty() == false) {
        NameToJsonsMapItr itr = pendingMsgs.find(toStr);
        if(itr == pendingMsgs.end()) {
            Jsons msgs;
            msgs.push_back(msg);
            pendingMsgs[toStr] = msgs;
        }
        else {
            itr->second.push_back(msg);
        }
        std::cout << "addPendingMsg storing msg:" << msg << std::endl;
        return true;
    }

    return false;
}


int main(int argc, char** argv)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    const char* connStr = "tcp://*:5554";

    socket.bind(connStr);

    for( ; ; ) {
        zmq::message_t zmqRequest;

        try {
            socket.recv(&zmqRequest);

            Json::Value request = getJsonMsg(zmqRequest);

            std::cout << "recieved from client:" << request << std::endl;

            addPendingMsg(request);

            std::string from = request[0]["payload"]["from"].asString();

            Json::Value reply;
            if(getPendingMsg(from, reply) == false) {
                reply["timestamp"] = "now";
                Json::Value payload;
                payload["user"] = "server";
                payload["msg"] = "Thank you," + request[0]["payload"]["from"].asString();
                reply["payload"] = payload;
            }


            Json::FastWriter writer;
            std::string wireMsg = writer.write(reply);

            zmq::message_t zmqResponse(wireMsg.size());
            memcpy(zmqResponse.data(), wireMsg.c_str(), wireMsg.size());
            socket.send(zmqResponse);

        }
        catch(std::exception& e) {
            std::cout << "exception msg:" << e.what() << std::endl;
        }

    }


    return 0;
}


