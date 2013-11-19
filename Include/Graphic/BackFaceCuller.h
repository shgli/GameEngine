#ifndef _BACKFACECULLER_H
#define _BACKFACECULLER_H
#include <vector>
#include "Graphic/ObjectVisitor.h"
#include "Graphic/ObjectState.h"

class BackFaceCuller
    :public Pass
{
public:
    BackFaceCuller( void ) {}
    void Visit(Object& obj);

private:
    void CalculateNormals(Object& obj) const;
};
#endif
 
