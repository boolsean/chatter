#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <string>

namespace gdm {

class ChatMessage {
public:
    ChatMessage();
    ChatMessage(const std::string& from, const std::string& to, const std::string& msg);
    ChatMessage(const ChatMessage& rhs);
    void set(const std::string& from, const std::string& to, const std::string& msg);

    const char* getRawBuffer() const;
    size_t getRawSize() const;
    std::string getFrom() const;
    std::string getTo() const;
    std::string getMsg() const;

    static ChatMessage getChatMessage(const char* buffer, int size);

protected:

private:
    std::string     _raw;
    std::string     _from;
    std::string     _to;
    std::string     _msg;
};

} // close namespace gdm

#endif
