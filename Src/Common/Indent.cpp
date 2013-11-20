#include "Common/Utils/Indent.h"
Indent cindent = Indent(4);
Indent::Indent(Int32 nShiftW)
    :m_nShiftWidth(nShiftW)
    ,m_nIndent(0)
{
    for(Int32 n = 0; n < m_nShiftWidth; ++n)
    {
	m_strShift += " ";
    }
}

std::ostream& operator<< (std::ostream& os,const Indent& ind)
{
    for(Int32 n = 0; n < ind.GetIndent(); ++n)
    {
	os<<ind.m_strShift;
    }

    return os;
}
