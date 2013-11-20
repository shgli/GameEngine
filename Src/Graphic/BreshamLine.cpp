#include "Common/Common.h"
#include "Graphic/BreshamLine.h"
BreshamLine::BreshamLine(int nY0,int nY1,int nX0,int nX1)
{
    Init(nY0,nY1,nX0,nX1);
}

void BreshamLine::Init(int nY0,int nY1,int nX0,int nX1)
{
    m_nX0 = nX0;
    m_nY0 = nY0;
    m_nX1 = nX1;
    m_nY1 = nY1;
    if(nY0 > nY1)
    {
	int nTmp;
        SwapEx(nX0,nX1,nTmp);
        SwapEx(nY0,nY1,nTmp);
    }

    m_nDeltaX = nX1 - nX0;
    m_nDeltaY = nY1 - nY0;

    //Increment or decrement depending on direction of line
    if(m_nDeltaX > 0)
    {
	m_nStepX = 1;
    }
    else if(m_nDeltaX < 0)
    {
	m_nStepX = -1;
	m_nDeltaX = -m_nDeltaX;
    }
    else
    {
	m_nStepX = 0;
    }

    if(m_nDeltaY > 0)
    {
	m_nStepY = 1;
    }
    else if(m_nDeltaY < 0)
    {
	//should not come here
	assert(false);
    }
    else
    {
	m_nStepY = 0;
    }
    
    m_nDeltaX2 = 2 * m_nDeltaX;
    m_nDeltaY2 = 2 * m_nDeltaY;

    ReStart();

}

int BreshamLine::ReStart( void )
{
    m_nX = m_nX0;
    m_nY = m_nY0;
    if(m_nDeltaY <= m_nDeltaX)
    {
        m_nErr = -m_nDeltaX;
    }
    else
    {
	m_nErr = -m_nDeltaY;
    }

    return m_nX;
}

int  BreshamLine::Next( void )
{
    if(m_nDeltaY <= m_nDeltaX)
    {
	//single step in x-direction
	//take bresenham step.
	do
	{
	    m_nX += m_nStepX;
	    m_nErr += m_nDeltaY2;
	}while(m_nErr < 0);

	m_nErr -= m_nDeltaX2;
	m_nY += m_nStepY;
	return m_nX;
    }
    else
    {
	//single step in y-direction
	if(m_nErr > 0)
	{
	    m_nX += m_nStepX;
	    m_nErr -= m_nDeltaY2;
	}
        m_nErr += m_nDeltaX2;
	m_nY += m_nStepY;
	return m_nX;
    }
}

