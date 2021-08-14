#include "stdafx.h"
#include "Bandage.h"
#include "ScrollMgr.h"

CBandage::CBandage()
{
}

CBandage::~CBandage()
{
	Release();
}

int CBandage::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * 0.5f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
	}
	if (!m_bReplay)
	{
		if (m_bEnd)
		{
			if (m_fAlpa > 0)
			{
				m_fAlpa -= m_pTimeMgr->GetDelta() * 150.f;
			}
		}
		m_listAlpa.push_back(m_fAlpa);
	}
	else
	{
		if (iter_begin != m_listAlpa.end())
		{
			if (iter_begin == m_listAlpa.begin())
			{
				m_bEnd = false;
				m_fAlpa = 255.f;
			}
			m_fAlpa = (*iter_begin);
			iter_begin++;
		}
	}
	return 0;
}

void CBandage::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;
	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x ,
		m_tInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tInfo.matWorld = matScale * matTrans;
}

void CBandage::Render()
{

	const TEX_INFO* pTexInfo = nullptr;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Bandage", L"help", m_tFrame.fCurFrame);
	
	NULL_CHECK(pTexInfo);
	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB((int)m_fAlpa, 255, 255, 255));

}

void CBandage::LineRender()
{

}

HRESULT CBandage::Initialize()
{
	m_fSize = 0.5f;
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_tInfo.vSize = { m_fSize, m_fSize, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 2.f;

	const TEX_INFO* pTexInfo = nullptr;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"Bandage", L"help", m_tFrame.fCurFrame);

	NULL_CHECK_RETURN(pTexInfo, false);
	m_fColSizeX = pTexInfo->tImgInfo.Width * 0.5f * m_fSize;
	m_fColSizeY = pTexInfo->tImgInfo.Height * 0.5f * m_fSize;
	m_fAlpa = 255.f;
	m_bReplay = false;
	iter_begin = m_listAlpa.begin();
	return S_OK;
}

void CBandage::Release()
{
	m_listAlpa.clear();
}

CBandage * CBandage::Create(D3DXVECTOR3  Pos)
{
	CBandage* pInstance = new CBandage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->m_tInfo.vPos = Pos;
	return pInstance;
}

const INFO & CBandage::GetInfo() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

const float & CBandage::GetColX() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_fColSizeX;
}

const float & CBandage::GetColY() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_fColSizeY;

}

void CBandage::SetPos(D3DXVECTOR3& Pos)
{
	m_tInfo.vPos = Pos;
}

void CBandage::SetEndflag(bool flag)
{
	m_bEnd = flag;
}

void CBandage::SetReplay()
{

	m_bReplay = true;
	iter_begin = m_listAlpa.begin();
}

const float& CBandage::GetAlpa() const
{
	return m_fAlpa;
}
