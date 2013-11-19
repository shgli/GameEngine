#ifndef _LIGHTPASS_H
#define _LIGHTPASS_H
#include "Graphic/ObjectVisitor.h"
class LightPass
    :public Pass
{
public:
    virtual void Visit(Object& obj);
};
#endif

