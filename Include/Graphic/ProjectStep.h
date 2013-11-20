#ifndef _PROJECTPASS_H
#define  _PROJECTPASS_H
#include <Common/Common.h>
#include "Graphic/ObjectVisitor.h"
#include "Graphic/Types.h"

class VertexIndex;
class ProjectStep
    :public Step
{
public:
    virtual void Visit(Object& obj);

    void Reset( void ) { m_vRendLists.clear(); }
    RenderList& GetRenderList( void ) { return m_vRendLists; }
private:
    virtual void Process(VertexArray& localBuf,VertexArray& globalBuf,Int32 p);
    void ProcessPosition(const VertexIndex& idx,VertexArray& buf);

    RenderList m_vRendLists;
};
#endif

