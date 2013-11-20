#ifndef _RENDERTRI_H
#define _RENDERTRI_H
#include "Graphic/Types.h"
#include "Graphic/ObjectState.h"
#include "Graphic/Interpolator.h"
class Canvas;
class Texture;
class Interpolator;
class Vertex;
class Material;
class RenderTri
{
public:

    RenderTri();
    //return false if not an triangle
    inline void SetShadingMode(ShadingMode mode) { m_shaderMode = mode; }
    inline void SetMaterial(Material* pMaterial) { r_pMaterial = pMaterial; }
    void Render(Canvas& canvas);
    void SetVertices(const Vertex& v0,const Vertex& v1,const Vertex& v2);

    void SetVertex(const Vertex& v,Int32 nIdx);
    void SetTexture(Texture* pTexture) { r_pTexture = pTexture; }
private:
    //help functions

    bool Sort( void );

    inline int VertexLessThan(int i0,int i1) const
    {
        return (m_fragment[i0].y < m_fragment[i1].y) || ((m_fragment[i0].y == m_fragment[i1].y) && (m_fragment[i0].x < m_fragment[i1].x));
    }

    void RenderLine(const ScreenVertex&,const ScreenVertex&,Canvas& canvas);


    void RenderLine(Canvas& canvas,const ScreenVertex& start,const ScreenVertex& end,int nY);
private:

    static const int ITEM_COUNT = 3;
    ScreenVertex m_fragment[ITEM_COUNT];
    Material* r_pMaterial;
    Texture* r_pTexture;
    ShadingMode m_shaderMode;

    UInt32 m_iP0,m_iP1,m_iP2;

    enum ITPLATOR
    {
        P02P1 = 0,
        P02P2 = 1,
        P12P2 = 2
    };
    Interpolator m_interpolator[ITEM_COUNT]; 
    Interpolator m_lineInter;
};
#endif

