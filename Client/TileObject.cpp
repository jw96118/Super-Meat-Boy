#include "stdafx.h"
#include "TileObject.h"
#include "SpriteTerrain.h"
#include "BackGround.h"
#include "BackObject.h"
#include "KillObject.h"
#include "ScrollMgr.h"
CTileObject::CTileObject() : m_pDeviceMgr(CDeviceMgr::GetInstance())
{
}

CTileObject::~CTileObject()
{
	Release();
}

int CTileObject::Update()
{
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->Update();
	}
	m_pSTerrain->Update();
	return 0;
}

void CTileObject::LateUpdate()
{
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->LateUpdate();
	}
}

void CTileObject::Render()
{
	m_pBack->Render();
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->Render();
	}
	
	m_pSTerrain->Render();

	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		m_pBackObj[i]->Render();
	}
}


void CTileObject::LineRender()
{
	// m_pSTerrain->LineRender();
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->LineRender();
	}
	//for (int i = 0; i < m_pBackObj.size(); i++)
	//{
	//	if (m_pBackObj[i]->select)
	//		m_pBackObj[i]->LineRender();
	//}
	D3DXVECTOR2 v1[5];
	D3DXVECTOR3 m_vConvert[4];
	m_vConvert[0] = { meatPos.x - 15.f - CScrollMgr::GetScrollPos().x, meatPos.y - 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[1] = { meatPos.x - 15.f - CScrollMgr::GetScrollPos().x, meatPos.y + 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[2] = { meatPos.x + 15.f - CScrollMgr::GetScrollPos().x, meatPos.y + 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[3] = { meatPos.x + 15.f - CScrollMgr::GetScrollPos().x, meatPos.y - 15.f - CScrollMgr::GetScrollPos().y , 0.f };

	for (int i = 0; i < 5; i++)
	{
		v1[i] = (D3DXVECTOR2)m_vConvert[i];
		if (i == 4)
		{
			v1[4] = (D3DXVECTOR2)m_vConvert[0];
		}
	}
	m_pDeviceMgr->GetLine()->Draw(v1, 5, D3DCOLOR_XRGB(0, 255, 255));

	D3DXVECTOR2 v2[5];
	D3DXVECTOR3 m_vConvert2[4];
	m_vConvert2[0] = { bandPos.x - 15.f - CScrollMgr::GetScrollPos().x, bandPos.y - 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert2[1] = { bandPos.x - 15.f - CScrollMgr::GetScrollPos().x, bandPos.y + 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert2[2] = { bandPos.x + 15.f - CScrollMgr::GetScrollPos().x, bandPos.y + 15.f - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert2[3] = { bandPos.x + 15.f - CScrollMgr::GetScrollPos().x, bandPos.y - 15.f - CScrollMgr::GetScrollPos().y , 0.f };

	for (int i = 0; i < 5; i++)
	{
		v2[i] = (D3DXVECTOR2)m_vConvert2[i];
		if (i == 4)
		{
			v2[4] = (D3DXVECTOR2)m_vConvert2[0];
		}
	}
	m_pDeviceMgr->GetLine()->Draw(v2, 5, D3DCOLOR_XRGB(255, 0, 255));


}

void CTileObject::Init(const TCHAR* pFilePath)
{
	
	LoadObj(pFilePath);

}

CKillObject * CTileObject::GetKillObj(int index, bool back)
{
	if (m_pKillObj[index] == nullptr)
		return nullptr;
	if (back)
		return m_pKillObj.back();
	else
		return m_pKillObj[index];
}

void CTileObject::SetSawRenderChange(int index)
{
	if (m_pKillObj[index] == nullptr)
		return ;
	else
		m_pKillObj[index]->SetSawChange();
}

const int & CTileObject::GetKillObjSize() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_pKillObj.size();
}

const D3DXVECTOR3 CTileObject::GetMeatPos() const
{
	return meatPos;
}

const D3DXVECTOR3 CTileObject::GetBandPos() const
{
	return bandPos;
}



void CTileObject::Release()
{
	SafeDelete(m_pSTerrain);
	SafeDelete(m_pBack);
	for_each(m_pBackObj.begin(), m_pBackObj.end(), SafeDelete<CBackObject*>);
	for_each(m_pKillObj.begin(), m_pKillObj.end(), SafeDelete<CKillObject*>);
}

void CTileObject::SaveObj(const TCHAR * pFilePath)
{
	TCHAR* path = {};
	//_tcscpy(path, pFilePath);
	//_tcscat(path, L"Tile");
	
	HANDLE hFile = ::CreateFile(pFilePath, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD dwBytes = 0;

	m_pSTerrain->SaveTile(dwBytes, hFile, pFilePath);
	m_pBack->SaveBack(dwBytes, hFile, pFilePath);
	for (size_t i = 0; i < m_pBackObj.size(); ++i)
		WriteFile(hFile, m_pBackObj[i], sizeof(CBackObject), &dwBytes, nullptr);
	for (size_t i = 0; i < m_pKillObj.size(); ++i)
		m_pKillObj[i]->SaveKillObj(dwBytes, hFile, pFilePath);

	WriteFile(hFile, meatPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	WriteFile(hFile, bandPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);

	CloseHandle(hFile);
}

void CTileObject::LoadObj(const TCHAR * pFilePath)
{
	HANDLE hFile = ::CreateFile(pFilePath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD dwBytes = 0;
	m_pSTerrain->LoadTile(dwBytes, hFile, pFilePath);
	m_pBack->LoadBack(dwBytes, hFile, pFilePath);
	if (!m_pBackObj.empty())
	{
		for_each(m_pBackObj.begin(), m_pBackObj.end(), SafeDelete<CBackObject*>);
		m_pBackObj.clear();
	}

	CBackObject tBack = {};
	int count = 0;
	while (true)
	{
		//ReadFile(hFile, &tBack, sizeof(CBackObject), &dwBytes, nullptr);
		tBack.LoadBackObj(dwBytes, hFile, pFilePath);
		m_pBackObj.push_back(new CBackObject(tBack));
		m_pBackObj[count]->Init();
		if (m_pBackObj[count]->endflag)
			break;
		count++;
	}

	if (!m_pKillObj.empty())
	{
		for_each(m_pKillObj.begin(), m_pKillObj.end(), SafeDelete<CKillObject*>);
		m_pKillObj.clear();
	}
	count = 0;
	while(true)
	{
		m_pKillObj.push_back(CKillObject::LoadKillObj(dwBytes, hFile, pFilePath));

		if (m_pKillObj[count]->endflag)
			break;
		count++;
	}
	ReadFile(hFile, meatPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, bandPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);

	CloseHandle(hFile);
}

CTileObject * CTileObject::Create()
{
	CTileObject* pInstance = new CTileObject;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

CSpriteTerrain * CTileObject::GetSTerrain() const
{
	if (m_pSTerrain == nullptr)
		return nullptr;
	return m_pSTerrain;
}

void CTileObject::SetReaplay()
{
	m_pSTerrain->SetReplay();
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->SetReplay(true);
	}
}

HRESULT CTileObject::Initialize()
{
	m_pSTerrain = CSpriteTerrain::Create();
	//NULL_CHECK_MSG(m_pSTerrain, L"Terrain Create Failed");
	m_pBack = CBackGround::Create();
	//NULL_CHECK_MSG(m_pSTerrain, L"Terrain Create Failed");

	//LoadObj(L"../MapData/testStage1.dat");

	m_pType = OBJECT_TERRAIN;
	return S_OK;
}
