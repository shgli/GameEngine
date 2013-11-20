#ifndef _PIPELINE_H
#define _PIPELINE_H
#include "Common/Common.h"
#include "Graphic/Object.h"
#include "Graphic/Types.h"
class Object;
class Camera;
class Step;
class PipeLine
{
public:
    PipeLine(Camera* pCamera);
    ~PipeLine( void );

    void Init( void );

    void Reset( void );

    void SetCamera(Camera* pCamera);

    void Do(ObjectList& container);

    RenderList& GetRenderList( void );

private:

    enum StepType
    {
	PT_CULLER,
	PT_BACKFACECULLER,
	PT_CLIPPER,
	PT_SHADING,
	PT_PROJECT,
	PT_COUNT
    };
    Step*  m_pStepes[PT_COUNT];

    Camera *r_pCamera;
    //RenderList m_renderList;

};
#endif

