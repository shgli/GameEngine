#include "Graphic/LightMgr.h"
LightMgr& LightMgr::Instance( void )
{
    static LightMgr instance;
    return instance;
}

void LightMgr::Shading(const Vertex& vertex,Color& clrBase)
{
    ColorEx clrSum = Color::Black;
    for(int curLight = 0; curLight < MAX_LIGHTS; ++curLight)
    {
	Light& light = m_lights[curLight];
	if(!light.IsOn())
	{
	    continue;
	}

	switch(light.GetType())
	{
	    case LIGHT_AMBIENT:
		{
		    clrSum.r += (light.ambient.r * clrBase.r) / 256;
		    clrSum.g += (light.ambient.g * clrBase.g) / 256;
		    clrSum.b += (light.ambient.b * clrBase.b) / 256;
		} 
		break;
	    case LIGHT_INFINITE:
		{
		    Double dotValue = vertex.GetNormal().Dot(light.dir);
		    if(dotValue > 0)
		    {
			Int32 i = 128 * dotValue;
			clrSum.r += (light.diffuse.r * clrBase.r * i) / (256 * 128);
			clrSum.g += (light.diffuse.g * clrBase.g * i) / (256 * 128);
			clrSum.b += (light.diffuse.b * clrBase.b * i) / (256 * 128);
		    }
		}
		break;
	    case LIGHT_POINT:
		{
		    Vector vertex2light = light.position - vertex.GetPosition();
                    CalculateDiffuse(light,vertex,vertex2light,clrBase,clrSum);
		}
		break;
	    case LIGHT_SPOT:
		{
		    CalculateDiffuse(light,vertex,light.dir,clrBase,clrSum);
		};
		break;
	    case LIGHT_SPOT1:
		{
		    Vector vertex2light = light.position - vertex.GetPosition();
		    Double dotValue = vertex.GetNormal().Dot(vertex2light);
		    if(dotValue > 0)
		    {
			Double dist = vertex2light.Length();
			Double atten = light.cons + (light.quadric * dist + light.linear) * dist;
			Double dp = Pow(dotValue / dist,light.exponent);
			Int32 i = 128 * dp / atten;
			clrSum.r += (light.diffuse.r * clrBase.r * i) / (256 * 128);
			clrSum.g += (light.diffuse.g * clrBase.g * i) / (256 * 128);
			clrSum.b += (light.diffuse.b * clrBase.b * i) / (256 * 128);
		    }
		}
		break;
	    default:
		break;
    	} //switch
    } //for lights

    clrBase.r = clrSum.r > 256 ? 256 : clrSum.r;
    clrBase.g = clrSum.g > 256 ? 256 : clrSum.g;
    clrBase.b = clrSum.b > 256 ? 256 : clrSum.b;
}

void LightMgr::CalculateDiffuse(const Light& light,const Vertex& vertex,const Vector& vertex2light,Color clrBase,ColorEx& clrSum)
{
    Double dotValue = vertex.GetNormal().Dot(vertex2light);
    if(dotValue > 0)
    {
	Double dist = vertex2light.Length();
	Double atten = light.cons + (light.quadric * dist + light.linear) * dist;
	Int32 i = 128 * dotValue / (dist * atten);
	clrSum.r += (light.diffuse.r * clrBase.r * i) / (256 * 128);
	clrSum.g += (light.diffuse.g * clrBase.g * i) / (256 * 128);
	clrSum.b += (light.diffuse.b * clrBase.b * i) / (256 * 128);
    }
}

