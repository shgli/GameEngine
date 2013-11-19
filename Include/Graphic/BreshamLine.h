#ifndef _BRESHAMLINE_H
#define _BRESHAMLINE_H

class BreshamLine
{
public:
    BreshamLine( void ) {}
    BreshamLine(int nY0,int nY1,int nX0,int nX1);
    void Init(int nY0,int nY1,int nX0,int nX1);

    int ReStart( void );
    int  Next( void );

    inline int GetX( void ) const { return m_nX; }
    inline int GetY( void ) const { return m_nY; }

    inline int GetStartX( void ) const { return m_nX0; }
    inline int GetStartY( void ) const { return m_nY0; }

    inline int GetEndX( void ) const { return m_nX1; }
    inline int GetEndY( void ) const { return m_nY1; }
private:
    int m_nX0,m_nY0,m_nX1,m_nY1;
    int m_nDeltaX,m_nDeltaY;
    int m_nDeltaX2,m_nDeltaY2;
    int m_nStepX,m_nStepY;
    int m_nX,m_nY;
    int m_nErr;
};
#endif //_BRESHAMLINE_H

