#ifndef _LOOPDRAWSTRATEGY_H
#define _LOOPDRAWSTRATEGY_H
#include <boost/asio.hpp>
#include "IDrawStrategy.h"
#include "Common/Common.h"
class Application;
class LoopDrawStrategy
    :public IDrawStrategy
{
public:
    LoopDrawStrategy(boost::asio::io_service& io_service,UInt32 interval);
    
    ~LoopDrawStrategy( void );
    void Set(Application *pApp) { m_pApp = pApp;}

    virtual void Start( void );

    virtual void Stop( void );

protected:
    virtual void Loop(const boost::system::error_code& );

    boost::asio::deadline_timer m_timer;
    UInt32 m_interval;
    Application *m_pApp;
};
#endif
 
