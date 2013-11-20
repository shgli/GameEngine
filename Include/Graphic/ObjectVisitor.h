#ifndef _OBJECTVISITOR_H
#define _OBJECTVISITOR_H
class Object;
class Camera;
class Step 
{
public:
    Step(Camera* pCamera = nullptr):r_pCamera(pCamera) {}
    virtual ~Step( void ) {}

    void SetCamera(Camera* pCamera) { r_pCamera = pCamera; }
    virtual void Reset( void ) {}
    virtual void Visit(Object& obj) = 0;
protected:
    Camera* r_pCamera;
};
#endif

