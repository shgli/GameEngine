#ifndef _MOUSEEVENT_HPP
#define _MOUSEEVENT_HPP
/*+==========================================================================
* Copyright (c) 2012 FengGe(CN), Inc
* All rights reserved
* This program is UNPUBLISHED PROPRIETARY property of TeleNav.
* Only for internal distribution.
* 
* FileName: MouseEvent.h
* 
* Purpose:  The class provides the implementation for the Pointer stragegy
*
* Author:Li Shugan(li_shugan@126.com)
* Since	vim7.3
==========================================================================+*/
#include <boost/asio.hpp>
#include "Common/Common.h"
//constant.
static const int LEFT_ARROW = 0x0001;
static const int RIGHT_ARROW = 0x0002;
static const int UP_ARROW = 0x0004;
static const int DOWN_ARROW = 0x0008;
static const int CHAR_KEY = 0x000c;

enum KeyState
{
    EKS_DOWN,
    EKS_UP
};

static const size_t g_nHoldingThreshold = 1000;  //1 sec
static const size_t g_nHoldingDistance = 101;	  //2 pixel
static const size_t g_nTapTimeThreshold   = 300;	  //300 ms
static const size_t g_nFlickTimeDurate	= 30; //the time duratation of filck

enum MouseEvent
{
    LButtonDown
    ,LButtonMove
    ,LButtonUp
    ,RButtonDown
    ,RButtonMove
    ,RButtonUp
};

enum EvtState
{
    ESTATE_START,
    ESTATE_ONGOING,
    ESTATE_END,
};

//user pointer event type
enum  EMannerType
{
    ENone,
    ETap,
    EMoving,
    EHolding,
    EDoubleTap
}; 

class MouseEventInfo
{
public:
    MouseEventInfo():
        m_nOccurX(-1024)
        ,m_nOccurY(-1024)
        ,nOccurTime(-1){}

    MouseEventInfo(Int16 x,Int16 y,UInt32 nTime):
        m_nOccurX(x)
        ,m_nOccurY(y)
        ,nOccurTime(nTime){}

public:
    Int16 DistSqure(const MouseEventInfo& rhs)
    {
        return	(rhs.m_nOccurX - m_nOccurX) * (rhs.m_nOccurX - m_nOccurX)  + 
        (rhs.m_nOccurY - m_nOccurY) * (rhs.m_nOccurY - m_nOccurY);
    }

    UInt32 TimeSpace(const MouseEventInfo& rhs)
    {
        return rhs.nOccurTime - nOccurTime > 0 ? rhs.nOccurTime - nOccurTime : nOccurTime - rhs.nOccurTime;
    }

    void    Reset()
    {
        nOccurTime = m_nOccurX = m_nOccurY = -1024;
    }

    Int16		m_nOccurX;
    Int16		m_nOccurY;
    Int64               nOccurTime;
};

class   MouseEventAssert
{  
public:
    MouseEventAssert();
    EMannerType GetMannerType()const{return m_eMannerType;}
    EMannerType AssertPointerEvent(MouseEvent event, Int16 x, Int16 y);
    const MouseEventInfo&    GetPressInfo()const{return m_infoPress;}
    const MouseEventInfo&    GetMoveInfo()const{return m_infoMove;}
    const MouseEventInfo&    GetReleaseInfo()const{return m_infoRelease;}

private:
    void    Reset()
    {
        m_eMannerType = ENone;
        m_nPrevTapTime = -1024;
        m_infoPress.Reset();
        m_infoMove.Reset();
        m_infoRelease.Reset();
    }
    EMannerType m_eMannerType;
    Int32             m_nPrevTapTime;
    MouseEventInfo    m_infoPress;
    MouseEventInfo    m_infoMove;
    MouseEventInfo    m_infoRelease;
};

class FlickInfo
{
    public:
    Int16 nDistFlickHor;	//the total horizontal distance of flick 
    Int16 nDistFlickVer;	//the total vertical distance of flick 

    Int16 nDistCurFlickHor;//the current horizontal distance of flick 
    Int16 nDistCurFlickVer;//the current vertical distance of flick 

    Int16 nRestCount;
    Int16 nTotalCount;
    struct 
    {
        Int16 x,y;
    }nCurPos;		//current location 
};

class MouseEventHandler
{
public:
    virtual bool HandlerTap(Int32 x,Int16 y,UInt32 dwParam){return false;};
    virtual bool HandlerDoubleTap(Int16 x,UInt16 y,UInt32 dwParam){return false;};
    virtual bool HandlerHolding(Int16 x,UInt16 y,UInt32 dwParam){return false;};
    virtual bool HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy){return false;};
    virtual bool HandlerFlicking(EvtState nState,Int16 x,Int16 y,Int16 nDx,Int16 nDy,Int16 nCurDx,Int16 nCurDy){return false;};
};

class MouseEventStrategy
{
public:
    enum HandlerType
    {
        ETYPE_TAP = 0x0001,
        ETYPE_DOUBLE_TAP = 0x0002,
        ETYPE_MOVING = 0x0004,
        ETYPE_FLICKING = 0x0008,
        ETYPE_HOLDING = 0x0010
    };


    MouseEventStrategy(boost::asio::io_service& io_service
                       ,Int handlerType = 0x001F);

    virtual ~MouseEventStrategy();

public:
    void CancelPointerEvent( void );

    virtual bool OnMouseEvent(MouseEvent event, Int x, Int y,Int32 dwParam);

    FlickInfo* GetFlicInfo( )const{return m_flickInfo;}
    
    void SetEventHandler(MouseEventHandler *pHandler) { r_pHandler = pHandler; }
private:
    void Flicking(const boost::system::error_code& );
    void UserTap(const boost::system::error_code& );
    void UserHolding(const boost::system::error_code& );

    FlickInfo* m_flickInfo;
    MouseEventAssert m_evtAssert;
    size_t m_handlerType;
    MouseEventHandler *r_pHandler;
    boost::asio::deadline_timer m_tapTimer;
    boost::asio::deadline_timer m_flickTimer;
    boost::asio::deadline_timer m_holdingTimer;
};
#endif

