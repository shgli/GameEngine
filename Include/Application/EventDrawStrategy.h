#ifndef _EVENTDRAWSTRATEGY_H
#define _EVENTDRAWSTRATEGY_H
#include "Application/LoopDrawStrategy.h"
class EventDrawStrategy
    :public LoopDrawStrategy
{
public:
    EventDrawStrategy(boost::asio::io_service& io_service,UInt32 time);

    void Invalidate( void ) { m_bNeeDraw = true; }
protected:
    virtual void Loop(const boost::system::error_code& );

    bool m_bNeeDraw;
};
#endif
 
