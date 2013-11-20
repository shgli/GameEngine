/*+==========================================================================
 * Copyright (c) 2008 FenGe(CN), Inc
 * All rights reserved
 * This program is UNPUBLISHED PROPRIETARY property of TeleNav.
 * Only for internal distribution.
 * 
 * FileName: MouseEventStrategy.cpp
 * 
 * Purpose:  The class provides the implementation for the Pointer stragegy
 *
 * Author:Li Shugan(li_shugan@126.com)
 * Since	vim7.3
 ==========================================================================+*/
#include <boost/bind.hpp>
#include "Application/MouseEvent.h"
MouseEventAssert::MouseEventAssert():
    m_eMannerType(ENone)
    ,m_nPrevTapTime(-1024)
{}

EMannerType MouseEventAssert::AssertPointerEvent(MouseEvent event, Int16 x, Int16 y)
{
    if(LButtonDown == event)
    {
	if(ETap != GetMannerType())
	{
	    Reset();
	}
	m_infoPress = MouseEventInfo(x,y,time(nullptr));
	m_infoMove  = m_infoPress;
    }
    else if(LButtonMove == event)
    {
	m_infoMove = MouseEventInfo(x,y,time(nullptr));
	if(m_eMannerType != EMoving && m_infoMove.DistSqure(m_infoPress) >= g_nHoldingDistance)
	{
	    m_eMannerType = EMoving;
	}
    }
    else
    {
	m_infoRelease = MouseEventInfo(x,y,time(nullptr));
	EMannerType eMannerType= GetMannerType();
	if(EMoving != eMannerType && m_infoRelease.DistSqure(m_infoPress) < g_nHoldingDistance)
	{
	    if(ETap == eMannerType && (m_nPrevTapTime - m_infoRelease.nOccurTime) * (m_nPrevTapTime - m_infoRelease.nOccurTime) < g_nTapTimeThreshold)
	    {
		m_eMannerType = EDoubleTap;
	    }
	    else
	    {
		m_nPrevTapTime = m_infoRelease.nOccurTime;
		m_eMannerType = ETap;
	    }
	}
    }
    return m_eMannerType;
}

MouseEventStrategy::MouseEventStrategy(boost::asio::io_service& io_service
	,Int handlerType)
    :m_flickInfo(NULL)
    ,m_handlerType((handlerType))
    ,r_pHandler(nullptr)
    ,m_tapTimer(io_service)
    ,m_flickTimer(io_service)
    ,m_holdingTimer(io_service)
{
    if(ETYPE_FLICKING & (m_handlerType))
    {
	m_flickInfo = new FlickInfo;
	m_flickInfo->nRestCount = -1;
    }
}

MouseEventStrategy::~MouseEventStrategy()
{
    delete 	m_flickInfo;
    CancelPointerEvent();
}

void MouseEventStrategy::CancelPointerEvent( void )
{
    m_tapTimer.cancel();
    m_flickTimer.cancel();
    m_holdingTimer.cancel();
}

void MouseEventStrategy::Flicking(const boost::system::error_code& )
{
    {
	FlickInfo* flickInfo = m_flickInfo;
	if (0 == flickInfo->nTotalCount)
	{
	    return ;
	}
	//compute the flick information
	Int nDx(0),nDy(0);
	EvtState evtState = ESTATE_ONGOING;
	if(0 <= (--(flickInfo->nRestCount)))
	{
	    Int nTmpCurFlickHor = flickInfo->nDistFlickHor * flickInfo->nRestCount * flickInfo->nRestCount / (flickInfo->nTotalCount * flickInfo->nTotalCount);
	    Int nTmpCurFlickVer = flickInfo->nDistFlickVer * flickInfo->nRestCount * flickInfo->nRestCount / (flickInfo->nTotalCount * flickInfo->nTotalCount);
	    nDx = flickInfo->nDistFlickHor - (flickInfo->nDistCurFlickHor + nTmpCurFlickHor);
	    nDy = flickInfo->nDistFlickVer - (flickInfo->nDistCurFlickVer + nTmpCurFlickVer);
	}

	//update flick information
	flickInfo->nDistCurFlickHor	+= nDx;
	flickInfo->nDistCurFlickVer	+= nDy;	
	flickInfo->nCurPos.x += nDx;
	flickInfo->nCurPos.y += nDy;


	//determine the state of flick.
	if(-1 == flickInfo->nRestCount)
	{
	    evtState = ESTATE_END;
	}
	else if(nDx == flickInfo->nDistCurFlickHor &&
		nDy == flickInfo->nDistCurFlickVer)
	{
	    evtState = ESTATE_START;
	}

	r_pHandler->HandlerFlicking(evtState
		,flickInfo->nCurPos.x
		,flickInfo->nCurPos.y
		,nDx,nDy
		,flickInfo->nDistCurFlickHor
		,flickInfo->nDistCurFlickVer);

	//continue flick
	if(ESTATE_END != evtState)
	{
            m_flickTimer.expires_at(m_flickTimer.expires_at() 
                                    + boost::posix_time::millisec((g_nFlickTimeDurate)));
            m_flickTimer.async_wait(boost::bind(&MouseEventStrategy::Flicking,this,boost::asio::placeholders::error));   
	}
    }
}

void MouseEventStrategy::UserTap(const boost::system::error_code& )
{
    //if this is a tap event,it should not a holding event.
    m_holdingTimer.cancel();
    r_pHandler->HandlerTap(m_evtAssert.GetReleaseInfo().m_nOccurX
            ,m_evtAssert.GetReleaseInfo().m_nOccurY,0);
}

void MouseEventStrategy::UserHolding(const boost::system::error_code& )
{
    r_pHandler->HandlerHolding(m_evtAssert.GetReleaseInfo().m_nOccurX
            ,m_evtAssert.GetReleaseInfo().m_nOccurY,0);
}

bool MouseEventStrategy::OnMouseEvent(MouseEvent event, Int x, Int y,Int32 dwParam)
{
    switch(event)
    {
	case LButtonDown:
	    {
		CancelPointerEvent();

		if(ETYPE_HOLDING & m_handlerType)
		{
                    m_holdingTimer.expires_at(m_flickTimer.expires_at() + boost::posix_time::millisec(g_nHoldingThreshold));
                    m_holdingTimer.async_wait(boost::bind(&MouseEventStrategy::UserHolding,this,boost::asio::placeholders::error));   
		}

		if(EMoving == m_evtAssert.GetMannerType())
		{
		    if(NULL != m_flickInfo && m_flickInfo->nRestCount >= 0)
		    {
			r_pHandler->HandlerFlicking(ESTATE_END
				,m_flickInfo->nCurPos.x
				,m_flickInfo->nCurPos.y
				,0,0
				,m_flickInfo->nDistCurFlickHor
				,m_flickInfo->nDistCurFlickVer);
		    }
		}
		m_evtAssert.AssertPointerEvent(event,x,y);
	    }
	    return false; //because when press,we can not guess the intent of user.

	case LButtonMove:
	    {
		MouseEventInfo prevMoveInfo = m_evtAssert.GetMoveInfo();
		EMannerType ePrevType = m_evtAssert.GetMannerType();
		if(EMoving == m_evtAssert.AssertPointerEvent(event,x,y))
		{
		    CancelPointerEvent(); //if this event is a move event,it should not holding event.
		    if(ETYPE_MOVING & m_handlerType)
		    {
			//give a chance for programmer
			if(EMoving != ePrevType)
			{
			    prevMoveInfo = m_evtAssert.GetPressInfo();
			}
			Int nDx = x - prevMoveInfo.m_nOccurX;
			Int nDy = y - prevMoveInfo.m_nOccurY;
			Int nTotalDx = x - m_evtAssert.GetPressInfo().m_nOccurX;
			Int nTotalDy = y - m_evtAssert.GetPressInfo().m_nOccurY;

			bool bStartMove = (nDx == nTotalDx) && (nDy == nTotalDy);
			bool bMoved = r_pHandler->HandlerMoving(bStartMove ? ESTATE_START : ESTATE_ONGOING,
				x,y,nDx,nDy,nTotalDx,nTotalDy);

			return bMoved;
		    }
		    return false;
		}
	    }
	    break;

	default:
	    {
		m_holdingTimer.cancel();

		EMannerType eMannerType = m_evtAssert.AssertPointerEvent(event,x,y);
		if(EDoubleTap == eMannerType)
		{
		    //1) if the last two pointer event squeue is occurs in a short time duration and distance, it a double tap event.
		    //2) if this event is a double tap,it should not a tap or holding event.
		    CancelPointerEvent();
		    if(ETYPE_DOUBLE_TAP & m_handlerType)
		    {
			return r_pHandler->HandlerDoubleTap(x,y,dwParam);
		    }
		    else 
		    {
			return false;
		    }
		}
		else if(ETap == eMannerType)
		{
		    if(ETYPE_TAP & m_handlerType)
		    {
			// if  a complete pointer sequence occurs in a short duration of time covering a small portion of the screen
			if (ETYPE_DOUBLE_TAP & m_handlerType)
			{
                            m_holdingTimer.expires_at(m_flickTimer.expires_at() + boost::posix_time::millisec(g_nTapTimeThreshold));
                            m_holdingTimer.async_wait(boost::bind(&MouseEventStrategy::UserTap,this,boost::asio::placeholders::error));   

			}
			else
			{
			    UserTap(boost::system::error_code());
			}

			return true;	//because  the programmer said that he need to handle tap event.
		    }
		    return false;
		}
		else if(EMoving == eMannerType)
		{
		    if(ETYPE_FLICKING & m_handlerType)
		    {
			//compute the flick information.
			Int nTotalMoveHor = x - m_evtAssert.GetPressInfo().m_nOccurX;
			Int nTotalMoveVer = y - m_evtAssert.GetPressInfo().m_nOccurY;
			Int64 nMoveTime = Int64(time(nullptr)) - m_evtAssert.GetPressInfo().nOccurTime;
			const Int nAcceleration = 2;
			const Int nMaxMoveCount = 16;
			const Int nMinMoveCount = 5;
			const Int nAcceUnit = 1000;
			Int32 nSqureDist = nTotalMoveHor * nTotalMoveHor + nTotalMoveVer * nTotalMoveVer;
			if ( 0 == nSqureDist ) 
			{
			    return true;
			}
			//DBGPRINTF(">>>>>>>>move dist(%d,%d)--%d,move time:%d",nTotalMoveHor,nTotalMoveVer,nSqureDist,nMoveTime);

			//m_flickInfo->nDistFlickHor = nTotalMoveHor * nSqureDist * nAcceUnit / (2 * nMoveTime * nMoveTime * nAcceleration);
			//m_flickInfo->nDistFlickVer = nTotalMoveVer * nSqureDist * nAcceUnit / (2 * nMoveTime * nMoveTime * nAcceleration);
			m_flickInfo->nRestCount 
			    = m_flickInfo->nTotalCount
			    = (Int16)(nSqureDist * nAcceUnit / (nMoveTime * nAcceleration * g_nFlickTimeDurate));

			if ( m_flickInfo->nTotalCount > 0 )
			{
			    if (m_flickInfo->nTotalCount > nMaxMoveCount)
			    {
				m_flickInfo->nRestCount = m_flickInfo->nTotalCount = nMaxMoveCount;
			    }
			    else if(m_flickInfo->nTotalCount < nMinMoveCount)
			    {
				m_flickInfo->nRestCount = m_flickInfo->nTotalCount = nMinMoveCount;
			    }
			}

			Int nTotalFlick = nAcceleration * m_flickInfo->nTotalCount
			    * (g_nFlickTimeDurate * m_flickInfo->nTotalCount) * (g_nFlickTimeDurate) / (2 * nAcceUnit);
			
			if(0 != nTotalFlick)
			{
			    m_flickInfo->nDistFlickHor =  (Int16)(nTotalFlick * nTotalMoveHor / nSqureDist);
			    m_flickInfo->nDistFlickVer =  (Int16)(nTotalFlick * nTotalMoveVer / nSqureDist);

			    m_flickInfo->nDistCurFlickHor = 0;//the current horizontal distance of flick 
			    m_flickInfo->nDistCurFlickVer = 0;//the current vertical distance of flick 

			    m_flickInfo->nCurPos.x = x;
			    m_flickInfo->nCurPos.y = y;
			    //Int nS = JMath::RootSquareSum(m_flickInfo->nDistCurFlickHor,m_flickInfo->nDistCurFlickVer);
			    //DBGPRINTF(">>>>>>>>>>>>>flick dist(%d,%d) --%d flick time:%d",m_flickInfo->nDistFlickHor,m_flickInfo->nDistFlickVer,nS,m_flickInfo->nTotalCount);
			    Flicking(boost::system::error_code());
			    return true;	//because  the programmer said that he need to handle flicking event. 
			}
			else
			{
			    m_flickInfo->nRestCount = m_flickInfo->nTotalCount = -1;
			}
		    }

		    //the position of the lastest time move should be equeal the m_curInfo->m_moveInfo.
		    Int nDx = x - m_evtAssert.GetMoveInfo().m_nOccurX;
		    Int nDy = y - m_evtAssert.GetMoveInfo().m_nOccurY;
		    Int nTotalDx = x - m_evtAssert.GetPressInfo().m_nOccurX;
		    Int nTotalDy = y - m_evtAssert.GetPressInfo().m_nOccurY;
		    return r_pHandler->HandlerMoving(ESTATE_END,x,y,nDx,nDy,nTotalDx,nTotalDy);

		}//end if(EMoving == eMannerType)
	    }//end if
	    break;
    }
    return false;
}

