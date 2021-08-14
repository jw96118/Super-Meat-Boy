#include "stdafx.h"
#include "MainGame.h"

float g_fTime[SCENE_END];
bool  g_bClaer[SCENE_END];
bool    m_bDebugFlag;
CMainGame::CMainGame()
	: m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pFrameMgr(CFrameMgr::GetInstance()),
	m_pSpriteMgr(CSpriteMgr::GetInstance()),
	m_pSoundMgr(CSoundMgr::GetInstance()),
	m_iEvent(NO_EVENT)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Update()
{
	m_pTimeMgr->Update();
	m_pKeyMgr->Update();	
	m_iEvent = m_pSceneMgr->Update();
	m_pSoundMgr->SetVolume(SOUNDMGR::BGM, 0.4f);
	m_pSoundMgr->SetVolume(SOUNDMGR::TITLE, 0.4f);
	m_pSoundMgr->SetVolume(SOUNDMGR::PLAYER, 1.0f);
	if (m_pKeyMgr->KeyDown(KEY_A))
	{
		m_bDebugFlag = !m_bDebugFlag;
	}
}

void CMainGame::LateUpdate()
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	m_pSceneMgr->LateUpdate();
}

void CMainGame::Render()
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	m_pDeviceMgr->Render_Begin();

	// 앞으로 모든 오브젝트들을 이 사이에서 렌더 호출!		
	m_pSceneMgr->Render();
	m_pFrameMgr->RenderFPS();

	m_pDeviceMgr->Render_End();
	m_pDeviceMgr->Render_Line_Begin();
	m_pSceneMgr->LineRender();
	m_pDeviceMgr->Render_Line_End();
}

HRESULT CMainGame::Initialize()
{
	
	HRESULT hr = m_pDeviceMgr->InitDevice(MODE_FULL);
	FAILED_CHECK_MSG_RETURN(hr, L"InitDevice Failed", E_FAIL);	


	m_pSoundMgr->Initialize();
	for (int i = 0; i < STAGE_END; i++)
	{
		g_bClaer[i] = false;
		g_fTime[i] = false;
	}

	hr = m_pSceneMgr->SceneChange(SCENE_END, SCENE_LOGO);
	FAILED_CHECK_MSG_RETURN(hr, L"Logo Change Failed", E_FAIL);

	

	return S_OK;
}

void CMainGame::Release()
{
	m_pSoundMgr->DestroyInstance();
	m_pFrameMgr->DestroyInstance();
	m_pSceneMgr->DestroyInstance();
	m_pTimeMgr->DestroyInstance();
	m_pObjectMgr->DestroyInstance();
	m_pKeyMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pSpriteMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}



CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
