#include "stdafx.h"
#include "SpriteTerrain.h"
#include "Sprite.h"
#include "ScrollMgr.h"
CSpriteTerrain::CSpriteTerrain()
{
}

CSpriteTerrain::~CSpriteTerrain()
{
	Release();
}

int CSpriteTerrain::Update()
{
	//int iCullStartY = (int)CScrollMgr::GetScrollPos().y / STILECY * 2.f;	// 행번호
	//int iCullStartX = (int)CScrollMgr::GetScrollPos().x / STILECX * 2.f;	// 열번호
	//int iTileCountX = WINCX / STILECX * 2.f;
	//int iTileCountY = WINCY / STILECY * 2.f;

	//int iIndex = 0;

	//for (int i = iCullStartY; i < iCullStartY + iTileCountY ; ++i)
	//{
	//	for (int j = iCullStartX; j < iCullStartX + iTileCountX ; ++j)
	//	{
	//		iIndex = i * TILEX + j;
	//		for (int z = 0; z < COL_END; z++)
	//		{
	//			if (m_vecBlood[z][iIndex]->m_bDrawBlood)
	//			{
	//				m_vecBlood[z][iIndex]->nowFrame += m_vecBlood[z][iIndex]->maxFrame * m_pTimeMgr->GetDelta() * 5.f;

	//				if (m_vecBlood[z][iIndex]->maxFrame <= m_vecBlood[z][iIndex]->nowFrame)
	//					m_vecBlood[z][iIndex]->nowFrame = m_vecBlood[z][iIndex]->maxFrame;
	//			}
	//		}
	//	}
	//}
	return 0;
}

void CSpriteTerrain::LateUpdate()
{
}

void CSpriteTerrain::Render()
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	const CSprite* pTexInfo = nullptr;
	const TEX_INFO* pBloodTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";




	int iCullStartY = (int)CScrollMgr::GetScrollPos().y / STILECY * 10 / 7;	// 행번호
	int iCullStartX = (int)CScrollMgr::GetScrollPos().x / STILECX * 10 / 7;	// 열번호
	int iTileCountX = WINCX / (STILECX)* 10 / 7;
	int iTileCountY = WINCY / (STILECY)* 10 / 7;

	int iIndex = 0;

	for (int i = iCullStartY; i < iCullStartY + iTileCountY + 3; ++i)
	{
		for (int j = iCullStartX; j < iCullStartX + iTileCountX + 3; ++j)
		{
			iIndex = i * TILEX + j;

			if (0 > iIndex || (int)m_vecTile.size() <= iIndex)
				continue;

			pTexInfo = m_pSpriteMgr->GetSpriteInfo(L"TILE");
			NULL_CHECK_CONTINUE(pTexInfo);

			D3DXMatrixScaling(&matScale,
				m_vecTile[iIndex]->vSize.x * m_vecTile[iIndex]->changeX,
				m_vecTile[iIndex]->vSize.y * m_vecTile[iIndex]->changeY,
				m_vecTile[iIndex]->vSize.z);
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_vecTile[iIndex]->m_fAngle));

			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x - CScrollMgr::GetScrollPos().x,
				m_vecTile[iIndex]->vPos.y - CScrollMgr::GetScrollPos().y,
				m_vecTile[iIndex]->vPos.z);
			int tempID = 0;
			if (m_vecTile[iIndex]->byDrawID == 27)
			{
				tempID = 80;
			}
			else
			{
				tempID = m_vecTile[iIndex]->byDrawID;
			}
			DrawPoint = { STILECX * (tempID % 10),STILECY * (tempID / 10),
				 STILECX * ((tempID % 10) + 1),  STILECY * ((tempID + 10) / 10) };

			fCenterX = STILECX * 0.5f;
			fCenterY = STILECY * 0.5f;

			m_pDeviceMgr->GetSprite()->SetTransform(&(matScale *  matRotZ * matTrans));
			m_pDeviceMgr->GetSprite()->Draw(pTexInfo->GetTex(), &DrawPoint,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


			

		

			
			float tempAngle = 0;
			float tempX = 0.f, tempY = 0.f;
			for(int z =0; z< COL_END; z++)
			{
				if (m_vecBlood[z][iIndex]->m_bDrawBlood)
				{
					m_vecBlood[z][iIndex]->nowFrame += m_vecBlood[z][iIndex]->maxFrame * m_pTimeMgr->GetDelta() * 5.f;

					if (m_vecBlood[z][iIndex]->maxFrame <= m_vecBlood[z][iIndex]->nowFrame)
						m_vecBlood[z][iIndex]->nowFrame = m_vecBlood[z][iIndex]->maxFrame;

					pBloodTexInfo = m_pTextureMgr->GetTexInfo(L"Blood", L"blood", m_vecBlood[z][iIndex]->nowFrame);
					NULL_CHECK_CONTINUE(pBloodTexInfo);
					switch (z)
					{
					case LEFT:
						tempAngle = 270.f;
						tempX = -(STILECX * 0.5f * (m_vecTile[iIndex]->vSize.x -0.1f));
						tempY = 0;
						break;
					case RIGHT:
						tempAngle = 90.f;
						tempX = (STILECX * 0.5f * (m_vecTile[iIndex]->vSize.x - 0.1f));
						tempY = 0;
						break;
					case TOP:
						tempAngle = 0.f;
						tempX = 0;
						tempY = -(STILECY * 0.5f * (m_vecTile[iIndex]->vSize.y - 0.1f));
						break;
					case BOTTOM:
						tempAngle = 180.f;
						tempX = 0;
						tempY = (STILECY * 0.5f * (m_vecTile[iIndex]->vSize.y - 0.1f));
						break;
					case UPBOTTOM:
						tempAngle = 45.f;
						tempX = 0;
						tempY = 0;
						break;
					case BOTTOMUP:
						tempAngle = 135.f;
						tempX = 0;
						tempY = 0;
						break;
					}
					D3DXMatrixScaling(&matScale,
						m_vecTile[iIndex]->vSize.x + 0.1f,
						m_vecTile[iIndex]->vSize.y + 0.1f,
						m_vecTile[iIndex]->vSize.z);

					D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(tempAngle));

					D3DXMatrixTranslation(&matTrans,
						m_vecBlood[z][iIndex]->vPos.x + tempX - CScrollMgr::GetScrollPos().x,
						m_vecBlood[z][iIndex]->vPos.y + tempY - CScrollMgr::GetScrollPos().y,
						m_vecBlood[z][iIndex]->vPos.z);

					fCenterX = pBloodTexInfo->tImgInfo.Width * 0.5f;
					fCenterY = pBloodTexInfo->tImgInfo.Height * 0.5f;

					m_pDeviceMgr->GetSprite()->SetTransform(&(matScale *  matRotZ * matTrans));
					m_pDeviceMgr->GetSprite()->Draw(pBloodTexInfo->pTexture, nullptr,
						&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
		}
	}

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
	if (!m_vecBlood->empty())
	{
		for (int i = 0; i < COL_END; i++)
		{
			for_each(m_vecBlood[i].begin(), m_vecBlood[i].end(), SafeDelete<BLOOD_INFO*>);
			m_vecBlood[i].clear();
		}
	}
	SPRITE_INFO tTile = {};
	BLOOD_INFO  tBlood = {};
	int count=0;
	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(SPRITE_INFO), &dwBytes, nullptr);

		tBlood.vPos = tTile.vPos;
		tBlood.nowFrame = 0;
		tBlood.m_bDrawBlood = false;
		
		m_vecTile.push_back(new SPRITE_INFO(tTile));
		for (int i = 0; i < COL_END; i++)
		{
			m_vecBlood[i].push_back(new BLOOD_INFO(tBlood));
		}
		
		if (m_vecTile[count]->endflag)
			break;
		count++;
	}

	//CloseHandle(hFile);
}

void CSpriteTerrain::SetReplay()
{
	if (!m_vecBlood->empty())
	{
		for (int i = 0; i < COL_END; i++)
		{
			for_each(m_vecBlood[i].begin(), m_vecBlood[i].end(), SafeDelete<BLOOD_INFO*>);
			m_vecBlood[i].clear();
		}
	}
	BLOOD_INFO  tBlood = {};
	for(int i =0;i< m_vecTile.size();i++)
	{
		tBlood.vPos = m_vecTile[i]->vPos;
		tBlood.nowFrame = 0;
		tBlood.m_bDrawBlood = false;

		for (int j = 0; j < COL_END; j++)
		{
			m_vecBlood[j].push_back(new BLOOD_INFO(tBlood));
		}
	}
}

SPRITE_INFO* CSpriteTerrain::GetSpriteTerrain(const D3DXVECTOR3& vPos)
{
	if (GetTileIndex(vPos) == -1)
	{
		return nullptr;
	}
	return m_vecTile[GetTileIndex(vPos)];
}

BLOOD_INFO * CSpriteTerrain::GetBloodTerrain(const D3DXVECTOR3 & vPos,const int& index)
{
	return m_vecBlood[index][GetTileIndex(vPos)];
}



void CSpriteTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<SPRITE_INFO*>);
	m_vecTile.clear();
	for (int i = 0; i < COL_END; i++)
	{
		for_each(m_vecBlood[i].begin(), m_vecBlood[i].end(), SafeDelete<BLOOD_INFO*>);
		m_vecBlood[i].clear();
	}
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
		m_vConvert[0] = { m_vecTile[i]->vPos.x - (STILECX * 0.5f * m_vecTile[i]->vSize.x) - CScrollMgr::GetScrollPos().x, m_vecTile[i]->vPos.y - (STILECY * 0.5f * m_vecTile[i]->vSize.y) -  CScrollMgr::GetScrollPos().y, 0.f };
		m_vConvert[1] = { m_vecTile[i]->vPos.x - (STILECX * 0.5f * m_vecTile[i]->vSize.x) - CScrollMgr::GetScrollPos().x, m_vecTile[i]->vPos.y + (STILECY * 0.5f * m_vecTile[i]->vSize.y) -  CScrollMgr::GetScrollPos().y, 0.f };
		m_vConvert[2] = { m_vecTile[i]->vPos.x + (STILECX * 0.5f * m_vecTile[i]->vSize.x) - CScrollMgr::GetScrollPos().x, m_vecTile[i]->vPos.y + (STILECY * 0.5f * m_vecTile[i]->vSize.y) -  CScrollMgr::GetScrollPos().y, 0.f };
		m_vConvert[3] = { m_vecTile[i]->vPos.x + (STILECX * 0.5f * m_vecTile[i]->vSize.x) - CScrollMgr::GetScrollPos().x, m_vecTile[i]->vPos.y - (STILECY * 0.5f * m_vecTile[i]->vSize.y) -  CScrollMgr::GetScrollPos().y , 0.f };

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
			vCol1[j] = { (float)m_vecTile[i]->Col[j].left - testx - CScrollMgr::GetScrollPos().x,(float)m_vecTile[i]->Col[j].top - testy - CScrollMgr::GetScrollPos().y };
			vCol2[j] = { (float)m_vecTile[i]->Col[j].right - testx - CScrollMgr::GetScrollPos().x,(float)m_vecTile[i]->Col[j].bottom  - testy - CScrollMgr::GetScrollPos().y };
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

CSpriteTerrain * CSpriteTerrain::Create()
{
	CSpriteTerrain* pInstance = new CSpriteTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}


	return pInstance;
}
int CSpriteTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	int iCullStartY = (int)CScrollMgr::GetScrollPos().y / STILECY * 10 / 7;	// 행번호
	int iCullStartX = (int)CScrollMgr::GetScrollPos().x / STILECX * 10 / 7;	// 열번호
	int iTileCountX = WINCX / (STILECX) * 10 / 7;
	int iTileCountY = WINCY / (STILECY) * 10 / 7;

	int iIndex = 0;

	for (int i = iCullStartY; i < iCullStartY + iTileCountY + 3; ++i)
	{
		for (int j = iCullStartX; j < iCullStartX + iTileCountX + 3; ++j)
		{
			iIndex = i * TILEX + j;

			if (0 > iIndex || (int)m_vecTile.size() <= iIndex)
				continue;

			if (IsPicking(vPos, iIndex))
				return iIndex;
		}
	}
		
	

	return -1;
}