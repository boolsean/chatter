#ifndef GDM_PLAYER
#define GDM_PLAYER

namespace gdm
{

class IPlayer
{
public:
    virtual bool init()=0;
    virtual bool start()=0;
    virtual bool stop()=0;
    virtual bool addSinks(void* fp)=0;

    virtual ~IPlayer(){}
};

}

#endif
