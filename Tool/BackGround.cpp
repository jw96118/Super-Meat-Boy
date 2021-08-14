#include "stdafx.h"
#include "BackGround.h"
#include "ToolView.h"
#include "Sprite.h"
CBackGround::CBackGround() : m_Back(nullptr)
{
}

CBackGround::~CBackGround()
{
}

int CBackGround::Update()
{
	return 0;
}

void CBackGround::LateUpdate()
{

}

void CBackGround::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"BackGround", L"BACK", m_Back->byDrawID);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		m_Back->vSize.x * m_Back->Size,
		m_Back->vSize.y * m_Back->Size,
		m_Back->vSize.z);

	D3DXMatrixTranslation(&matTrans,
		m_Back->vPos.x  - m_pView->GetScrollPos(0),
		m_Back->vPos.y  - m_pView->GetScrollPos(1),
		m_Back->vPos.z);


	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale  * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

HRESULT CBackGround::Initialize()
{

	float fX = 0.f, fY = 0.f;
	float Size = 1.f;

	m_Back = new TILE_INFO;
	m_Back->vPos = { fX, fY, 0.f };
	m_Back->vSize = { Size, Size, 0.f };
	m_Back->byDrawID = 0;
	m_Back->byOption = 0;

	return S_OK;
}

void CBackGround::Release()
{
	if (m_Back != nullptr)
	{
		delete m_Back;
		m_Back = nullptr;
	}
}

void CBackGround::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption, const float & angle, const float & changex, const float & changey, const RECT * col)
{
}

void CBackGround::MiniRender()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"BackGround", L"BACK", m_Back->byDrawID);
	NULL_CHECK(pTexInfo);
	float _Size = 0.3f;
	D3DXMatrixScaling(&matScale,
		m_Back->vSize.x * _Size *m_Back->Size,
		m_Back->vSize.y * _Size *m_Back->Size,
		m_Back->vSize.z);

	D3DXMatrixTranslation(&matTrans,
		m_Back->vPos.x * _Size,
		m_Back->vPos.y * _Size,
		m_Back->vPos.z);

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale  * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CBackGround::SaveBack(DWORD& dwBytes,const HANDLE & hFile, const TCHAR * pFilePath)
{
	WriteFile(hFile, m_Back, sizeof(TILE_INFO), &dwBytes, nullptr);
}

void CBackGround::LoadBack(DWORD& dwBytes,const HANDLE & hFile, const TCHAR * pFilePath)
{
	if (m_Back != nullptr)
	{
		delete m_Back;
		m_Back = nullptr;
	}
	m_Back = new TILE_INFO;
	ReadFile(hFile, m_Back, sizeof(TILE_INFO), &dwBytes, nullptr);
	
}

void CBackGround::SetSize(float size)
{
	m_Back->Size = size;
}



int CBackGround::GetBackIndex(const D3DXVECTOR3 & vPos)
{
	return 0;
}

CBackGround * CBackGround::Create(CToolView * pView)
{
	CBackGround* pInstance = new CBackGround;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	if (pView)
		pInstance->m_pView = pView;

	return pInstance;
}
