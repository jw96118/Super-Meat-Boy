#include "stdafx.h"
#include "BackObject.h"
#include "ToolView.h"
CBackObject::CBackObject() : m_pView(nullptr), m_fAngle(0.f)
{															
}															

CBackObject::~CBackObject()
{
	Release();
}

int CBackObject::Update()
{
	return 0;
}

void CBackObject::LateUpdate()
{
}

void CBackObject::Render()
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"TileObject", L"FOREST", byDrawID);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		vSize.x ,
		vSize.y ,
		vSize.z);

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	D3DXMatrixTranslation(&matTrans,
		vPos.x - m_pView->GetScrollPos(0),
		vPos.y - m_pView->GetScrollPos(1),
		vPos.z);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale *  matRotZ * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CBackObject::Initialize()
{
	
	return S_OK;
}

void CBackObject::Init(CToolView* view)
{
	m_pView = view;
	m_pDeviceMgr = CDeviceMgr::GetInstance();
	m_pTextureMgr = CTextureMgr::GetInstance();
	m_pSpriteMgr = CSpriteMgr::GetInstance();
	vSize = { m_fSize,m_fSize ,0.f };
}

void CBackObject::Release()
{
}

void CBackObject::ObjChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID)
{
}

void CBackObject::MiniRender()
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"TileObject", L"FOREST", byDrawID);
	NULL_CHECK(pTexInfo);
	float Size = 0.3f;
	D3DXMatrixScaling(&matScale,
		vSize.x * Size,
		vSize.y * Size,
		vSize.z);

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	D3DXMatrixTranslation(&matTrans,
		vPos.x * Size - m_pView->GetScrollPos(0),
		vPos.y * Size - m_pView->GetScrollPos(1),
		vPos.z);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale *  matRotZ * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBackObject::LineRender()
{

	D3DXMATRIX matScale, matTrans, matRotZ;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"TileObject", L"FOREST", byDrawID);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f * m_fSize;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f * m_fSize;

	D3DXVECTOR2 v1[5];
	D3DXVECTOR2 vCol1[COL_END];
	D3DXVECTOR2 vCol2[COL_END];
	D3DXVECTOR2 vCol[2];
	D3DXVECTOR3 m_vConvert[4];
	
	//오브젝트 테두리
	m_vConvert[0] = { vPos.x - fCenterX - m_pView->GetScrollPos(0), vPos.y - fCenterY - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[1] = { vPos.x - fCenterX - m_pView->GetScrollPos(0), vPos.y + fCenterY - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[2] = { vPos.x + fCenterX - m_pView->GetScrollPos(0), vPos.y + fCenterY - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[3] = { vPos.x + fCenterX - m_pView->GetScrollPos(0), vPos.y - fCenterY - m_pView->GetScrollPos(1) , 0.f };

	for (int i = 0; i < 5; i++)
	{
		v1[i] = (D3DXVECTOR2)m_vConvert[i];
		if (i == 4)
		{
			v1[4] = (D3DXVECTOR2)m_vConvert[0];
		}
	}

	m_pDeviceMgr->GetLine()->Draw(v1, 5, D3DCOLOR_XRGB(0, 255, 255));
}

void CBackObject::SetSize(float size)
{
}

void CBackObject::SaveBackObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath)
{
	WriteFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	WriteFile(hFile, vSize, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	WriteFile(hFile, matWorld, sizeof(D3DXMATRIX), &dwBytes, nullptr);
	WriteFile(hFile, &byDrawID, sizeof(BYTE), &dwBytes, nullptr);
	WriteFile(hFile, &m_fAngle, sizeof(float), &dwBytes, nullptr);
	WriteFile(hFile, &m_fSize, sizeof(float), &dwBytes, nullptr);
	WriteFile(hFile, &select, sizeof(bool), &dwBytes, nullptr);
	WriteFile(hFile, &endflag, sizeof(bool), &dwBytes, nullptr);
}

void CBackObject::LoadBackObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath)
{
	ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, vSize, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, matWorld, sizeof(D3DXMATRIX), &dwBytes, nullptr);
	ReadFile(hFile, &byDrawID, sizeof(BYTE), &dwBytes, nullptr);
	ReadFile(hFile, &m_fAngle, sizeof(float), &dwBytes, nullptr);
	ReadFile(hFile, &m_fSize, sizeof(float), &dwBytes, nullptr);
	ReadFile(hFile, &select, sizeof(bool), &dwBytes, nullptr);
	ReadFile(hFile, &endflag, sizeof(bool), &dwBytes, nullptr);
}
