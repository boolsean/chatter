#ifndef GDM_IPOSTLISTENER
#define GDM_IPOSTLISTENER

#include <string>

namespace gdm {

class IPostListener
{

public:
    virtual ~IPostListener() {}
    virtual void onPostEvent(const std::string& event)=0;
    virtual void onAdminEvent(const std::string& event)=0;

};

} // close namespace gdm

#endif
