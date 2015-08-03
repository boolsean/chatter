#include "chatmessage.h"

#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <zmq.hpp>
#include <unistd.h>
#include <queue>

static const short PORT_NO = 5555;
static const char* CONN_STR = "tcp://localhost:5555";

static zmq::context_t       context(1);
static zmq::socket_t        socket(context, ZMQ_REQ);

static bool                 connected = false;
static boost::mutex         lock;

bool                        started = false;

std::queue<gdm::ChatMessage> pendingMsgs;
std::string from("sean");


static void hbLoop()
{
    bool first = true;
    for(;;) {
        // sleep 1 s
        // check for pending msgs
        sleep(1);

        if(connected == false) {
            std::cout << "hbLoop exit" << std::endl;
            break;
        }

        // send a pending msg
        // else send a hb
        gdm::ChatMessage cm(from, "", "HB");
        {
            boost::lock_guard<boost::mutex> lg(lock);
            if(!pendingMsgs.empty()) {
                cm = pendingMsgs.front();
                pendingMsgs.pop();
            }
        }

        if(first) {
            std::cout << "first msg from:" << from << std::endl;
            first = false;
        }

        try {
            zmq::message_t request(cm.getRawSize());
            memcpy(reinterpret_cast<void*>(request.data()), cm.getRawBuffer(), cm.getRawSize());
            socket.send(request);
        }
        catch(std::exception& e) {
            std::cout << "ERROR sendMsg exception:" << e.what() << std::endl;
        }

        // print response from server
        char buf[5000];

        zmq::message_t reply;
        try {
            socket.recv(&reply);
            if(reply.size() > 0) {
                memcpy(buf, reply.data(), reply.size());
                buf[reply.size()] = '\0';
                gdm::ChatMessage cm = gdm::ChatMessage::getChatMessage(buf, reply.size());
                if(cm.getMsg() != "ACK")
                    std::cout << "printResponse msg:"<< cm.getMsg() << std::endl;
            }
            else {
                std::cout << "printReponse ERROR size:" << reply.size() << std::endl;
            }
        }
        catch(std::exception& e) {
            std::cout << "printResponse ERROR exception:" << e.what() << std::endl;
        }
    }
}



void connect()
{

    if(connected == false) {
        connected = true;
        socket.connect(CONN_STR);
        std::cout << "connected...." << std::endl;
        boost::thread hbThread(hbLoop);
    }
}

void sendMsg(const gdm::ChatMessage& cm)
{
    boost::lock_guard<boost::mutex> lg(lock);
    pendingMsgs.push(cm);
}

int main(int argc, char** argv)
{

    if(argc > 1) {
        from = argv[1];
        std::cout << "setting from:" << from << std::endl;
    }

    connect();
    for(;;) {
        std::string line("");
        std::getline(std::cin, line);
        if(line.empty()) {
            std::cout << "exiting..." << std::endl;
            break;
        }
        std::size_t pos = line.find_first_of(":");
        if(pos == std::string::npos) {
            std::cout << "could not find to delimiter ':'" << std::endl;
            continue;
        }

        std::string to(line.substr(0, pos));
        std::string msg(line.substr(pos+1));
        gdm::ChatMessage cm(from, to, msg);
        std::cout << "Payload:";
        std::cout << cm.getRawBuffer() << std::endl;

        sendMsg(cm);
    }

    return 0;
}

