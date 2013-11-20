#include <boost/bind.hpp>
#include "Common/Common.h"
#include "Application/LoopDrawStrategy.h"
#include "Application/Application.h"
LoopDrawStrategy::LoopDrawStrategy(boost::asio::io_service& io_service,UInt32 interval)
    :m_timer(io_service)
    ,m_interval(interval)
    ,m_pApp(nullptr)
{}

LoopDrawStrategy::~LoopDrawStrategy( void )
{
    Stop();
}

void LoopDrawStrategy::Start( void )
{
    m_timer.expires_at(m_timer.expires_at() + boost::posix_time::millisec(m_interval));
    m_timer.async_wait(boost::bind(&LoopDrawStrategy::Loop,this,boost::asio::placeholders::error));   
}

void LoopDrawStrategy::Stop( void )
{
    m_timer.cancel();
}

void LoopDrawStrategy::Loop(const boost::system::error_code& )
{
    if(nullptr != m_pApp)
    {
    }
    Start();
}
