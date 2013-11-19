#ifndef _INTERPOLATOR_HPP
#define _INTERPOLATOR_HPP
#include "Graphic/BreshamLine.h"
#include "Graphic/GraphicTypes.h"
#if _USE_BRESHAM_
class Interpolator
{
public:
    Interpolator();
    ~Interpolator();

    Interpolator(Int32 from,Int32 to
	         ,const Fragment& start
		 ,const Fragment& end);

    void SetFragment(Int32 from,Int32 to
	            ,const Fragment& start
		    ,const Fragment& end);

    void ReStart( void );

    Fragment& GetFragment( void ) { return m_item; }

    Fragment& Next( void );
private:
    enum ItpType
    {
        ITT_X,
	ITT_Y,
	ITT_Z,
        ITT_RED,
        ITT_GREEN,
        ITT_BLUE,
        ITT_TTEXT,
        ITT_STEXT,
        ITT_TTEXT1,
        ITT_STEXT1,
        ITT_COUNT
    };

    BreshamLine *m_itps[ITT_COUNT];
    bool m_bNeedItp[ITT_COUNT];
    Fragment m_item;
};
#else
class Interpolator
{
public:
    Interpolator(){}
    ~Interpolator(){}

    Interpolator(Int32 from,Int32 to
	         ,const Fragment& start
		 ,const Fragment& end);

    void SetFragment(Int32 from,Int32 to
	            ,const Fragment& start
		    ,const Fragment& end)
    {
        m_start = start;
        m_delta = end;
        m_delta -= start;
        m_delta /= (to - from);

        ReStart();
    }

    void ReStart( void ) { m_current = m_start; }

    Fragment& GetFragment( void ) { return m_current; }

    Fragment& Next( void ) {m_current += m_delta; return m_current;}
private:
    Fragment m_start,m_current,m_delta;
};
#endif
#endif

