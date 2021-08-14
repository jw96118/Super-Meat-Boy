#include "stdafx.h"
#include "TileObject.h"
#include "SpriteTerrain.h"
#include "BackGround.h"
#include "ToolView.h"
#include "BackObject.h"
#include "MainFrm.h"
#include "MyForm.h"
#include "BackObjTool.h"
#include "KillObject.h"

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
	m_pView->Invalidate(FALSE);
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

	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		m_pBackObj[i]->Render();
	}
	
	m_pSTerrain->Render();

	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->Render();
	}
}

void CTileObject::MiniRender()
{
	m_pBack->MiniRender();	
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->MiniRender();
	}
	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		m_pBackObj[i]->MiniRender();
	}
	m_pSTerrain->MiniRender();
}

void CTileObject::LineRender()
{
	//m_pSTerrain->LineRender();
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		if (m_pKillObj[i]->select)
			m_pKillObj[i]->LineRender();
	}
	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		if (m_pBackObj[i]->select)
			m_pBackObj[i]->LineRender();
	}
	D3DXVECTOR2 v1[5];
	D3DXVECTOR3 m_vConvert[4];
	m_vConvert[0] = { meatPos.x - 15.f - m_pView->GetScrollPos(0), meatPos.y - 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[1] = { meatPos.x - 15.f - m_pView->GetScrollPos(0), meatPos.y + 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[2] = { meatPos.x + 15.f - m_pView->GetScrollPos(0), meatPos.y + 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert[3] = { meatPos.x + 15.f - m_pView->GetScrollPos(0), meatPos.y - 15.f - m_pView->GetScrollPos(1) , 0.f };

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
	m_vConvert2[0] = { bandPos.x - 15.f - m_pView->GetScrollPos(0), bandPos.y - 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert2[1] = { bandPos.x - 15.f - m_pView->GetScrollPos(0), bandPos.y + 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert2[2] = { bandPos.x + 15.f - m_pView->GetScrollPos(0), bandPos.y + 15.f - m_pView->GetScrollPos(1), 0.f };
	m_vConvert2[3] = { bandPos.x + 15.f - m_pView->GetScrollPos(0), bandPos.y - 15.f - m_pView->GetScrollPos(1) , 0.f };

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

void CTileObject::Init(CToolView* pView)
{
	m_pSTerrain = CSpriteTerrain::Create(pView);
	//NULL_CHECK_MSG(m_pSTerrain, L"Terrain Create Failed");
	m_pBack = CBackGround::Create(pView);
	m_pView = pView;
	//NULL_CHECK_MSG(m_pBack, L"BackGround Create Failed");
}

void CTileObject::SpriteTileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption, const float & angle, const float & changex, const float & changey, const RECT * col)
{
	m_pSTerrain->TileChange(vPos, byDrawID, byOption, angle, changex, changey, col);
}

void CTileObject::SetBackGroundSize(float size)
{
	m_pBack->SetSize(size);
}

void CTileObject::InsertBackObj(CToolView* pView, const D3DXVECTOR3 & vPos, const D3DXVECTOR3 & vSize, const BYTE & byDrawID, float angle)
{
	CBackObject temp = {};
	temp.vPos = vPos;
	temp.vSize = vSize;
	temp.m_fAngle = angle;
	temp.byDrawID = byDrawID;
	temp.Init(pView);
	m_pBackObj.push_back(new CBackObject(temp));
	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		m_pBackObj[i]->endflag = false;
	}
	m_pBackObj.back()->endflag = true;
}

void CTileObject::DeleteBackObj(int iIndex)
{
	m_pBackObj.erase(m_pBackObj.begin() + iIndex);
	m_pBackObj.back()->endflag = true;
}

void CTileObject::InsertKillObj(KILLOBJ_TYPE type)
{
	m_pKillObj.push_back(CKillObject::Create(m_pView,type));
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		m_pKillObj[i]->endflag = false;
	}
	m_pKillObj.back()->endflag = true;
}


void CTileObject::DeleteKillObj(int iIndex)
{
	m_pKillObj.erase(m_pKillObj.begin() + iIndex);
	m_pKillObj.back()->endflag = true;
}



void CTileObject::SetBackObj(int iIndex, float& fSize, const BYTE & byDrawID, float angle)
{
	m_pBackObj[iIndex]->m_fSize = fSize;
	m_pBackObj[iIndex]->vSize = { fSize ,fSize ,0.f };
	m_pBackObj[iIndex]->byDrawID = byDrawID;
	m_pBackObj[iIndex]->m_fAngle = angle;
}

void CTileObject::SetBackObjPos(int iIndex, const D3DXVECTOR3 & vPos)
{
	if (!m_pBackObj.empty())
		m_pBackObj[iIndex]->vPos = vPos;
}

void CTileObject::SetKillSize(int iIndex, float & fSize, float angle, KILLOBJ_TYPE type)
{
	m_pKillObj[iIndex]->m_fSize = fSize;
	m_pKillObj[iIndex]->m_fAngle = angle;
	m_pKillObj[iIndex]->obj_Type = type;
	m_pKillObj[iIndex]->m_pSaw->m_fAngle = angle;
	//m_pKillObj[iIndex]->m_pSaw2->m_fAngle = angle;
	m_pKillObj[iIndex]->m_pSawAngle->m_fAngle = angle;
	m_pKillObj[iIndex]->m_pSawShoter->m_fAngle = angle;
}

void CTileObject::SetKillPos(int iIndex, const D3DXVECTOR3 & vPos)
{
	if (!m_pKillObj.empty())
		m_pKillObj[iIndex]->vPos = vPos;
}

int CTileObject::BObjectImage(int index)
{
	return m_pBackObj[index]->byDrawID;
}

void CTileObject::SelectBObject(int index)
{
	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		if (i == index)
		{
			m_pBackObj[i]->select = true;
		}
		else
		{
			m_pBackObj[i]->select = false;
		}
	}

}

void CTileObject::SelectKObject(int index)
{
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		if (i == index)
		{
			m_pKillObj[i]->select = true;
		}
		else
		{
			m_pKillObj[i]->select = false;
		}
	}

}

CBackObject * CTileObject::GetBackObj(int index, bool back)
{
	if (m_pBackObj[index] == nullptr)
		return nullptr;
	if (back)
		return m_pBackObj.back();
	else
		return m_pBackObj[index];
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

void CTileObject::SetMeatPos(const D3DXVECTOR3 & vPos)
{
	meatPos = vPos;
}

void CTileObject::SetBandPos(const D3DXVECTOR3 & vPos)
{
	bandPos = vPos;
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
		m_pBackObj[i]->SaveBackObj(dwBytes, hFile, pFilePath);
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
		m_pBackObj[count]->Init(m_pView);
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
		m_pKillObj.push_back(CKillObject::LoadKillObj(dwBytes, hFile, pFilePath,m_pView));

		if (m_pKillObj[count]->endflag)
			break;
		count++;
	}
	ReadFile(hFile, meatPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, bandPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);

	CloseHandle(hFile);

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pMyView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pMyView);

	pMyView->m_BackObjTool.DeleteAll();
	for (int i = 0; i < m_pBackObj.size(); i++)
	{
		pMyView->m_BackObjTool.InputList(i);
	}

	pMyView->m_KillObjTool.DeleteAll();
	for (int i = 0; i < m_pKillObj.size(); i++)
	{
		pMyView->m_KillObjTool.InputList(i);
	}

	m_pView->Invalidate(FALSE);
}
