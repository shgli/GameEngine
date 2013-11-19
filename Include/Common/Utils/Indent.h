#ifndef _INDENT_H
#define _INDENT_H
#include <string>
#include <ostream>
#include "Common/Numeric/Numeric.h"
class Indent
{
public:
    Indent(Int32 nShiftW = 4);

    Int32 GetIndent( void ) const { return m_nIndent; }
    void SetIndent(Int32 nInd) {m_nIndent = nInd; }

    Indent& Shift(Int32 n = 0) {m_nIndent += n; return *this;}
    Indent& Reset(Int32 n = 0) { m_nIndent = n; return *this; }
    friend std::ostream& operator<< (std::ostream& os,const Indent& ind);
private:
    Int32 m_nShiftWidth;
    Int32 m_nIndent;
    std::string m_strShift;
};


class IndentSaver
{
public:
    IndentSaver(Indent& ind)
    :m_rIndent(ind)
    ,m_nIndent(ind.GetIndent())
    {}

    ~IndentSaver( void )
    {
        m_rIndent.SetIndent(m_nIndent);
    }
private:
    Indent& m_rIndent;
    Int32 m_nIndent;
};
extern Indent cindent;
#define SAVE_INDENT(ind)  IndentSaver __indSaver(ind)
#endif

