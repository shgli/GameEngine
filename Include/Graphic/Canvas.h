/**
 * @file Canvas.h
 * @brief 
 * @author Li Shugan
 * @date 2011-10-15 23:01:04
 * @version 1.0
 * copyright:fenge.com
 * email: li_shugan@126.com
 * company: fenge
 * All rights reserved.
 * modification:
 * Write modifications here.
 */
#ifndef _CANVAS_H
#define _CANVAS_H
#include <vector>
#include "Graphic/GraphicTypes.h"
#include "Graphic/Bitmap.h"
class Texture;
class BreshamLine;
class Canvas
{
    public:
	Canvas(Bitmap* pDestination);

        void DrawHLine(int nStartX,int nEndX,int nY,Color clr);
        
	bool PrepareDraw(Int32 nX,Int32 nY,Texture* texture);
        void DrawPixel(Int32 nX,Int32 nY,const Fragment& frag,Texture* texture);

	void DrawLine(int nStartX,int nStartY,int nEndX,int nEndY);
	void DrawCircle(int nCenterX,int nCenterY,int nRadius);
	void DrawEllipse(int nCenterX,int nCenterY,int nA,int nB);
	void DrawEllipse(int nCenterX,int nCenterY,int nAx,int nAy,int nBx,int nBy);
	void FillTriangle(int nX0,int nY0,int nX1,int nY1,int nX2,int nY2);

	void DrawTriangle(int nX0,int nY0,int nX1,int nY1,int nX2,int nY2);
	void DrawRect(int nX0,int nY0,int nX1,int nY1);
	void FillRect(int nX0,int nY0,int nX1,int nY1);

	Bitmap* GetDestination( void ) { return m_pDestination; }
	Int32 GetWidth( void ) const;
	Int32 GetHeight( void ) const;

	void Clear(Color clr);
        void ClearZBuffer( void );

	void SetColor(Color clr) { m_bkClr = clr; }

    private:
	bool ClipLine(int& nX0,int& nY0,int& nX1,int& nY1);
	bool SolveInequality(double& low,double& up,double delta,double q); //solve delta * x <= q and low <= x >= up

	enum TriRenderType
	{
	    TRT_None,
	    TRT_TOP_FLAT,
	    TRT_BOTTOM_FLAT,
	    TRT_GENERIC
	};

	TriRenderType SortTriVertex(int& nX0,int& nY0,int& nX1,int& nY1,int& nX2,int& nY2);

	void FillTopTriangle(BreshamLine& leftLine,BreshamLine& rightLine,int nEndY);
	void FillBottomTriangle(BreshamLine& leftLine,BreshamLine& rightLine,int nEndY);

	Bitmap *m_pDestination;
	Fix28 *m_pZBuffer;
	Rect2D m_rcClip;
	Color m_bkClr;
	Int32 m_nZBufferIdx;
};
#endif 
