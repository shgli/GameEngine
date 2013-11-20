#ifndef _RENDER_H
#define _RENDER_H
#include <vector>
#include "Graphic/Triangle.h"
#include "Graphic/Types.h"
class Canvas;
class Bitmap;
class RenderTri;
class PipeLine;
class Camera;
class Object;

typedef std::vector<Object*> ObjectList;
class Render
{
public:
    Render(Canvas* pCanvas);

    void Init( void );

    void SetCamera(Camera* pCamera);

    void SetCanvas(Canvas* pCanvas) { m_pCanvas = pCanvas; }

    Canvas* GetCanvas( void ) { return m_pCanvas; }

    Bitmap* GetDestination( void );

    void Draw(ObjectList& objs);

private:
    void Draw(RenderList& rendList);

    Canvas* m_pCanvas;
    Camera* r_pCamera;
    PipeLine* m_pPipeLine;
    RenderTri *m_pTriRender;
};
#endif

