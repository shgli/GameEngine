#ifndef _PROJECTPASS_H
#define  _PROJECTPASS_H
#include <Common/Common.h>
#include "Graphic/ObjectVisitor.h"
#include "Graphic/GraphicTypes.h"

class ProjectPass
    :public Pass
{
public:
    virtual void Visit(Object& obj);

    void Reset( void ) { m_vRendLists.clear(); }
    RenderList& GetRenderList( void ) { return m_vRendLists; }
private:
    virtual void Process(VertexBuffer& localBuf,VertexBuffer& globalBuf,Int32 p);

    RenderList m_vRendLists;
};
#endif

