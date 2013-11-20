#include <cstring>
#include "Graphic/Interpolator.h"
#include "Graphic/Types.h"
#if _USE_BRESHAM_

Interpolator::Interpolator()
{
    for(Int32 idx = 0; idx < ITT_COUNT; ++idx)
    {
        m_itps[idx] = new BreshamLine();
    }
}

Interpolator::~Interpolator()
{
    for(Int32 idx = 0; idx < ITT_COUNT; ++idx)
    {
        delete m_itps[idx];
    }

}

Interpolator::Interpolator(Int32 from,Int32 to
	     ,const ScreenVertex& start
	     ,const ScreenVertex& end)
{
    for(Int32 idx = 0; idx < ITT_COUNT; ++idx)
    {
        m_itps[idx] = new BreshamLine();
    }

    SetScreenVertex(from,to,start,end);
}

void Interpolator::SetScreenVertex(Int32 from,Int32 to
		,const ScreenVertex& start
		,const ScreenVertex& end)
{
    m_item = start;
    std::memset(m_bNeedItp,0,sizeof(m_bNeedItp));
    if(start.x != end.x)
    {
	m_bNeedItp[ITT_X] = true;
	m_itps[ITT_X]->Init(from,to,start.x,end.x);
    }

    if(start.z != end.z)
    {
	m_bNeedItp[ITT_Z] = true;
	m_itps[ITT_Z]->Init(from,to,start.z.AsInt32(),end.z.AsInt32());
    }

    if(start.clr.AsInt32() != end.clr.AsInt32())
    {
	if(start.clr.r != end.clr.r)
	{
	    m_bNeedItp[ITT_RED] = true;
	    m_itps[ITT_RED]->Init(from,to,start.clr.r,end.clr.r);
	}

   	if(start.clr.g != end.clr.g)
	{
	    m_bNeedItp[ITT_GREEN] = true;
	    m_itps[ITT_GREEN]->Init(from,to,start.clr.g,end.clr.g);
	}

 	if(start.clr.b != end.clr.b)
	{
	    m_bNeedItp[ITT_BLUE] = true;
	    m_itps[ITT_BLUE]->Init(from,to,start.clr.b,end.clr.b);
	}
    }

    if(start.t != end.t)
    {
	m_bNeedItp[ITT_TTEXT] = true;
	m_itps[ITT_TTEXT]->Init(from,to,start.t.AsInt32(),end.t.AsInt32());
    }	

    if(start.s != end.s)
    {
	m_bNeedItp[ITT_STEXT] = true;
	m_itps[ITT_STEXT]->Init(from,to,start.s.AsInt32(),end.s.AsInt32());
    }

    if(start.t1 != end.t1)
    {
	m_bNeedItp[ITT_TTEXT1] = true;
	m_itps[ITT_TTEXT1]->Init(from,to,start.t1.AsInt32(),end.t1.AsInt32());
    }	

    if(start.s1 != end.s1)
    {
	m_bNeedItp[ITT_STEXT1] = true;
	m_itps[ITT_STEXT1]->Init(from,to,start.s1.AsInt32(),end.s.AsInt32());
    }
}

void Interpolator::ReStart( void )
{
    for(Int32 idx = 0; idx < ITT_COUNT; ++idx)
    {
	if(m_bNeedItp[idx])
	{
	    m_itps[idx]->ReStart();
	}
    }
}

ScreenVertex& Interpolator::Next( void )
{
    if(m_bNeedItp[ITT_X])
    {
	m_item.x = m_itps[ITT_X]->Next();
    }

    //if(m_bNeedItp[ITT_Y])
    //{
    //    m_item.x = m_itps[ITT_POS]->Next();
    //}
    if(m_bNeedItp[ITT_Z])
    {
	m_item.z = m_itps[ITT_Z]->Next();
    }
    if(m_bNeedItp[ITT_RED])
    {
	m_item.clr.r = m_itps[ITT_RED]->Next();
    }
    if(m_bNeedItp[ITT_GREEN])
    {
	m_item.clr.g = m_itps[ITT_GREEN]->Next();
    }
    if(m_bNeedItp[ITT_BLUE])
    {
	m_item.clr.b = m_itps[ITT_BLUE]->Next();
    }
    if(m_bNeedItp[ITT_TTEXT])
    {
	m_item.t = m_itps[ITT_TTEXT1]->Next();
    }
    if(m_bNeedItp[ITT_STEXT])
    {
	m_item.s = m_itps[ITT_STEXT1]->Next();
    }
    if(m_bNeedItp[ITT_TTEXT1])
    {
	m_item.t1 = m_itps[ITT_TTEXT1]->Next();
    }
    if(m_bNeedItp[ITT_STEXT1])
    {
	m_item.s1 = m_itps[ITT_STEXT1]->Next();
    }
    return m_item;
}
#endif

