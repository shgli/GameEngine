#ifndef _LIGHTPASS_H
#define _LIGHTPASS_H
#include "Graphic/ObjectVisitor.h"
class LightStep
    :public Step
{
public:
    virtual void Visit(Object& obj);
};
#endif

