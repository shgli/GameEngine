#include <boost/thread.hpp>
#include <boost/system/system_error.hpp>
#include "Application/Service.h"
Service& Service::Instance()
{
    static Service service;
    return service;
}

void Service::LoopTimer(const boost::system::error_code& /*e*/)
{
    m_loopTimer.expires_at(m_loopTimer.expires_at() + boost::posix_time::seconds(2));
    m_loopTimer.async_wait(boost::bind(&Service::LoopTimer,this,boost::asio::placeholders::error));
}

void Service::ThreadFunc( void )
{
    LoopTimer(boost::system::error_code());
    m_ioService.run();
}

void Service::Run( void )
{
    boost::thread thrd(boost::bind(&Service::ThreadFunc,this));
}

