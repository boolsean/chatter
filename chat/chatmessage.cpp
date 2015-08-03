#include "chatmessage.h"

#include <iostream>


namespace gdm {

ChatMessage::ChatMessage()
    :   _from(),
        _to(),
        _msg()
{
}
ChatMessage::ChatMessage(const std::string& from, const std::string& to, const std::string& msg)
    :   _from(from),
        _to(to),
        _msg(msg)
{
    set(_from, _to, _msg);

}

ChatMessage::ChatMessage(const ChatMessage& rhs)
    :   _from(rhs._from),
        _to(rhs._to),
        _msg(rhs._msg)
{
    set(rhs._from, rhs._to, rhs._msg);

}

void ChatMessage::set(const std::string& from, const std::string& to, const std::string& msg)
{
    _raw.clear();
    _raw += from + "|"+ to + "|" + msg;
}

const char* ChatMessage::getRawBuffer() const
{
    if(_raw.empty())
        return NULL;
    return _raw.c_str();
}

size_t ChatMessage::getRawSize() const
{
    return _raw.size();
}

std::string ChatMessage::getFrom() const
{
    return _from;
}

std::string ChatMessage::getTo() const
{
    return _to;
}

std::string ChatMessage::getMsg() const
{
    return _msg;
}

ChatMessage ChatMessage::getChatMessage(const char* buffer, int size)
{
    std::string from;
    std::string to;
    std::string msg;

    int prevOffset = 0;
    for(int i = 0; i < size; i++) {

        if(buffer[i] == '|') {
            if(from.empty()) {
                from.append(buffer, i);
                prevOffset = i;
            }
            else if(to.empty()) {
                to.append(&buffer[prevOffset+1], i-prevOffset-1);
                prevOffset = i;
                break;
            }
        }
    }

    msg.append(&buffer[prevOffset+1], size-prevOffset-1);

/*    std::cout << "getChatMessage from:" << from << " to:" << to*/
/*        << " msg:" << msg << "|" << std::endl;*/

    return ChatMessage(from, to, msg);

}

} // close namespace gdm

