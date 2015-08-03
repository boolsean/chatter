#ifndef chatclient_h
#define chatclient_h

namespace gdm {

class ChatClient {
    public:
        bool sendMsg(const std::string& msg);
        bool sendMsg(const std::string& to, const std::string& msg);

        bool connect();

    protected:

    private:
};

} // close namespace gdm

#endif
