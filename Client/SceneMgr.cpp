#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"
#include "StageSelect.h"
#include "ScrollMgr.h"
IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_pDeviceMgr(CDeviceMgr::GetInstance()), m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance())
{
	for (int i = 0; i < SCENE_END; i++)
	{
		m_bTextureLoad[i] = false;
	}
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENE_TYPE eCurType, SCENE_TYPE eNextType, int Stage)
{
	if (!m_bSawLoad)
	{
		m_tInfo.vPos = { 0.f,0.f,0.f };
		m_tInfo.vSize = { 0.f,0.f,0.f };
		LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
		NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

		HRESULT hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/Scene_Saw2.png",
			L"SCENE", L"SAW", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Saw Object Texture Load Failed", E_FAIL);
		m_bSawLoad = true;
	}

	m_eCurType = eCurType;
	m_eNextType = eNextType;
	m_iStage = Stage;
	m_bSceneChange = true;
	if (eCurType != eNextType)
	{
		SafeDelete(m_pScene);
		D3DXVECTOR3 tempVec = {0.f,0.f,0.f};
		CScrollMgr::SetScrollPos(tempVec);
		switch (eNextType)
		{
		case SCENE_LOGO:
			m_pScene = CLogo::Create(m_bTextureLoad[SCENE_LOGO]);
			m_bTextureLoad[SCENE_LOGO] = true;

			m_tInfo.vPos = { WINCX * 0.5f, WINCY * 0.5f ,0.f };
			break;
		case SCENE_STAGE_SELECT:
			m_pScene = CStageSelect::Create(m_bTextureLoad[SCENE_STAGE_SELECT]);
			m_bTextureLoad[SCENE_STAGE_SELECT] = true;

			m_tInfo.vPos = { WINCX * 0.5f,WINCY * 0.5f ,0.f };
			break;
		case SCENE_STAGE:
			m_pScene = CStage::Create(Stage, m_bTextureLoad[SCENE_STAGE]);
			m_bTextureLoad[SCENE_STAGE] = true;

			m_tInfo.vPos = { WINCX * 0.5f,WINCY * 0.5f ,0.f };
			cout << CScrollMgr::GetScrollPos().y << endl;
			break;
		default:
			break;
		}

		NULL_CHECK_RETURN(m_pScene, E_FAIL);
	}

	return S_OK;
}

int CSceneMgr::Update()
{
	int iEvent = m_pScene->Update();

	return iEvent;
}

void CSceneMgr::LateUpdate()
{
	
	m_pScene->LateUpdate();
	
}

void CSceneMgr::Render()
{
	
	m_pScene->Render();
	D3DXMATRIX matScale, matTrans, matRotZ;

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_Angle));

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f); // 다이렉트 이동행렬 함수

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f;
	float fCenterY = 0.f;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"SCENE", L"SAW", 0);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSceneMgr::LineRender()
{
	m_pScene->LineRender();
}

bool CSceneMgr::SceneChangeSaw(bool flag)
{
	


	if (flag)
	{
		if (m_tInfo.vSize.x > 10.f)
		{
			return true;
		}
		else
		{
			m_tInfo.vSize += {m_pTimeMgr->GetDelta()*10.f, m_pTimeMgr->GetDelta()*10.f, 0.f};
			m_Angle += m_pTimeMgr->GetDelta()*100.f;
			return false;
		}
	}
	else
	{
		if (m_tInfo.vSize.x <= 0.f)
		{
			m_tInfo.vSize = { 0.f , 0.f, 0.f };
			return true;
		}
		else
		{
			m_tInfo.vSize -= {m_pTimeMgr->GetDelta()*10.f, m_pTimeMgr->GetDelta()*10.f, 0.f};
			m_Angle -= m_pTimeMgr->GetDelta()*100.f;
			return false;
		}
	}



}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
