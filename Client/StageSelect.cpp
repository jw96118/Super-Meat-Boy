#include "stdafx.h"
#include "StageSelect.h"

CStageSelect::CStageSelect() : m_pKeyMgr(CKeyMgr::GetInstance())
{
}

CStageSelect::~CStageSelect()
{
}

int CStageSelect::Update()
{
	m_tSelect_Saw1.m_fAngle -= m_pTimeMgr->GetDelta() * 200.f;
	m_tSelect_Saw2.m_fAngle -= m_pTimeMgr->GetDelta() * 200.f;
	if (!m_bGoStage)
	{
		if (!m_bMoveFlag)
		{
			if (m_pKeyMgr->KeyDown(KEY_LEFT))
			{
				if (m_iSelectCount > 0)
				{
					m_iSelectCount--;
					moveLength = -150;
					m_bMoveFlag = true;
				}
			}
			else if (m_pKeyMgr->KeyDown(KEY_RIGHT))
			{
				if (m_iSelectCount < 2)
				{
					m_iSelectCount++;
					moveLength = 150;
					m_bMoveFlag = true;
				}
			}
			if (m_pKeyMgr->KeyDown(KEY_RETURN) || m_pKeyMgr->KeyDown(KEY_SPACE))
			{
				m_bGoStage = true;

			}
		}
		else
		{
			if (moveLength < 0)
			{
				if (m_iSelectCount == 0)
				{
					if (m_tSelect_Player.vPos.x <= WINCX * 0.4f)
					{
						m_tSelect_Player.vPos.x = WINCX * 0.4f;
						m_bMoveFlag = false;
					}
				}
				if (m_iSelectCount == 1)
				{
					if (m_tSelect_Player.vPos.x <= WINCX * 0.5f)
					{
						m_tSelect_Player.vPos.x = WINCX * 0.5f;
						m_bMoveFlag = false;
					}
				}
			}
			else
			{
				if (m_iSelectCount == 1)
				{
					if (m_tSelect_Player.vPos.x >= WINCX * 0.5f)
					{
						m_tSelect_Player.vPos.x = WINCX * 0.5f;
						m_bMoveFlag = false;
					}
				}
				if (m_iSelectCount == 2)
				{
					if (m_tSelect_Player.vPos.x >= WINCX * 0.6f)
					{
						m_tSelect_Player.vPos.x = WINCX * 0.6f;
						m_bMoveFlag = false;
					}
				}
			}
			m_tSelect_Player.vPos.x += m_pTimeMgr->GetDelta() * moveLength;
		}
	}
	m_tFrame_Player.fCurFrame += m_tFrame_Player.fMaxFrame * m_pTimeMgr->GetDelta();

	if (m_tFrame_Player.fMaxFrame <= m_tFrame_Player.fCurFrame)
	{
		m_tFrame_Player.fCurFrame = 0.f;
	}
	if (m_bGoStage)
	{

		if (!m_bChangeX)
		{
			if (m_tSelect_Player.vSize.x >= 0.2f)
			{
				m_tSelect_Player.vSize.y += m_pTimeMgr->GetDelta() * 2.f;
				m_tSelect_Player.vSize.x -= m_pTimeMgr->GetDelta() * 2.f;
			}
			else
			{
				m_bChangeX = true;
			}
		}
		else
		{
			if (m_tSelect_Player.vSize.x <= 2.f)
			{

				if (m_tSelect_Player.vSize.y > 0)
				{
					m_tSelect_Player.vPos.y += m_pTimeMgr->GetDelta() * 80.f;
					m_tSelect_Player.vSize.y -= m_pTimeMgr->GetDelta() * 2.f;
					m_tSelect_Player.vSize.x += m_pTimeMgr->GetDelta() * 2.f;
				}
				if (m_tSelect_Player.vSize.x >= 0.3f)
				{
					if (!m_bTestflag)
					{
						m_tFrame_Blood.fCurFrame += m_tFrame_Blood.fMaxFrame * m_pTimeMgr->GetDelta();
						if (!m_bSceneMeat)
						{
							m_pSoundMgr->PlaySound(L"Meat_jumps3.wav", SOUNDMGR::SCENE);
							m_bSceneMeat = true;
						}
						if (m_tFrame_Blood.fMaxFrame <= m_tFrame_Blood.fCurFrame)
						{
							m_bTestflag = true;

							m_tFrame_Blood.fCurFrame = m_tFrame_Blood.fMaxFrame - 1;
						}
					}
				}
			}
		}

	}
	else
	{
		m_tSelect_Blood.vPos = m_tSelect_Player.vPos;
		m_tSelect_Shadow.vPos = { m_tSelect_Player.vPos.x, m_tSelect_Player.vPos.y + PlayerImageY,0.f };
	}
	return 0;
}

void CStageSelect::LateUpdate()
{
	LateUpdateSprite(m_tSelect_Back, 1.0f);
	LateUpdateSprite(m_tSelect_Saw1, 1.0f);
	LateUpdateSprite(m_tSelect_Saw2, 1.0f);
	LateUpdateSprite(m_tSelect_Stage1, 1.0f);
	LateUpdateSprite(m_tSelect_Stage2, 1.0f);
	LateUpdateSprite(m_tSelect_Stage3, 1.0f);
	LateUpdateSprite(m_tSelect_Stage_Line1, 1.0f);
	LateUpdateSprite(m_tSelect_Stage_Line2, 1.0f);
	LateUpdateSprite(m_tSelect_Player, 1.0f);
	LateUpdateSprite(m_tSelect_Back_Front, 1.0f);
	LateUpdateSprite(m_tSelect_Blood, 1.0f);
	LateUpdateSprite(m_tSelect_Shadow, 1.0f);
}

void CStageSelect::Render()
{
	if (!m_InitSaw)
	{
		if (m_pSceneMgr->SceneChangeSaw(false))
		{
			m_InitSaw = true;
		}
	}

	if (m_bTestflag)
	{
		if (m_pSceneMgr->SceneChangeSaw(true))
		{
			m_pSoundMgr->StopAll();
			m_pSceneMgr->SceneChange(SCENE_STAGE_SELECT, SCENE_STAGE, m_iSelectCount);
			return;
		}
	}

	RenderSprite(m_tSelect_Back.matWorld, L"SELECT", L"BACK", 255);


	RenderSprite(m_tSelect_Saw1.matWorld, L"SELECT", L"SAW", 255);
	RenderSprite(m_tSelect_Saw2.matWorld, L"SELECT", L"SAW", 255);

	RenderSprite(m_tSelect_Stage_Line1.matWorld, L"SELECT", L"STAGE_LINE", 255);
	RenderSprite(m_tSelect_Stage_Line2.matWorld, L"SELECT", L"STAGE_LINE", 255);
	if (g_bClaer[STAGE_1])
		RenderSprite(m_tSelect_Stage1.matWorld, L"SELECT", L"CLEAR", 255);
	else
		RenderSprite(m_tSelect_Stage1.matWorld, L"SELECT", L"NO_CLEAR", 255);
	if (g_bClaer[STAGE_2])
		RenderSprite(m_tSelect_Stage2.matWorld, L"SELECT", L"CLEAR", 255);
	else
		RenderSprite(m_tSelect_Stage2.matWorld, L"SELECT", L"NO_CLEAR", 255);
	if (g_bClaer[STAGE_3])
		RenderSprite(m_tSelect_Stage3.matWorld, L"SELECT", L"CLEAR", 255);
	else
		RenderSprite(m_tSelect_Stage3.matWorld, L"SELECT", L"NO_CLEAR", 255);

	RenderSprite(m_tSelect_Shadow.matWorld, L"SELECT", L"SHADOW", 255);
	RenderSprite(m_tSelect_Player.matWorld, L"SELECT", L"PLAYER", 255, m_tFrame_Player.fCurFrame);


	RenderSprite(m_tSelect_Blood.matWorld, L"SELECT", L"BLOOD", 255, m_tFrame_Blood.fCurFrame);


	RenderSprite(m_tSelect_Back_Front.matWorld, L"SELECT", L"FRONT", 255);


	swprintf_s(m_szTime, L"%.2f", g_fTime[m_iSelectCount]);



	// 다이렉트 폰트 출력
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX * 0.72f, WINCY * 0.885f, 0.f);

	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);


	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_szTime, /* 출력할 문자열 */
		lstrlen(m_szTime), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		D3DCOLOR_ARGB(255, 0, 0, 0));

	D3DXMATRIX matPos;
	D3DXMATRIX matSize;
	D3DXMatrixScaling(&matSize, 2.f, 2.f, 0.f);
	D3DXMatrixTranslation(&matPos, WINCX * 0.4f, WINCY * 0.82f, 0.f);

	m_pDeviceMgr->GetSprite()->SetTransform(&(matSize *matPos));

	switch (m_iSelectCount)
	{
	case 0:
		m_szStage = L"Stage 1";
		break;
	case 1:
		m_szStage = L"Stage 2";
		break;
	case 2:
		m_szStage = L"Stage 3";
		break;
	}
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_szStage, /* 출력할 문자열 */
		lstrlen(m_szStage), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		D3DCOLOR_ARGB(255, 0, 0, 0));


}

void CStageSelect::LineRender()
{
}

HRESULT CStageSelect::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// Cube Texture
	HRESULT hr;
	if (!m_bTextureLoad)
	{
		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Stage_Select_Back.png",
			L"SELECT", L"BACK", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Back Object Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Stage_Select_Front.png",
			L"SELECT", L"FRONT", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Front Object Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Stage_Select_Saw.png",
			L"SELECT", L"SAW", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Saw Object Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/No_Clear.png",
			L"SELECT", L"NO_CLEAR", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"No_Clear Object Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Clear.png",
			L"SELECT", L"CLEAR", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Clear Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Stage_Line.png",
			L"SELECT", L"STAGE_LINE", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Stage_Line Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Select_Ani%d.png",
			L"SELECT", L"PLAYER", 10);
		FAILED_CHECK_MSG_RETURN(hr, L"Select_Ani Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/Select_Blood%d.png",
			L"SELECT", L"BLOOD", 7);
		FAILED_CHECK_MSG_RETURN(hr, L"Select_Blood Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/SELECT/menumeatboy_179.png",
			L"SELECT", L"SHADOW", 7);
		FAILED_CHECK_MSG_RETURN(hr, L"menumeatboy_179 Texture Load Failed", E_FAIL);
	}
	float BackfSize = 1.f;
	float fSize = 0.5f;

	m_tSelect_Back.vSize = { BackfSize,BackfSize,0.f };
	m_tSelect_Back_Front.vSize = { BackfSize,BackfSize,0.f };
	m_tSelect_Saw1.vSize = { 0.3f,0.3f,0.f };
	m_tSelect_Saw2.vSize = { 0.3f,0.3f,0.f };
	m_tSelect_Stage1.vSize = { fSize,fSize,0.f };
	m_tSelect_Stage2.vSize = { fSize,fSize,0.f };
	m_tSelect_Stage3.vSize = { fSize,fSize,0.f };
	m_tSelect_Stage_Line1.vSize = { fSize,fSize,0.f };
	m_tSelect_Stage_Line2.vSize = { fSize,fSize,0.f };
	m_tSelect_Player.vSize = { 0.4f ,0.4f ,0.f };
	m_tSelect_Blood.vSize = m_tSelect_Player.vSize;
	m_tSelect_Shadow.vSize = m_tSelect_Player.vSize;

	m_tSelect_Back.vPos = { WINCX * 0.5f,WINCY * 0.5f,0.f };
	m_tSelect_Back_Front.vPos = { WINCX * 0.5f,WINCY * 0.5f,0.f };
	m_tSelect_Saw1.vPos = { 250.f, 35.f,0.f };
	m_tSelect_Saw2.vPos = { 1080.f,125.f,0.f };
	m_tSelect_Stage1.vPos = { WINCX * 0.4f,WINCY * 0.5f,0.f };
	m_tSelect_Stage2.vPos = { WINCX * 0.5f,WINCY * 0.5f,0.f };
	m_tSelect_Stage3.vPos = { WINCX * 0.6f,WINCY * 0.5f,0.f };
	m_tSelect_Stage_Line1.vPos = { WINCX * 0.45f,WINCY * 0.5f,0.f };
	m_tSelect_Stage_Line2.vPos = { WINCX * 0.55f,WINCY * 0.5f,0.f };
	m_tSelect_Player.vPos = { WINCX * 0.4f ,WINCY * 0.47f ,0.f };

	m_tSelect_Blood.vPos = m_tSelect_Player.vPos;
	m_tSelect_Shadow.vPos = m_tSelect_Player.vPos;

	m_tFrame_Player.fCurFrame = 0.f;
	m_tFrame_Player.fMaxFrame = 10.f;
	m_tFrame_Blood.fCurFrame = 0.f;
	m_tFrame_Blood.fMaxFrame = 7.f;
	m_pSoundMgr->StopAll();
	m_pSoundMgr->PlayBGM(L"forestmenuloop.wav");
	m_bMoveFlag = false;

	const TEX_INFO* pTexInfo = nullptr;
	pTexInfo = m_pTextureMgr->GetTexInfo(L"SELECT", L"PLAYER", 0);


	PlayerImageY = pTexInfo->tImgInfo.Height * 0.5f * 0.4f;
	m_pObjectMgr->DeleteMeatBand();
	m_bSceneMeat = false;
	return S_OK;
}

void CStageSelect::Release()
{
}

void CStageSelect::RenderSprite(D3DXMATRIX & tempMat, const TCHAR * type1, const TCHAR * type2, int Alpha, float frame)
{
	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f;
	float fCenterY = 0.f;

	pTexInfo = m_pTextureMgr->GetTexInfo(type1, type2, frame);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&tempMat);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(Alpha, 255, 255, 255));

}

void CStageSelect::LateUpdateSprite(LOGO_INFO & info, float ChangeX)
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	D3DXMatrixScaling(&matScale,
		info.vSize.x * ChangeX,
		info.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(info.m_fAngle));

	D3DXMatrixTranslation(&matTrans,
		info.vPos.x,
		info.vPos.y,
		0.f); // 다이렉트 이동행렬 함수

	info.matWorld = matScale * matRotZ * matTrans;
}

CStageSelect* CStageSelect::Create(bool flag)
{
	CStageSelect* pInstance = new CStageSelect;
	pInstance->m_bTextureLoad = flag;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}