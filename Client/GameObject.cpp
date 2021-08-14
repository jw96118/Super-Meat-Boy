#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSpriteMgr(CSpriteMgr::GetInstance()),
	m_pSoundMgr(CSoundMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance())
{
}


CGameObject::~CGameObject()
{
}

const OBJECT_TYPE CGameObject::GetType() const
{
	return m_pType;
}
