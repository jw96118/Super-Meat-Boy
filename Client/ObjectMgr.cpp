#include "stdafx.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "Effect.h"
#include "TileObject.h"
#include "Player.h"
#include "Bandage.h"
#include "ScrollMgr.h"
IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr():m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CObjectMgr::~CObjectMgr()
{
	Release();
}

HRESULT CObjectMgr::AddObject(OBJECT_TYPE eType, CGameObject* pObject)
{
	NULL_CHECK_RETURN(pObject, E_FAIL);
	m_ObjectList[eType].push_back(pObject);

	return S_OK;
}

void CObjectMgr::CreateEffect(D3DXVECTOR3 & vPos, D3DXVECTOR3 & vSize,EFFECT_TYPE type)
{
	if (m_ObjectList[OBJECT_EFFECT].empty())
	{
		AddObject(OBJECT_EFFECT, CEffect::Create());
	}
	auto iter_begin = m_ObjectList[OBJECT_EFFECT].begin();
	for (; iter_begin != m_ObjectList[OBJECT_EFFECT].end(); iter_begin++)
	{
		if (!dynamic_cast<CEffect*>(*iter_begin)->GetEnable())
		{
			dynamic_cast<CEffect*>(*iter_begin)->SetEnable(true);
			dynamic_cast<CEffect*>(*iter_begin)->SetInfo(vPos, vSize, type);
			return;
		}
	}
	AddObject(OBJECT_EFFECT, CEffect::Create());
	dynamic_cast<CEffect*>(m_ObjectList[OBJECT_EFFECT].back())->SetInfo(vPos, vSize, type);
	dynamic_cast<CEffect*>(m_ObjectList[OBJECT_EFFECT].back())->SetEnable(true);
}

int CObjectMgr::Update()
{
	list<CGameObject*>::iterator iter_begin, iter_end;

	for(int i = 0; i < OBJECT_END; ++i)
	{
		iter_begin = m_ObjectList[i].begin();
		iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}	





	if (!m_ObjectList[OBJECT_BANDAGE].empty())
	{
		if (!m_ObjectList[OBJECT_TERRAIN].empty())
		{
			CCollisionMgr::CollisionFloor(m_ObjectList[OBJECT_PLAYER].back(), m_ObjectList[OBJECT_TERRAIN]);
			CCollisionMgr::CollisionSaw(m_ObjectList[OBJECT_PLAYER], m_ObjectList[OBJECT_TERRAIN]);
		}
		if (CCollisionMgr::CollisionBandage(m_ObjectList[OBJECT_PLAYER].back(), m_ObjectList[OBJECT_BANDAGE].back()))
		{
			if (dynamic_cast<CBandage*>(m_ObjectList[OBJECT_BANDAGE].back())->GetAlpa() <= 0)
			{
				return NEXT_STAGE;
			}
		}
	}


	if (!m_ObjectList[OBJECT_PLAYER].empty())
	{
		if (dynamic_cast<CPlayer*>(m_ObjectList[OBJECT_PLAYER].back())->GetState() != DEAD)
		{
			D3DXVECTOR3 tempScorll = dynamic_cast<CPlayer*>(m_ObjectList[OBJECT_PLAYER].back())->GetInfo().vPos;
			SetScrollPos(tempScorll);
		}
		else
		{
		}

	}
	return NO_EVENT;
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}	
	
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto pObject : m_ObjectList[i])
			pObject->Render();
	}
}

void CObjectMgr::LineRender()
{
	m_ObjectList[OBJECT_TERRAIN].back()->LineRender();
}

CGameObject* CObjectMgr::GetTileInfo()
{
	if (m_ObjectList[OBJECT_TERRAIN].empty())
		return nullptr;
	return m_ObjectList[OBJECT_TERRAIN].back();
}

CGameObject * CObjectMgr::GetPlayer()
{
	if(m_ObjectList[OBJECT_PLAYER].empty())
		return nullptr;

	return m_ObjectList[OBJECT_PLAYER].back();
}

void CObjectMgr::PlayerReplay()
{
	auto iter_begin = m_ObjectList[OBJECT_PLAYER].begin();
	for (; iter_begin != m_ObjectList[OBJECT_PLAYER].end(); iter_begin++)
	{
		dynamic_cast<CPlayer*>(*iter_begin)->SetReplay(true);
	}
	dynamic_cast<CTileObject*>(m_ObjectList[OBJECT_TERRAIN].back())->SetReaplay();
	dynamic_cast<CBandage*>(m_ObjectList[OBJECT_BANDAGE].back())->SetReplay();
}

void CObjectMgr::DeleteMeatBand()
{
	for_each(m_ObjectList[OBJECT_PLAYER].begin(), m_ObjectList[OBJECT_PLAYER].end(), SafeDelete<CGameObject*>);
	m_ObjectList[OBJECT_PLAYER].clear();
	for_each(m_ObjectList[OBJECT_BANDAGE].begin(), m_ObjectList[OBJECT_BANDAGE].end(), SafeDelete<CGameObject*>);
	m_ObjectList[OBJECT_BANDAGE].clear();
}

void CObjectMgr::InitTile(const TCHAR* pFilePath)
{
	if(!m_ObjectList[OBJECT_TERRAIN].empty())
	    dynamic_cast<CTileObject*>(m_ObjectList[OBJECT_TERRAIN].back())->Init(pFilePath);
}

void CObjectMgr::InitPos(D3DXVECTOR3 & vMeatPos, D3DXVECTOR3 & vBandPos)
{
	//if (!m_ObjectList[OBJECT_PLAYER].empty())
	//	dynamic_cast<CPlayer*>(m_ObjectList[OBJECT_PLAYER].back())->SetPosFirst(vMeatPos);
	//if (!m_ObjectList[OBJECT_BANDAGE].empty())
	//	dynamic_cast<CBandage*>(m_ObjectList[OBJECT_BANDAGE].back())->SetPos(vBandPos);
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

void CObjectMgr::SetScrollPos(D3DXVECTOR3 vPos)
{
	//½ºÅ©·Ñ
	D3DXVECTOR3 tempPos = {};
	if (vPos.x >= CScrollMgr::GetScrollPos().x + WINCX - 500.f)
	{
		tempPos = { vPos.x + 500.f - WINCX,CScrollMgr::GetScrollPos().y,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.x <= CScrollMgr::GetScrollPos().x + 500.f)
	{
		tempPos = { vPos.x - 500.f,CScrollMgr::GetScrollPos().y,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.y <= CScrollMgr::GetScrollPos().y + 300.f)
	{
		tempPos = { CScrollMgr::GetScrollPos().x,vPos.y - 300.f,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.y >= CScrollMgr::GetScrollPos().y + WINCY - 300.f)
	{
		tempPos = { CScrollMgr::GetScrollPos().x,vPos.y - WINCY + 300.f,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
}
