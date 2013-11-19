#include <cmath>
#include "Common/Numeric/Numeric.h"

BitsView GetBitsView(uint64_t v)
{
    BitsView ret;
    size_t nPos = BitsView::SIZE_OF_BITS - 1;
    while(v)
    {
        size_t res = v % 2;
	if(0 != res)
	{
	    ret.Set(nPos); 
	}
	v /= 2;
	nPos -= 1;
    }

    return ret;

}

