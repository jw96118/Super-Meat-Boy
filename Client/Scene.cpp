#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pSpriteMgr(CSpriteMgr::GetInstance()),
	m_pSoundMgr(CSoundMgr::GetInstance()), m_pObjectMgr(CObjectMgr::GetInstance())
{
}


CScene::~CScene()
{
}
