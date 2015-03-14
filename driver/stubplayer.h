#ifndef GDM_STUBPLAYER
#define GDM_STUBPLAYER

#include "player.h"

namespace gdm
{

class StubPlayer : public IPlayer
{
public:
    StubPlayer();

    virtual bool init();
    virtual bool start();
    virtual bool stop();
    virtual bool addSinks(void* fp);
};
}


#endif
