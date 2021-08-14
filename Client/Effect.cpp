#include "stdafx.h"
#include "Effect.h"
#include "ScrollMgr.h"
#include "Player.h"
CEffect::CEffect() : m_pObjectMgr(CObjectMgr::GetInstance())
{
}

CEffect::~CEffect()
{
	Release();
}

int CEffect::Update()
{
	if (m_bEnable)
	{
		D3DXVECTOR3 tempVec;
		switch (m_RenderType)
		{
		case PLAYER_WALK:
			m_MaxFrame = 2;
			break;
		case PLAYER_DASH:
			m_MaxFrame = 4;
			break;
		case PLAYER_JUMP:
			m_MaxFrame = 4;
			break;
		case PLAYER_START:
			m_MaxFrame = 9;
			break;
		case PLAYER_DEAD:
			m_MaxFrame = 9;
		//	tempVec = { m_tInfo.vPos.x -WINCX * 0.5f + rand() % 3 - 1, m_tInfo.vPos.y - WINCY * 0.5f + rand() % 3 -1,0.f };
			CScrollMgr::Vibration();
			break;
		case PLAYER_JUMP_WALL:
			m_MaxFrame = 4;
			break;
		case PLAYER_LAND:
			m_MaxFrame = 4;
			break;
		}


		m_NowFrame += m_MaxFrame * m_pTimeMgr->GetDelta() * 2.f;
		if (m_MaxFrame <= m_NowFrame)
		{
			m_NowFrame = 0.f;
			m_MaxFrame = 0.f;
			m_bEnable = false;
			if (m_RenderType == PLAYER_DEAD)
			{
				if (!dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->GetReplay())
					dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->CreateStartEffect();
			}
			else if (m_RenderType == PLAYER_START)
			{
				m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create(m_tInfo.vPos));
			}
		}


	}
	return 0;
}

void CEffect::LateUpdate()
{
	if (m_bEnable)
	{
		D3DXMATRIX matScale, matTrans;
		switch (m_RenderType)
		{
		case PLAYER_WALK:
			break;
		case PLAYER_DASH:
			break;
		case PLAYER_JUMP:
			break;
		}

		D3DXMatrixScaling(&matScale,
			m_tInfo.vSize.x,
			m_tInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수

		m_tInfo.matWorld = matScale * matTrans;
	}
}

void CEffect::Render()
{
	if (m_bEnable)
	{
		const TEX_INFO* pTexInfo = nullptr;
		switch (m_RenderType)
		{
		case PLAYER_WALK:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerWalk", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_DASH:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerRun", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_JUMP:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerJump", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_START:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerStart", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_DEAD:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerDead", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_JUMP_WALL:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerWallJump", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		case PLAYER_LAND:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Effect", L"PlayerLand", m_NowFrame);
			NULL_CHECK(pTexInfo);
			break;
		}
		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CEffect::LineRender()
{
}

HRESULT CEffect::Initialize()
{
	m_bEnable = false;
	m_NowFrame = 0;
	m_MaxFrame = 0;
	return S_OK;
}

void CEffect::Release()
{
}

CEffect * CEffect::Create()
{
	CEffect* pInstance = new CEffect;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

const bool & CEffect::GetEnable() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bEnable;
}

void CEffect::SetEnable(bool flag)
{
	m_bEnable = flag;
}

void CEffect::SetInfo(D3DXVECTOR3 & vPos, D3DXVECTOR3 & vSize, EFFECT_TYPE RenderType)
{
	m_tInfo.vPos = vPos;
	m_tInfo.vSize = vSize;
	m_RenderType = RenderType;
}
