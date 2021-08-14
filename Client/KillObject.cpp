#include "stdafx.h"
#include "KillObject.h"
#include "ScrollMgr.h"
CKillObject::CKillObject() : m_pSaw(nullptr), m_pSawAngle(nullptr), m_pSawShoter(nullptr)
{
}

CKillObject::~CKillObject()
{
	Release();
}

int CKillObject::Update()
{
		switch (obj_Type)
		{
		case SAW_MOVE_ANGLE:
			m_pSawAngle->m_fAngle += m_pTimeMgr->GetDelta() * 200.f;
			break;
		case SAW_MOVE:
			if (tempPos.x <= -126)
			{
				moveflag = true;
			}
			if (tempPos.x >= 126)
			{
				moveflag = false;
			}
			if (tempPos.x > -126 && !moveflag)
				tempPos -= {m_pTimeMgr->GetDelta() * 100.f, 0, 0};
			else if (tempPos.x < 126 && moveflag)
				tempPos += {m_pTimeMgr->GetDelta() * 100.f, 0, 0};
			break;
		}
		m_pSaw->m_fAngle += m_pTimeMgr->GetDelta() * 250.f;	
		m_listKill.push_back(SetReplayInfo());
		iter_begin = m_listKill.begin();
	
	return 0;
}

void CKillObject::LateUpdate()
{
	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMATRIX matRotZ_A, matTrans_A;
	D3DXMATRIX matMiniScale, matMiniTrans;
	float fSize = 0.3f;
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		m_pSaw->vPos = vPos;
		m_pSaw->m_fSize = m_fSize;
		D3DXMatrixScaling(&matScale,
			m_pSaw->vSize.x * m_pSaw->m_fSize,
			m_pSaw->vSize.y * m_pSaw->m_fSize,
			m_pSaw->vSize.z);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_pSaw->m_fAngle));
		D3DXMatrixTranslation(&matTrans,
			m_pSaw->vPos.x - CScrollMgr::GetScrollPos().x,
			m_pSaw->vPos.y - CScrollMgr::GetScrollPos().y,
			m_pSaw->vPos.z);
		m_pSaw->matWorld = matScale * matRotZ * matTrans;
	case SAW_MOVE:
		m_pSawAngle->vPos = vPos;
		m_pSawAngle->m_fSize = m_fSize;
		D3DXMatrixScaling(&matScale,
			m_pSawAngle->vSize.x * m_pSawAngle->m_fSize,
			m_pSawAngle->vSize.y * m_pSawAngle->m_fSize,
			m_pSawAngle->vSize.z);
		D3DXMatrixRotationZ(&matRotZ_A, D3DXToRadian(m_pSawAngle->m_fAngle));
		D3DXMatrixTranslation(&matTrans_A,
			m_pSawAngle->vPos.x - CScrollMgr::GetScrollPos().x,
			m_pSawAngle->vPos.y - CScrollMgr::GetScrollPos().y,
			m_pSawAngle->vPos.z);
		m_pSawAngle->matWorld = matScale * matRotZ_A * matTrans_A;

		m_pSaw->m_fSize = m_fSize;
		m_pSaw->vPos = tempPos * m_fSize;

		D3DXMatrixScaling(&matScale,
			m_pSaw->vSize.x * m_pSaw->m_fSize,
			m_pSaw->vSize.y * m_pSaw->m_fSize,
			m_pSaw->vSize.z);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_pSaw->m_fAngle));
		D3DXMatrixTranslation(&matTrans,
			m_pSaw->vPos.x,
			m_pSaw->vPos.y,
			m_pSaw->vPos.z);
		m_pSaw->matWorld = matScale * matRotZ * matTrans * matRotZ_A* matTrans_A;

		tempMat = matScale * matTrans * matRotZ_A;

		break;
	case SAW_MOVE_ANGLE:
		m_pSawAngle->vPos = vPos;
		m_pSawAngle->m_fSize = m_fSize;
		D3DXMatrixScaling(&matScale,
			m_pSawAngle->vSize.x * m_pSawAngle->m_fSize,
			m_pSawAngle->vSize.y * m_pSawAngle->m_fSize,
			m_pSawAngle->vSize.z);

		D3DXMatrixRotationZ(&matRotZ_A, D3DXToRadian(m_pSawAngle->m_fAngle));
		D3DXMatrixTranslation(&matTrans_A,
			m_pSawAngle->vPos.x - CScrollMgr::GetScrollPos().x,
			m_pSawAngle->vPos.y - CScrollMgr::GetScrollPos().y,
			m_pSawAngle->vPos.z);
		m_pSawAngle->matWorld = matScale * matRotZ_A * matTrans_A;

		tempPos = { 252, 0 ,0.f };
		m_pSaw->m_fSize = m_fSize;
		m_pSaw->vPos = tempPos * m_fSize;

		D3DXMatrixScaling(&matScale,
			m_pSaw->vSize.x * m_pSaw->m_fSize,
			m_pSaw->vSize.y * m_pSaw->m_fSize,
			m_pSaw->vSize.z);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_pSaw->m_fAngle));

		D3DXMatrixTranslation(&matTrans,
			m_pSaw->vPos.x,
			m_pSaw->vPos.y,
			m_pSaw->vPos.z);
		m_pSaw->matWorld = matScale * matRotZ * matTrans * matRotZ_A * matTrans_A;
		tempMat = matScale * matTrans * matRotZ_A;
		break;
	default:
		break;
	}
}

void CKillObject::Render()
{
	float fCenterX = 0.f, fCenterY = 0.f;
	float fSawColX = 0.f, fSawColY = 0.f;
	TCHAR szIndexNum[MIN_STR] = L"";
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		pSawTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
		NULL_CHECK(pSawTexInfo);

		fCenterX = pSawTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSaw->matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case SAW_MOVE:
		pSawTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
		NULL_CHECK(pSawTexInfo);

		fCenterX = pSawTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSaw->matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		pSawATexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW_PIVOT", 0);
		NULL_CHECK_MSG(pSawATexInfo, L"test");

		fCenterX = pSawATexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawATexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSawAngle->matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawATexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		break;
	case SAW_MOVE_ANGLE:
		pSawTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
		NULL_CHECK(pSawTexInfo);

		fCenterX = pSawTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSaw->matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		pSawATexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW_PIVOT", 0);
		NULL_CHECK_MSG(pSawATexInfo, L"test");

		fCenterX = 13;
		fCenterY = 13;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSawAngle->matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawATexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		break;
	default:
		break;
	}
	fSawColX = pSawTexInfo->tImgInfo.Width * 0.5f * m_fSize;
	fSawColY = pSawTexInfo->tImgInfo.Height * 0.5f * m_fSize;
	m_pSaw->Col = { (int)(m_pSaw->vPos.x - fSawColX) , (int)(m_pSaw->vPos.y - fSawColY),
		(int)(m_pSaw->vPos.x + fSawColX), (int)(m_pSaw->vPos.y + fSawColY) };
}

HRESULT CKillObject::Initialize()
{
	float fX = 0.f, fY = 0.f;
	select = false;
	endflag = false;
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		m_pSaw = new KILLOBJ;
		m_pSaw->vPos = { fX, fY, 0.f };
		m_pSaw->vSize = { 1.f, 1.f, 0.f };
		m_pSaw->byDrawID = 0;
		m_pSaw->obj_Type = SAW;
		m_pSaw->m_fAngle = 0.f;
		m_pSaw->m_fSize = 1.f;
		m_pSaw->Col = {};
		D3DXMatrixIdentity(&m_pSaw->matWorld); // 다이렉트 항등행렬 함수
		m_pSawAngle = new KILLOBJ;
		m_pSawShoter = new KILLOBJ;
		break;
	case SAW_MOVE:
		m_pSaw = new KILLOBJ;
		m_pSaw->vPos = { 126, 0, 0.f };
		m_pSaw->vSize = { 1.f, 1.f, 0.f };
		m_pSaw->byDrawID = 0;
		m_pSaw->obj_Type = SAW;
		m_pSaw->m_fAngle = 0.f;
		m_pSaw->m_fSize = 1.f;
		m_pSaw->Col = {};
		D3DXMatrixIdentity(&m_pSaw->matWorld); // 다이렉트 항등행렬 함수
		m_pSawAngle = new KILLOBJ;
		m_pSawAngle->vPos = { fX, fY, 0.f };
		m_pSawAngle->vSize = { 1.f, 1.f, 0.f };
		m_pSawAngle->byDrawID = 0;
		m_pSawAngle->obj_Type = SAW_MOVE_ANGLE;
		m_pSawAngle->m_fAngle = 0.f;
		m_pSawAngle->m_fSize = 1.f;
		m_pSawAngle->Col = {};
		D3DXMatrixIdentity(&m_pSawAngle->matWorld); // 다이렉트 항등행렬 함수
		m_pSawShoter = new KILLOBJ;
		tempPos = { 126, 0 ,0.f };
		break;
	case SAW_MOVE_ANGLE:
		m_pSaw = new KILLOBJ;
		m_pSaw->vPos = { 252, 24, 0.f };
		m_pSaw->vSize = { 1.f, 1.f, 0.f };
		m_pSaw->byDrawID = 0;
		m_pSaw->obj_Type = SAW;
		m_pSaw->m_fAngle = 0.f;
		m_pSaw->m_fSize = 1.f;
		m_pSaw->Col = {};
		D3DXMatrixIdentity(&m_pSaw->matWorld); // 다이렉트 항등행렬 함수
		m_pSawAngle = new KILLOBJ;
		m_pSawAngle->vPos = { fX, fY, 0.f };
		m_pSawAngle->vSize = { 1.f, 1.f, 0.f };
		m_pSawAngle->byDrawID = 0;
		m_pSawAngle->obj_Type = SAW_MOVE_ANGLE;
		m_pSawAngle->m_fAngle = 0.f;
		m_pSawAngle->m_fSize = 1.f;
		m_pSawAngle->Col = {};
		D3DXMatrixIdentity(&m_pSawAngle->matWorld); // 다이렉트 항등행렬 함수
		m_pSawShoter = new KILLOBJ;

		break;
	default:
		break;
	}

	return S_OK;
}

void CKillObject::Release()
{
	SafeDelete(m_pSaw);
	SafeDelete(m_pSawAngle);
	SafeDelete(m_pSawShoter);
}

void CKillObject::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption, const float & angle, const float & changex, const float & changey, const RECT * col)
{

}

void CKillObject::MiniRender()
{
	float fCenterX = 0.f, fCenterY = 0.f;
	TCHAR szIndexNum[MIN_STR] = L"";
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		pSawTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
		NULL_CHECK(pSawTexInfo);

		fCenterX = pSawTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSaw->matMiniWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case SAW_MOVE:
		break;
	case SAW_MOVE_ANGLE:
		pSawTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
		NULL_CHECK(pSawTexInfo);

		fCenterX = pSawTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pSawTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSaw->matMiniWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		pSawATexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW_PIVOT", m_pSaw->byDrawID);
		NULL_CHECK(pSawATexInfo);

		fCenterX = 13;
		fCenterY = 13;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_pSawAngle->matMiniWorld);
		m_pDeviceMgr->GetSprite()->Draw(pSawATexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void CKillObject::LineRender()
{

	D3DXMATRIX matScale, matTrans, matRotZ;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"KillObject", L"SAW", m_pSaw->byDrawID);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f * m_fSize;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f * m_fSize;

	D3DXVECTOR2 v1[5];
	D3DXVECTOR3 m_vConvert[4];
	D3DXVECTOR3 tempPos = {};
	D3DXVECTOR3 tempSize = {};
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		tempPos = m_pSaw->vPos;
	case SAW_MOVE:
		//cout << m_pSaw->Col.left << " , " << m_pSaw->Col.right << endl;
		D3DXMatrixDecompose(&tempSize, &D3DXQUATERNION(), &tempPos, &tempMat);
		tempPos = { tempPos.x + m_pSawAngle->vPos.x  , tempPos.y + m_pSawAngle->vPos.y  ,0.f };
		break;
	case SAW_MOVE_ANGLE:
		D3DXMatrixDecompose(&tempSize, &D3DXQUATERNION(), &tempPos, &tempMat);
		tempPos = { tempPos.x + m_pSawAngle->vPos.x  , tempPos.y + m_pSawAngle->vPos.y  ,0.f };
		break;
	}


	//오브젝트 테두리
	m_vConvert[0] = { tempPos.x - fCenterX - CScrollMgr::GetScrollPos().x,tempPos.y - fCenterY - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[1] = { tempPos.x - fCenterX - CScrollMgr::GetScrollPos().x,tempPos.y + fCenterY - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[2] = { tempPos.x + fCenterX - CScrollMgr::GetScrollPos().x,tempPos.y + fCenterY - CScrollMgr::GetScrollPos().y, 0.f };
	m_vConvert[3] = { tempPos.x + fCenterX - CScrollMgr::GetScrollPos().x,tempPos.y - fCenterY - CScrollMgr::GetScrollPos().y , 0.f };
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

void CKillObject::SaveKillObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath)
{
	DWORD tempdwBytes = 0;
	WriteFile(hFile, &obj_Type, sizeof(KILLOBJ_TYPE), &dwBytes, nullptr);
	WriteFile(hFile, tempPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	WriteFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	WriteFile(hFile, &select, sizeof(bool), &dwBytes, nullptr);
	WriteFile(hFile, &endflag, sizeof(bool), &dwBytes, nullptr);
	WriteFile(hFile, &moveflag, sizeof(bool), &dwBytes, nullptr);
	WriteFile(hFile, &m_fSize, sizeof(float), &dwBytes, nullptr);
	WriteFile(hFile, &m_fAngle, sizeof(float), &dwBytes, nullptr);
	WriteFile(hFile, m_pSaw, sizeof(KILLOBJ), &dwBytes, nullptr);
	WriteFile(hFile, m_pSawAngle, sizeof(KILLOBJ), &dwBytes, nullptr);
	WriteFile(hFile, m_pSawShoter, sizeof(KILLOBJ), &dwBytes, nullptr);
}

CKillObject* CKillObject::LoadKillObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath)
{
	CKillObject* tTile = new CKillObject;
	DWORD tempdwBytes = 0;
	ReadFile(hFile, &tTile->obj_Type, sizeof(KILLOBJ_TYPE), &dwBytes, nullptr);
	ReadFile(hFile, tTile->tempPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, tTile->vPos, sizeof(D3DXVECTOR3), &dwBytes, nullptr);
	ReadFile(hFile, &tTile->select, sizeof(bool), &dwBytes, nullptr);
	ReadFile(hFile, &tTile->endflag, sizeof(bool), &dwBytes, nullptr);
	ReadFile(hFile, &tTile->moveflag, sizeof(bool), &dwBytes, nullptr);
	ReadFile(hFile, &tTile->m_fSize, sizeof(float), &dwBytes, nullptr);
	ReadFile(hFile, &tTile->m_fAngle, sizeof(float), &dwBytes, nullptr);
	KILLOBJ tempSaw = {};
	ReadFile(hFile, &tempSaw, sizeof(KILLOBJ), &dwBytes, nullptr);
	tTile->m_pSaw = new KILLOBJ(tempSaw);

	KILLOBJ tempSawA = {};
	ReadFile(hFile, &tempSawA, sizeof(KILLOBJ), &dwBytes, nullptr);
	tTile->m_pSawAngle = new KILLOBJ(tempSawA);

	KILLOBJ tempSawS = {};
	ReadFile(hFile, &tempSawS, sizeof(KILLOBJ), &dwBytes, nullptr);
	tTile->m_pSawShoter = new KILLOBJ(tempSawS);
	return tTile;
}

void CKillObject::SetSize(float size)
{
}

void CKillObject::SetSawChange()
{
	m_pSaw->byDrawID++;
	if (m_pSaw->byDrawID >= 3)
	{
		m_pSaw->byDrawID = 3;
	}
}

void CKillObject::SetReplay(bool flag)
{
	m_bReplay = true;
}

const int & CKillObject::GetSawColSize() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return (m_pSaw->Col.right - m_pSaw->Col.left) / 2;
}

const D3DXVECTOR3 & CKillObject::GetSawPos() const
{
	D3DXVECTOR3 tempPos = {};
	// TODO: 여기에 반환 구문을 삽입합니다.
	switch (obj_Type)
	{
	case NO_OBJ:
		break;
	case SAW:
		return m_pSaw->vPos;
	case SAW_MOVE:
		//cout << m_pSaw->Col.left << " , " << m_pSaw->Col.right << endl;
		tempPos = {};
		D3DXMatrixDecompose(&D3DXVECTOR3(), &D3DXQUATERNION(), &tempPos, &tempMat);
		tempPos = { tempPos.x + m_pSawAngle->vPos.x  , tempPos.y + m_pSawAngle->vPos.y  ,0.f };
		return tempPos;
	case SAW_MOVE_ANGLE:
		tempPos = {};
		D3DXMatrixDecompose(&D3DXVECTOR3(), &D3DXQUATERNION(), &tempPos, &tempMat);
		tempPos = { tempPos.x + m_pSawAngle->vPos.x  , tempPos.y + m_pSawAngle->vPos.y  ,0.f };
		return tempPos;
	}
	return m_pSaw->vPos;
}

CKillObject * CKillObject::Create(KILLOBJ_TYPE obj)
{
	CKillObject* pInstance = new CKillObject;
	if (obj != NO_OBJ)
		pInstance->obj_Type = obj;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CKillObject::GetReplayInfo(REPLAY_KILL_INFO info)
{
	*m_pSaw = info.m_pSaw;
	*m_pSawAngle = info.m_pSawAngle;
	*m_pSawShoter = info.m_pSawAngle;
	moveflag = info.moveflag;
	tempPos = info.tempPos;
}

REPLAY_KILL_INFO CKillObject::SetReplayInfo()
{
	REPLAY_KILL_INFO temp;
	temp.m_pSaw = *m_pSaw;
	temp.m_pSawAngle = *m_pSawAngle;
	temp.m_pSawShoter = *m_pSawAngle;
	temp.moveflag = moveflag;
	temp.tempPos = tempPos;
	return temp;
}
