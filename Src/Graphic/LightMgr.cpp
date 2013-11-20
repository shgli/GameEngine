#include "Graphic/LightMgr.h"

void Light::CalculateAmbient(VertexLightAttr& v)
{
    v.clr += m_clrAmbient * v.material->GetAmbient();
}

void Light::CalculateDiffuse(VertexLightAttr& v)
{
    Double dotValue = v.normal->Dot(m_vextex2Light);
    if(dotValue > 0)
    {
	v.clr += dotValue * m_clrDiffuse * v.material->GetDiffuse();
    }
}

void Light::CalculateSpecular(VertexLightAttr& v)
{
    Vector halfWay = m_vextex2Light;
    halfWay += v.viewDir;

    Double dotValue = v.normal->Dot(halfWay);
    if(dotValue > 0)
    {
	Double dp = Pow(dotValue / halfWay.Length(),v.material->GetShiness());
	v.clr += dp * m_clrSpecular * v.material->GetSpecular();
    }
}

void Light::CalcHelpVariables(VertexLightAttr& v)
{
    m_vextex2Light = m_position - *(v.position);
    m_dist = m_vextex2Light.Length();
    m_vextex2Light *= 1/ m_dist;
}

void Light::Shading(VertexLightAttr& v)
{
    switch(m_eType)
    {
        case LIGHT_GLOBAL_AMBIENT:
	    {
		CalculateAmbient(v);
	    }
	    break;
	case LIGHT_INFINITE:
	    {
                CalcHelpVariables(v);
		CalculateAmbient(v);
		CalculateDiffuse(v);
	    }
	    break;
	case LIGHT_POINT:
	    {
                CalcHelpVariables(v);
	        Double atten = 1 / (m_dConstant + (m_dQuadric * + m_dLinear) * m_dist);
		CalculateAmbient(v);
		CalculateDiffuse(v);
		CalculateSpecular(v);

		v.clr *= atten;
	    }
	    break;
	case LIGHT_SPOT:
	    {
               CalcHelpVariables(v);
               Double spotValue = m_vextex2Light.Dot(m_dirSpot);
	       if(spotValue < 0)
	       {
		   Double atten = Pow(-spotValue,m_nExponent) / (m_dConstant + (m_dQuadric * + m_dLinear) * m_dist);
        	   CalculateAmbient(v);
		   CalculateDiffuse(v);
		   CalculateSpecular(v);

		   v.clr *= atten;
	       }
	    }
	    break;
	default:
	    break;
    }
}

//============================LightMgr================================
LightMgr& LightMgr::Instance( void )
{
    static LightMgr instance;
    return instance;
}

void LightMgr::Shading(VertexLightAttr& v)
{
    for(int curLight = 0; curLight < MAX_LIGHTS; ++curLight)
    {
	Light& light = m_lights[curLight];
	if(!light.IsOn())
	{
	    continue;
	}

	light.Shading(v);
    } //for lights
}

void LightMgr::Shading(VertexIndex& vertex)
{
    VertexLightAttr v;
    Shading(v);
}

