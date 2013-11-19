#ifndef _SERVICE_H
#define _SERVICE_H
#include <boost/asio.hpp>
class Service
{
public:
    static Service& Instance();

    boost::asio::io_service& GetIoService( void ) { return m_ioService; }

    void Run( void );
private:
    Service( void ):m_loopTimer(m_ioService){}
    Service(const Service&);
    Service& operator = (const Service&);

    void LoopTimer(const boost::system::error_code& /*e*/);
    void ThreadFunc( void );

    //data members
    boost::asio::io_service m_ioService;
    boost::asio::deadline_timer m_loopTimer;

};
#endif

