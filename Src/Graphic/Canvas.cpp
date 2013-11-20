/**
* @file Canvas.cpp
* @brief 
* @author Li Shugan
* @date 2011-10-15 23:02:34
* @version 1.0
* copyright:fenge.com
* email: li_shugan@126.com
* company: fenge
* All rights reserved.
* modification:
* Write modifications here.
*/

#include <vector>
#include "Graphic/Canvas.h"
#include "Graphic/BreshamLine.h"
#include "Graphic/Texture.h"

Canvas::Canvas(Bitmap* pDestination)
:m_pDestination(pDestination)
,m_bkClr(0x00FF0000)
,m_rcClip(0,0,m_pDestination->GetWidth(),m_pDestination->GetHeight())
{
    assert(nullptr != m_pDestination);
    m_pZBuffer = new Fix28[m_pDestination->GetWidth() * m_pDestination->GetHeight()];
}

bool Canvas::SolveInequality(double& low,double& up,double delta,double q)
{
    if(0.0 == delta)
    {
        if(q < 0.0) return false;

        return true;
    }
    else if(delta > 0)
    {
        double t = q / delta;
        if( t < up) up = t;
    }
    else
    {
        double t = q / delta;
        if( t > low ) low = t;
    }

    if(up < low) return false;
    return true;
}

bool Canvas::ClipLine(int& nX0,int& nY0,int& nX1,int& nY1)
{
    double low = 0.0,up = 1.0;

    //the x coordinate should statisfy that: 
    //  XL <= X0 + t(X1 - X0) <=XR( 0<=t<=1)
    double deltaX = nX1 - nX0;
    double q = m_rcClip.x + m_rcClip.dx - nX0;

    if(SolveInequality(low,up,deltaX,q))
    {
        q = nX0 - m_rcClip.x;
        if(SolveInequality(low,up,-1 * deltaX,q))
        {
            //the y coordinate should statisfy that:
            //  YB <= Y0 + t(Y1 - Y0) <=YT( 0<=t<=1)
            double deltaY = nY1 - nY0;	
            q = m_rcClip.y + m_rcClip.dy - nY0;

            if(SolveInequality(low,up,deltaY,q))
            {
                q = nY0 - m_rcClip.y;
                if(SolveInequality(low,up,-1 * deltaY,q))
                {
                    //now we should calcute the intersection
                    nX1 = nX0 + up * deltaX;
                    nY1 = nY0 + up * deltaY;
                    nX0 += low * deltaX;
                    nY0 += low * deltaY;
                    return true;
                }
            }//Y
        }
    }//X

    return false;
}

void Canvas::DrawLine(int nX0, int nY0, int nX1, int nY1)
{
    if((!m_rcClip.Test(nX0,nY0) || !m_rcClip.Test(nX1,nY1)) && !ClipLine(nX0,nY0,nX1,nY1))
    {
        return;
    }
    //starting point of line
    int nX = nX0, nY = nY0;

    //direction of line
    int nDx = nX1 - nX0, nDy = nY1 - nY0;

    //Increment or decrement depending on direction of line
    int nSx,nSy;
    if(nDx > 0){
        nSx = 1;
    }else if(nDx < 0){
        nSx = -1;
        nDx = -nDx;
    }else{
        nSx = 0;
    }

    if(nDy > 0)
    {
        nSy = 1;
    }
    else if(nDy < 0)
    {
        nSy = -1;
        nDy = -nDy;
    }
    else
    {
        nSy = 0;
    }


    int nAx = 2 * nDx,nAy = 2 * nDy;
    if(nDy <= nDx)
    {
        //single step in x-direction
        for(int nDecy = nAy - nDx;; nX += nSx,nDecy += nAy)
        {
            m_pDestination->SetPixel(nX,nY,m_bkClr);

            //take bresenham step.
            if(nX == nX1)
            {
                break;
            }
            if(nDecy >= 0)
            {
                nDecy -= nAx;
                nY += nSy;
            }
        }
    }
    else
    {
        //single step in y-direction
        for(int nDecx = nAx - nDy;; nY += nSy,nDecx += nAx)
        {
            m_pDestination->SetPixel(nX,nY,m_bkClr);

            //take bresenham step.
            if(nY == nY1)
            {
                break;
            }

            if(nDecx >= 0)
            {
                nDecx -= nAy;
                nX += nSx;
            }
        }

    }
    }

void Canvas::DrawCircle(int nXCenter,int nYCenter,int nRadius)
{
    for(int nX = 0,nY = nRadius,nDec = 3 - 2 * nRadius; nX <= nY; ++nX)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter + nX,nYCenter - nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter + nY,nYCenter + nX,m_bkClr);
        m_pDestination->SetPixel(nXCenter + nY,nYCenter - nX,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nY,nYCenter + nX,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nY,nYCenter - nX,m_bkClr);

        if(nDec >= 0)
        {
            nDec += -4 * (nY--) + 4;
        }
        nDec += 4 * nX + 6;
    }
}

void Canvas::DrawEllipse(int nXCenter,int nYCenter,int nA,int nB)
{
    int nA2 = nA * nA,nB2 = nB * nB,nFa2 = 4 * nA2;
    for(int nX = 0,nY = nB,nSigma = 2 * nB2 + nA2 * (1 - 2 * nB);nB2 * nX <= nA2 * nY;++nX)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter + nX,nYCenter - nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);

        if(nSigma >= 0)
        {
            nSigma += nFa2 * (1 - nY);
            --nY;
        }

        nSigma += nB2 * (4 * nX + 6);
    }

    int nFb2 = 4 * nB2;
    for(int nX = nA,nY = 0,nSigma = 2 * nA2 + nB2 * (1 - 2 * nA); nA2 * nY <= nB2 * nX;++nY)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter + nX,nYCenter - nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);

        if(nSigma >= 0)
        {
            nSigma += nFb2 * (1 - nX);
            --nX;
        }
        nSigma += nA2 * (4 * nY + 6);
    }
}

void Canvas::DrawEllipse(int nXCenter,int nYCenter,int nAx,int nAy,int nBx,int nBy)
{
    int64_t nAx2 = nAx * nAx,nAy2 = nAy * nAy,nBx2 = nBx * nBx,nBy2 = nBy * nBy;
    int64_t nA2 = (nAx2 + nAy2) * (nAx2 + nAy2), nB2 = (nBx2 + nBy2) * (nBx2 + nBy2);
    int64_t nQurXCoef = nAx2 * nB2 + nBx2 * nA2;
    int64_t nCrossCoef = nAx * nAy * nB2 + nBx * nBy * nA2;
    int64_t nQurYCoef = nAy2 * nB2 + nBy2 * nA2;
    int64_t nConstCoef = nA2 * nB2;

    int64_t nDx = -(nCrossCoef * nAx + nQurYCoef * nAy),nDy = nQurXCoef * nAx + nCrossCoef * nAy;
    int nX = -1 * nAx,nY = -1 * nAy;
    int64_t nSigma = 0;
    while(nDx <= 0)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);
        ++nY;
        nSigma = nQurXCoef * nX * nX + 2 * nCrossCoef * nX * nY + nQurYCoef * nY * nY - nConstCoef;

        if(nSigma < 0)
        {
            nDx -= nCrossCoef;
            nDy += nQurXCoef;
            --nX;
        }

        nDx += nQurYCoef;
        nDy -= nCrossCoef;
    }

    while(nDx <= nDy)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);
        ++nY;
        nSigma = nQurXCoef * nX * nX + 2 * nCrossCoef * nX * nY + nQurYCoef * nY * nY - nConstCoef;

        if(nSigma > 0)
        {
            nDx += nCrossCoef;
            nDy -= nQurXCoef;
            ++nX;
        }

        nDx += nQurYCoef;
        nDy -= nCrossCoef;
    }

    while(nDy >= 0)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);
        ++nX;
        nSigma = nQurXCoef * nX * nX + 2 * nCrossCoef * nX * nY + nQurYCoef * nY * nY - nConstCoef;

        if(nSigma < 0)
        {
            nDx += nQurYCoef;
            nDy -= nCrossCoef;
            ++nY;
        }

        nDx += nCrossCoef;
        nDy -= nQurXCoef;
    }

    int nAbsBx = nBx < 0 ? -nBx : nBx;
    int nAbsBy = nBy < 0 ? -nBy : nBy;
    while(nDy * nAbsBx >= -nAbsBy * nDx)
    {
        m_pDestination->SetPixel(nXCenter + nX,nYCenter + nY,m_bkClr);
        m_pDestination->SetPixel(nXCenter - nX,nYCenter - nY,m_bkClr);
        ++nX;
        nSigma = nQurXCoef * nX * nX + 2 * nCrossCoef * nX * nY + nQurYCoef * nY * nY - nConstCoef;

        if(nSigma > 0)
        {
            nDx -= nQurYCoef;
            nDy += nCrossCoef;
            --nY;
        }

        nDx += nCrossCoef;
        nDy -= nQurXCoef;
    }
    }
    Int32 Canvas::GetWidth( void ) const
    {
        if(nullptr != m_pDestination)
        {
            return m_pDestination->GetWidth();
        }

        return -1;
    }

Int32 Canvas::GetHeight( void ) const
{
    if(nullptr != m_pDestination)
    {
        return m_pDestination->GetHeight();
    }

    return -1;
}

void Canvas::Clear(Color clr)
{
    if(nullptr != m_pDestination)
    {
        m_pDestination->Clear(clr.AsInt32());
    }
}

void Canvas::ClearZBuffer( void )
{
    std::memset(m_pZBuffer,0,sizeof(Fix28) * m_pDestination->GetWidth() * m_pDestination->GetHeight());
}

void Canvas::DrawTriangle(int nX0,int nY0,int nX1,int nY1,int nX2,int nY2)
{
    if(nullptr != m_pDestination)
    {
        //std::cout<<"Draw Triangle: {("<<nX0<<","<<nY0<<"),("<<nX1<<","<<nY1<<"),("<<nX2<<","<<nY2<<")}"<<std::endl;
        DrawLine(nX0,nY0,nX1,nY1);
        DrawLine(nX1,nY1,nX2,nY2);
        DrawLine(nX2,nY2,nX0,nY0);
    }
}

Canvas::TriRenderType Canvas::SortTriVertex(int& nX0,int& nY0,int& nX1,int& nY1,int& nX2,int& nY2)
{
    if((nX0 == nX1 && nX0 == nX2)
       ||(nY0 == nY1 && nY0 == nY2))
    {
        return TRT_None;
    }

    int ntmp;
    //represet p1(nX0,nY0) p2(nX1,nY1) p3(nX2,nY2)
    //Sort p1,p2,p3 in ascending y order
    if(nY0 > nY1)
    {
        SwapEx(nX0,nX1,ntmp);
        SwapEx(nY0,nY1,ntmp);
    }

    if(nY0 > nY2)
    {
        SwapEx(nX0,nX2,ntmp);
        SwapEx(nY0,nY2,ntmp);

        SwapEx(nX1,nX2,ntmp);
        SwapEx(nY1,nY2,ntmp);
    }
    else if(nY2 < nY1)
    {
        SwapEx(nX1,nX2,ntmp);
        SwapEx(nY1,nY2,ntmp);
    }

    if(nY1 == nY2) //top
    {
        if(nX1 > nX2)
        {
            SwapEx(nX1,nX2,ntmp);
            SwapEx(nY1,nY2,ntmp);
        }

        return TRT_TOP_FLAT;
    }
    else if(nY0 == nY1)//bottom
    {
        if(nX0 > nX1)
        {
            SwapEx(nX0,nX1,ntmp);
            SwapEx(nY0,nY1,ntmp);
        }
        return TRT_BOTTOM_FLAT;
    }
    else 
    {
        return TRT_GENERIC;
    }
}

void Canvas::FillTriangle(int nX0,int nY0,int nX1,int nY1,int nX2,int nY2)
{
    if(nullptr != m_pDestination)
    {
        TriRenderType eType = SortTriVertex(nX0,nY0,nX1,nY1,nX2,nY2);

        switch(eType)
        {
            case TRT_TOP_FLAT:
            {
                BreshamLine leftLine(nY0,nY1,nX0,nX1),rightLine(nY0,nY2,nX0,nX2);
                FillTopTriangle(leftLine,rightLine,nY2);
            }
            break;
            case TRT_BOTTOM_FLAT:
            {
                BreshamLine leftLine(nY0,nY2,nX0,nX2),rightLine(nY1,nY2,nX1,nX2);
                FillBottomTriangle(leftLine,rightLine,nY2);
            }
	    break;
            case TRT_GENERIC:
            {
                int cross = (nX1 - nX0) * (nY2 - nY0) - (nX2 - nX0) * (nY1 - nY0);
                if(cross < 0)
                {
                    BreshamLine leftLine1(nY0,nY1,nX0,nX1),rightLine(nY0,nY2,nX0,nX2);
                    BreshamLine leftLine2(nY1,nY2,nX1,nX2);
                    FillTopTriangle(leftLine1,rightLine,nY1);
                    FillBottomTriangle(leftLine2,rightLine,nY2);
                }
                else
                {
                    BreshamLine leftLine(nY0,nY2,nX0,nX2),rightLine1(nY0,nY1,nX0,nX1);
                    BreshamLine rightLine2(nY1,nY2,nX1,nX2);
                    FillTopTriangle(leftLine,rightLine1,nY1);
                    FillBottomTriangle(leftLine,rightLine2,nY2);
                }
            }
	    break;
            default: //TRT_None
            break;
        } //switch
    }//if
}

void Canvas::FillTopTriangle(BreshamLine& leftLine,BreshamLine& rightLine,int nEndY)
{
    //m_pDestination->SetPixel(leftLine.GetX(),rightLine.GetX(),leftLine.GetY(),m_bkClr);
    for(int y = leftLine.GetY() + 1; y <= nEndY; ++y)
    {
        m_pDestination->DrawHLine(leftLine.Next(),rightLine.Next(),y,m_bkClr);
    }
}

void Canvas::FillBottomTriangle(BreshamLine& leftLine,BreshamLine& rightLine,int nEndY)
{
    for(int y = leftLine.GetY() + 1; y <= nEndY; ++y)
    {
        m_pDestination->DrawHLine(leftLine.Next(),rightLine.Next(),y,m_bkClr);
    }

    //m_pDestination->SetPixel(leftLine.GetX(),rightLine.GetX(),m_bkClr);
}

void Canvas::DrawRect(int nX0,int nY0,int nX1,int nY1)
{
    if(nullptr != m_pDestination)
    {
        DrawLine(nX0,nY0,nX1,nY0);
        DrawLine(nX1,nY0,nX1,nY1);
        DrawLine(nX0,nY1,nX1,nY1);
        DrawLine(nX0,nY0,nX0,nY1);
    }
}

void Canvas::FillRect(int nX0,int nY0,int nX1,int nY1)
{
    if(nullptr != m_pDestination)
    {
        int nSX0 = nX0 < nX1 ? nX0 : nX1;
        int nSX1 = nSX0 == nX0 ? nX1 : nX0;

        int nSY0 = nY0 < nY1 ? nY0 : nY1;
        int nSY1 = nSY0 == nY0 ? nY1 : nY0;

        for(int y = nSY0; y < nSY1; ++y)
        {
            //m_pDestination->DrawHLine(nSX0,nSX1,y,m_bkClr);
	    for(int x = nSX0; x < nSX1; ++x)
	    {
		m_pDestination->SetPixel(x,y,m_bkClr);
	    }
        }
    }
}

bool Canvas::PrepareDraw(Int32 nX,Int32 nY,Texture* texture)
{
    if(nY < m_rcClip.y || nY >= (m_rcClip.y + m_rcClip.dy) || nX >= (m_rcClip.x + m_rcClip.dx))
    {
        return false;
    }
    else if(nX < m_rcClip.x)
    {
	nX = m_rcClip.x;
    }

    m_nZBufferIdx = nY * m_pDestination->GetWidth() + nX;
    m_pDestination->SetRowPixel(nX,nY,Color::Black);

    return true;
}

void Canvas::DrawPixel(Int32 nX,Int32 nY,const ScreenVertex& frag,Texture* pTexture)
{
    if(nX >= m_rcClip.x && nX < (m_rcClip.x + m_rcClip.dx))
    {
        if(frag.z > m_pZBuffer[m_nZBufferIdx]) //Z test
        {
            m_bkClr = frag.GetColor();
            if(nullptr != pTexture)
            {
                m_bkClr *= pTexture->GetSample(frag.t.Div2Int(frag.z,pTexture->GetWidth())
                                          ,frag.s.Div2Int(frag.z,pTexture->GetHeight()));
            }
            m_pDestination->SetRowPixel(nX,nY,m_bkClr,false);
            //m_pZBuffer[m_nZBufferIdx] = frag.z;
        }
        ++m_nZBufferIdx;
    }
}

void Canvas::DrawHLine(int nX0,int nX1,int nY,Color clr)
{
    m_pDestination->DrawHLine(nX0,nX1,nY,clr.AsInt32());
}

