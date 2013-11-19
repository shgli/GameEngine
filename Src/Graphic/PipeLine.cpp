#include "Graphic/PipeLine.h"
#include "Graphic/BackFaceCuller.h"
#include "Graphic/LightPass.h"
#include "Graphic/ProjectPass.h"
#include "Graphic/Clipper.h"
#include "Graphic/Object.h"
#include "Graphic/Camera.h"
PipeLine::PipeLine(Camera* camera)
    :r_pCamera(camera)
{
}

PipeLine::~PipeLine( void )
{
    for(Int32 nIdx = 0; nIdx < PT_COUNT; ++nIdx)
    {
        delete m_pPasses[nIdx];
    }
}

void PipeLine::Init( void )
{
    m_pPasses[PT_CULLER] = new Culler();
    m_pPasses[PT_BACKFACECULLER] = new BackFaceCuller();
    m_pPasses[PT_CLIPPER] = new Clipper();
    m_pPasses[PT_SHADING] = new LightPass();
    m_pPasses[PT_PROJECT] = new ProjectPass();

    if(nullptr != r_pCamera)
    {
	SetCamera(r_pCamera);
    }
}

RenderList& PipeLine::GetRenderList( void )
{
    return static_cast<ProjectPass*>(m_pPasses[PT_PROJECT])->GetRenderList();
}

void PipeLine::Reset( void )
{
    m_pPasses[PT_CULLER]->Reset();
    m_pPasses[PT_BACKFACECULLER]->Reset();
    m_pPasses[PT_CLIPPER]->Reset();
    m_pPasses[PT_SHADING]->Reset();
    m_pPasses[PT_PROJECT]->Reset();
}

void PipeLine::SetCamera(Camera* pCamera)
{
    r_pCamera = pCamera;
    for(Int32 nIdx = 0; nIdx < PT_COUNT; ++nIdx)
    {
        m_pPasses[nIdx]->SetCamera(pCamera);
    }
}

void PipeLine::Do(ObjectList& container)
{
    //if(nullptr != container)
    {
#ifdef _DEBUG
        SAVE_INDENT(cindent);
	cindent.Shift(1);
        std::cout<<"Camera "<<r_pCamera->GetCameraMatrix()<<std::endl;
#endif

        for(auto pObj : container)
        {

	    try
	    {
		pObj->Update(r_pCamera->GetCameraMatrix()); //Translate to camera cooridinate system
		pObj->CalculateBound();
		pObj->Accept(m_pPasses[PT_CULLER]);

		if(!pObj->HasState(OS_CULLED))
		{
		    pObj->Accept(m_pPasses[PT_BACKFACECULLER]);
		    pObj->Accept(m_pPasses[PT_CLIPPER]);
		    pObj->Accept(m_pPasses[PT_SHADING]);
		    pObj->Accept(m_pPasses[PT_PROJECT]);
#ifdef _DEBUG
                    std::cout<<*pObj<<std::endl;
#endif
                }
	    }
#if 0 
            catch(std::exception& ex)
	    {
                std::cout<<ex.what()<<std::endl;
	    }
#else
            catch(...)
            {}
#endif
	}
    }
}
