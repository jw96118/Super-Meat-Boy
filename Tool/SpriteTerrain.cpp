#include "stdafx.h"
#include "SpriteTerrain.h"
#include "ToolView.h"
#include "Sprite.h"
CSpriteTerrain::CSpriteTerrain()
{
}

CSpriteTerrain::~CSpriteTerrain()
{
	Release();
}

int CSpriteTerrain::Update()
{
	return 0;
}

void CSpriteTerrain::LateUpdate()
{
}

void CSpriteTerrain::Render()
{
	//D3DXMATRIX matScale, matTrans, matRotZ;

	//const CSprite* pTexInfo = nullptr;
	//float fCenterX = 0.f, fCenterY = 0.f;

	//TCHAR szIndexNum[MIN_STR] = L"";

	//for (size_t i = 0; i < m_vecTile.size(); ++i)
	//{
	//	pTexInfo = m_pSpriteMgr->GetSpriteInfo(L"TILE");
	//	NULL_CHECK_CONTINUE(pTexInfo);

	//	D3DXMatrixScaling(&matScale,
	//		m_vecTile[i]->vSize.x * m_vecTile[i]->changeX,
	//		m_vecTile[i]->vSize.y * m_vecTile[i]->changeY,
	//		m_vecTile[i]->vSize.z);
	//	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_vecTile[i]->m_fAngle));

	//	D3DXMatrixTranslation(&matTrans,
	//		m_vecTile[i]->vPos.x - m_pView->GetScrollPos(0),
	//		m_vecTile[i]->vPos.y - m_pView->GetScrollPos(1),
	//		m_vecTile[i]->vPos.z);

	//	DrawPoint = { STILECX * (m_vecTile[i]->byDrawID % 10),STILECY * (m_vecTile[i]->byDrawID / 10),
	//		 STILECX * ((m_vecTile[i]->byDrawID % 10) + 1),  STILECY * ((m_vecTile[i]->byDrawID + 10) / 10) };

	//	fCenterX = STILECX * 0.5f ;
	//	fCenterY = STILECY * 0.5f ;

	//	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale *  matRotZ * matTrans));
	//	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->GetTex(), &DrawPoint,
	//		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	//	// 타일 인덱스 출력
	//	swprintf_s(szIndexNum, L"%d", i);

	//	m_pDeviceMgr->GetFont()->DrawText(m_pDeviceMgr->GetSprite(), szIndexNum,
	//		lstrlen(szIndexNum), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}
}

HRESULT CSpriteTerrain::Initialize()
{
	m_vecTile.reserve(TILEX * TILEY);

	SPRITE_INFO* pTile = nullptr;
	float fX = 0.f, fY = 0.f;
	float Size = 0.7f;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fX = j * STILECX * Size + STILECX * Size / 2;
			fY = i * STILECY * Size + STILECY * Size / 2;

			pTile = new SPRITE_INFO;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { Size, Size, 0.f };
			pTile->byDrawID = 27;
			pTile->byOption = 0;
			pTile->m_fAngle = 0.f;
			pTile->changeX = 1.f;
			pTile->changeY = 1.f;
			pTile->endflag = false;
			for (int i = 0; i < COL_END; i++)
			{
				pTile->Col[i] = { 0 };
			}
			m_vecTile.push_back(pTile);
		}
	}
	m_vecTile.back()->endflag = true;

	return S_OK;
}

void CSpriteTerrain::SaveTile(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath)
{
	//HANDLE hFile = ::CreateFile(pFilePath, GENERIC_WRITE, 0, nullptr,
	//	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	//if (INVALID_HANDLE_VALUE == hFile)
	//	return;


	for (size_t i = 0; i < m_vecTile.size(); ++i)
		WriteFile(hFile, m_vecTile[i], sizeof(SPRITE_INFO), &dwBytes, nullptr);

	//CloseHandle(hFile);
}

void CSpriteTerrain::LoadTile(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath)
{
	//HANDLE hFile = ::CreateFile(pFilePath, GENERIC_READ, 0, nullptr,
	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	//if (INVALID_HANDLE_VALUE == hFile)
	//	return;

	if (!m_vecTile.empty())
	{
		for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<SPRITE_INFO*>);
		m_vecTile.clear();
	}

	SPRITE_INFO tTile = {};
	int count=0;
	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(SPRITE_INFO), &dwBytes, nullptr);

		/*if (0 == dwBytes)
			break;
*/
		m_vecTile.push_back(new SPRITE_INFO(tTile));
		if (m_vecTile[count]->endflag)
			break;
		count++;
	}

	//CloseHandle(hFile);
}



void CSpriteTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<SPRITE_INFO*>);
	m_vecTile.clear();

}

void CSpriteTerrain::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption,const float& angle, const float& changex, const float& changey, const RECT* col)
{
	int iIndex = GetTileIndex(vPos);
	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
	m_vecTile[iIndex]->m_fAngle = angle;
	m_vecTile[iIndex]->changeX = changex;
	m_vecTile[iIndex]->changeY = changey;
	for (int i = 0; i < COL_END; i++)
	{
		m_vecTile[iIndex]->Col[i] = { (int)(m_vecTile[iIndex]->vPos.x + col[i].left * m_vecTile[iIndex]->vSize.x ),
		(int)(m_vecTile[iIndex]->vPos.y + col[i].top  * m_vecTile[iIndex]->vSize.y),
		(int)(m_vecTile[iIndex]->vPos.x + col[i].right * m_vecTile[iIndex]->vSize.x),
		(int)(m_vecTile[iIndex]->vPos.y + col[i].bottom  * m_vecTile[iIndex]->vSize.y) };
	}
}

void CSpriteTerrain::MiniRender()
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	const CSprite* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = m_pSpriteMgr->GetSpriteInfo(L"TILE");
		NULL_CHECK_CONTINUE(pTexInfo);
		float Size = 0.3f;
		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x * Size,
			m_vecTile[i]->vSize.y * Size,
			m_vecTile[i]->vSize.z * Size);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_vecTile[i]->m_fAngle));


		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x* Size ,
			m_vecTile[i]->vPos.y* Size ,
			m_vecTile[i]->vPos.z* Size);

		DrawPoint = { STILECX * (m_vecTile[i]->byDrawID % 10),STILECY * (m_vecTile[i]->byDrawID / 10),
			 STILECX * ((m_vecTile[i]->byDrawID % 10) + 1),  STILECY * ((m_vecTile[i]->byDrawID + 10) / 10) };

		fCenterX = 60 * 0.5f;
		fCenterY = 60 * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matRotZ *matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->GetTex(), &DrawPoint,
			&D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CSpriteTerrain::LineRender()
{

	D3DXVECTOR2 v1[5];
	D3DXVECTOR2 vCol1[COL_END];
	D3DXVECTOR2 vCol2[COL_END];
	D3DXVECTOR2 vCol[2];
	D3DXVECTOR3 m_vConvert[4];
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		//타일 테두리
		m_vConvert[0] = { m_vecTile[i]->vPos.x - (STILECX * 0.5f * m_vecTile[i]->vSize.x) - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y - (STILECY * 0.5f * m_vecTile[i]->vSize.y) - m_pView->GetScrollPos(1), 0.f };
		m_vConvert[1] = { m_vecTile[i]->vPos.x - (STILECX * 0.5f * m_vecTile[i]->vSize.x) - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y + (STILECY * 0.5f * m_vecTile[i]->vSize.y) - m_pView->GetScrollPos(1), 0.f };
		m_vConvert[2] = { m_vecTile[i]->vPos.x + (STILECX * 0.5f * m_vecTile[i]->vSize.x) - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y + (STILECY * 0.5f * m_vecTile[i]->vSize.y) - m_pView->GetScrollPos(1), 0.f };
		m_vConvert[3] = { m_vecTile[i]->vPos.x + (STILECX * 0.5f * m_vecTile[i]->vSize.x) - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y - (STILECY * 0.5f * m_vecTile[i]->vSize.y) - m_pView->GetScrollPos(1) , 0.f };

		for (int i = 0; i < 5; i++)
		{
			v1[i] = (D3DXVECTOR2)m_vConvert[i];
			if (i == 4)
			{
				v1[4] = (D3DXVECTOR2)m_vConvert[0];
			}
		}

		m_pDeviceMgr->GetLine()->Draw(v1, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		//충돌처리 타일
		for (int j = 0; j < COL_END; j++)
		{
			float testx=0.f, testy=0.f;
			if (m_vecTile[i]->Col[j].left != 0)
			{
				if (j % 2 == 1)
				{
					testx = 1.f;
					testy = 1.f;
				}
			}
			vCol1[j] = { (float)m_vecTile[i]->Col[j].left - testx - m_pView->GetScrollPos(0),(float)m_vecTile[i]->Col[j].top - testy - m_pView->GetScrollPos(1) };
			vCol2[j] = { (float)m_vecTile[i]->Col[j].right - testx - m_pView->GetScrollPos(0),(float)m_vecTile[i]->Col[j].bottom  - testy - m_pView->GetScrollPos(1) };
			vCol[0] = vCol1[j];
			vCol[1] = vCol2[j];
			m_pDeviceMgr->GetLine()->Draw(vCol, 2, D3DCOLOR_ARGB(255, 255, 0, 0));

		}

	}
}



bool CSpriteTerrain::IsPicking(const D3DXVECTOR3 & vPos, int iIndex)
{
	if ((m_vecTile[iIndex]->vPos.x - STILECX * 0.5f * m_vecTile[iIndex]->vSize.x <= vPos.x) &&
		(m_vecTile[iIndex]->vPos.x + STILECX * 0.5f* m_vecTile[iIndex]->vSize.x >= vPos.x) &&
		(m_vecTile[iIndex]->vPos.y - STILECY * 0.5f* m_vecTile[iIndex]->vSize.y <= vPos.y) &&
		(m_vecTile[iIndex]->vPos.y + STILECY * 0.5f * m_vecTile[iIndex]->vSize.y >= vPos.y))
	{
		return true;
	}
	return false;
}

CSpriteTerrain * CSpriteTerrain::Create(CToolView * pView)
{
	CSpriteTerrain* pInstance = new CSpriteTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	if (pView)
		pInstance->m_pView = pView;

	return pInstance;
}
int CSpriteTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (int i = 0; i < (int)m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}

	return -1;
}