#ifndef _CULLER_H
#define _CULLER_H
#include "Graphic/ObjectVisitor.h"
#include "Graphic/ObjectState.h"
class Camera;
class Culler
    :public Step
{
public:
    Culler(Camera* pCamera = nullptr)
        :Step(pCamera)
    {}

    void Visit(Object& obj);

};
#endif

