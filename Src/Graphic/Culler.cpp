#include "Graphic/Culler.h"
#include "Graphic/Object.h"
#include "Graphic/Camera.h"
void Culler::Visit(Object& obj) 
{
    switch(obj.GetCullMode())
    {
	case CM_NEVER:
	    break;
	case CM_ALAWYS:
	    obj.AddState(OS_CULLED);
	    break;
	default:
	    {
		Point sphereWorld = r_pCamera->GetCameraMatrix() * obj.GetWorldPosition();
		Real radius = obj.GetBound().radius;
                if(obj.GetCullMode() & CM_NEAR)
		{
	            if((sphereWorld.z + radius) < r_pCamera->GetNear())
		    {
			obj.AddState(OS_CULLED);
			break;
		    }
		}	    

		if(obj.GetCullMode() & CM_FAR)
		{
                    if((sphereWorld.z - radius) > r_pCamera->GetFar())
		    {
			obj.AddState(OS_CULLED);
			break;
		    }
		}

		bool bCulled = false;
		if(obj.GetCullMode() & CM_LEFT)
		{
		    bCulled = r_pCamera->GetLeftPlane().Test(sphereWorld) > radius;
		}

		if(!bCulled && (obj.GetCullMode() & CM_RIGHT))
		{
		    bCulled = r_pCamera->GetRightPlane().Test(sphereWorld) > radius;
		}

		if(!bCulled && (obj.GetCullMode() & CM_TOP))
		{
		    bCulled = r_pCamera->GetTopPlane().Test(sphereWorld) > radius;
		}

		if(!bCulled && (obj.GetCullMode() & CM_BOTTOM))
		{
		    bCulled = r_pCamera->GetBottomPlane().Test(sphereWorld) > radius;
		}

		if(bCulled)
		{
		    obj.AddState(OS_CULLED);
		}
	    } //switch-default
    } //switch

#ifdef _DEBUG
    if(obj.IsCulled())
    {
	std::cout<<"Object "<<obj.GetName()<<" been culled"<<std::endl;
    }
#endif
}

