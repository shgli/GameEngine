#include "Application/EventDrawStrategy.h"
#include "Application/Application.h"
EventDrawStrategy::EventDrawStrategy(boost::asio::io_service& io_service,UInt32 time)
    :LoopDrawStrategy(io_service,time)
    ,m_bNeeDraw(false)
{}

void EventDrawStrategy::Loop(const boost::system::error_code& )
{
    if(NULL != m_pApp && m_bNeeDraw)
    {
	m_pApp->Draw();
    }
    m_bNeeDraw = false;
    Start();
}
