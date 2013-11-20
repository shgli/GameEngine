#ifndef _STATUSARRAY_H
#define _STATUSARRAY_H
#include <cstring>
#include <cassert>
#include "Common/Numeric/CIntypes.h"
class StatusArray
{
public:
    StatusArray(UInt32 nTotalSize,UInt32 nNegativeSize)
    {
	assert(nTotalSize > nNegativeSize);
	m_nSize = (nTotalSize + UNIT) / UNIT;
	m_pBase = new char[nTotalSize];
        m_pStatus = m_pBase + (nNegativeSize + UNIT) / UNIT;
    }

    void Reset( void )
    {
	std::memset(m_pBase,0,m_nSize);
    }


    bool Test(Int32 nPos,Int32 nOffset)
    {
	Int32 nIdx = AdjustPos(nPos,nOffset);
	return m_pStatus[nIdx / UNIT] & Bits[BitsIndex(nIdx)];
    }

    void Set(Int32 nPos,Int32 nOffset)
    {
	Int32 nIdx = AdjustPos(nPos,nOffset);
	m_pStatus[nIdx / UNIT] |= Bits[BitsIndex(nIdx)];
    }

    void UnSet(Int32 nPos,Int32 nOffset)
    {
	Int32 nIdx = AdjustPos(nPos,nOffset);
	m_pStatus[nIdx / UNIT] &= ~Bits[BitsIndex(nIdx)];
    }

    bool TestAndSet(Int32 nPos,Int32 nOffset)
    {
        Int32 nIdx = AdjustPos(nPos,nOffset);
	bool bSet = m_pStatus[nIdx / UNIT] & Bits[BitsIndex(nIdx)];
	m_pStatus[nIdx / UNIT] |= Bits[BitsIndex(nIdx)];
        return bSet;
    }

    ~StatusArray( void )
    {
	delete[] m_pBase;
    }

private:
    inline Int32 AdjustPos(Int32 nPos,Int32 nOffset)
    {
	return nPos >= 0 ? nPos : (nPos + nOffset - UNIT);
    }

    inline Int32 BitsIndex(Int32 nPos) 
    {
        return (nPos % UNIT) + UNIT;
    }

    char* m_pBase;
    char* m_pStatus;
    UInt32 m_nSize;

    static const Int32 UNIT = 8;
    static UInt8 Bits[2 * UNIT];
};

#endif

