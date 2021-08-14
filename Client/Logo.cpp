#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
	: m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CLogo::~CLogo()
{
	Release();
}

int CLogo::Update()
{
	m_tLogo_Saw.m_fAngle -= m_pTimeMgr->GetDelta() * 200.f;
	if (m_pKeyMgr->KeyDown(KEY_DOWN) || m_pKeyMgr->KeyDown(KEY_UP))
	{
		m_bStartflag = !m_bStartflag;
	}


	if (m_pKeyMgr->KeyDown(KEY_RETURN) || m_pKeyMgr->KeyDown(KEY_SPACE))
	{
		if (m_bStartflag)
		{
			m_bTestflag = true;
		}
		else
		{
			PostQuitMessage(0);
		}
	}

	
	if (m_bStartflag)
	{
		m_tLogo_Now_Select.vPos = { WINCX * 0.52f ,WINCY * 0.4f ,0.f };
		m_tLogo_Start_Game.vPos = { WINCX * 0.56f ,WINCY * 0.4f ,0.f };
		m_tLogo_Exit_Game.vPos = { WINCX * 0.54f ,WINCY * 0.5f ,0.f };
	}
	else
	{
		m_tLogo_Now_Select.vPos = { WINCX * 0.52f ,WINCY * 0.5f ,0.f };
		m_tLogo_Start_Game.vPos = { WINCX * 0.54f ,WINCY * 0.4f ,0.f };
		m_tLogo_Exit_Game.vPos = { WINCX * 0.56f ,WINCY * 0.5f ,0.f };
	}
	
	for (int i = 0; i < BACK1X; i++)
	{
		for (int j = 0; j < BACK1Y; j++)
		{
			m_tLogo_Back1[i][j].vPos.y += m_pTimeMgr->GetDelta() * 100.f;
			if (m_tLogo_Back1[i][j].vPos.y >= WINCY + 70)
			{
				if (i % 2 == 0)
				{
					m_tLogo_Back1[i][j].vPos.y = -70;
				}
				else
				{
					m_tLogo_Back1[i][j].vPos.y = -40;
				}

			
			}
		}
	}

	return NO_EVENT;
}

void CLogo::LateUpdate()
{
	D3DXMATRIX matScale, matTrans, matRotZ;
	LateUpdateSprite(m_tLogo_Saw,1.f);
	LateUpdateSprite(m_tLogo_Face, 1.f);
	LateUpdateSprite(m_tLogo_Title, 1.f);
	LateUpdateSprite(m_tLogo_Back_Bottom, 1.f);
	LateUpdateSprite(m_tLogo_Back, 1.f);
	LateUpdateSprite(m_tLogo_Cur1, 1.f);
	LateUpdateSprite(m_tLogo_Cur2, -1.f);
	LateUpdateSprite(m_tLogo_Select, 1.f);
	LateUpdateSprite(m_tLogo_Now_Select, 1.f);
	LateUpdateSprite(m_tLogo_Start_Game, 1.f);
	LateUpdateSprite(m_tLogo_Exit_Game, 1.f);
	for (int i = 0; i < BACK1X; i++)
	{
		for (int j = 0; j < BACK1Y; j++)
		{
			LateUpdateSprite(m_tLogo_Back1[i][j], 1.f);
		}
	}

}

void CLogo::Render()
{
	RenderSprite(m_tLogo_Back.matWorld, L"LOGO", L"BACK",255);
	
	for (int i = 0; i < BACK1X; i++)
	{
		for (int j = 0; j < BACK1Y; j++)
		{
			RenderSprite(m_tLogo_Back1[i][j].matWorld, L"LOGO", L"BACK1", 255);
		}
	}
	RenderSprite(m_tLogo_Cur1.matWorld, L"LOGO", L"CUR", 255);
	RenderSprite(m_tLogo_Cur2.matWorld, L"LOGO", L"CUR", 255);

	RenderSprite(m_tLogo_Back.matWorld, L"LOGO", L"BACK", 230);
	RenderSprite(m_tLogo_Saw.matWorld, L"LOGO", L"SAW",255);
	RenderSprite(m_tLogo_Face.matWorld, L"LOGO", L"FACE",255);
	RenderSprite(m_tLogo_Title.matWorld, L"LOGO", L"TITLE", 255);
	RenderSprite(m_tLogo_Select.matWorld, L"LOGO", L"SELECT",255);
	RenderSprite(m_tLogo_Back_Bottom.matWorld, L"LOGO", L"BACK_BOTTOM", 255);
	RenderSprite(m_tLogo_Now_Select.matWorld, L"LOGO", L"NOW_SELECT", 255);
	RenderSprite(m_tLogo_Start_Game.matWorld, L"LOGO", L"START_GAME", 255);
	RenderSprite(m_tLogo_Exit_Game.matWorld, L"LOGO", L"EXIT_GAME", 255);

	if (m_bTestflag)
	{
		if (m_pSceneMgr->SceneChangeSaw(true))
		{
			m_pSoundMgr->StopAll();
			m_pSceneMgr->SceneChange(SCENE_LOGO, SCENE_STAGE_SELECT);
		}
	}
}

void CLogo::LineRender()
{

}

HRESULT CLogo::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// Cube Texture
	HRESULT hr;
	if (!m_bTextureLoad)
	{
		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_BACK.png",
			L"LOGO", L"BACK", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_BACK Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_BACK_BOTTOM.png",
			L"LOGO", L"BACK_BOTTOM", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_BACK_BOTTOM Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_BACK1.png",
			L"LOGO", L"BACK1", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_BACK1 Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_CUR.png",
			L"LOGO", L"CUR", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_CUR Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_FACE.png",
			L"LOGO", L"FACE", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_FACE Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_SAW.png",
			L"LOGO", L"SAW", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_SAW Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_TITLE.png",
			L"LOGO", L"TITLE", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_TITLE Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_SELECT.png",
			L"LOGO", L"SELECT", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_SELECT Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_NOW_SELECT.png",
			L"LOGO", L"NOW_SELECT", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_NOW_SELECT Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_START_GAME.png",
			L"LOGO", L"START_GAME", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_START_GAME Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/TITLE/LOGO_EXIT_GAME.png",
			L"LOGO", L"EXIT_GAME", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"LOGO_EXIT_GAME Texture Load Failed", E_FAIL);
	}

	float fSize = 1.f;
	m_tLogo_Saw.vSize = { 1.2f,1.2f,0.f };
	m_tLogo_Face.vSize = { 1.2f,1.2f,0.f };
	m_tLogo_Back.vSize = { fSize,fSize,0.f };
	m_tLogo_Back_Bottom.vSize = { fSize,fSize*1.1f,0.f };
	m_tLogo_Title.vSize = { 0.8f,0.8f,0.f };
	m_tLogo_Cur1.vSize = { 0.723f,0.723f,0.f };
	m_tLogo_Cur2.vSize = { 0.723f,0.723f,0.f };
	m_tLogo_Select.vSize = { 1.1f,1.1f,0.f };
	m_tLogo_Now_Select.vSize = { fSize ,fSize ,0.f};
	m_tLogo_Exit_Game.vSize = { fSize ,fSize ,0.f };
	m_tLogo_Start_Game.vSize = { fSize ,fSize ,0.f };


	m_tLogo_Saw.vPos = { WINCX * 0.33f,WINCY * 0.55f + 30.f,0.f };
	m_tLogo_Face.vPos = { WINCX * 0.33f ,WINCY * 0.55f + 30.f,0.f };
	m_tLogo_Back.vPos = { WINCX * 0.5f , WINCY * 0.5f + 30.f , 0.f};
	m_tLogo_Back_Bottom.vPos = { WINCX * 0.5f, WINCY *0.965f,0.f };
	m_tLogo_Title.vPos = { WINCX * 0.5f , WINCY/8 , 0.f };
	m_tLogo_Select.vPos = { WINCX * 0.75f , WINCY * 0.6f,0.f};
	m_tLogo_Now_Select.vPos = { WINCX * 0.5f ,WINCY * 0.6f ,0.f };
	m_tLogo_Start_Game.vPos = { WINCX * 0.54f ,WINCY * 0.4f ,0.f };
	m_tLogo_Exit_Game.vPos =  { WINCX * 0.54f ,WINCY * 0.5f ,0.f };
	


	const TEX_INFO* pTexInfo = nullptr;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"LOGO", L"CUR", 0);
	NULL_CHECK_RETURN(pTexInfo,false);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f * 0.6f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f * 0.6f;

	m_tLogo_Cur1.vPos = { fCenterX,WINCY * 0.5f + 30.f,0.f };
	m_tLogo_Cur2.vPos = { WINCX - fCenterX,WINCY * 0.5f + 30.f,0.f };

	m_tLogo_Face.m_fAngle = -10.f;

	m_bStartflag = true;



	pTexInfo = m_pTextureMgr->GetTexInfo(L"LOGO", L"BACK1", 0);
	NULL_CHECK_RETURN(pTexInfo, false);

	for (int i = 0; i < BACK1X; i++)
	{
		for (int j = 0; j < BACK1Y; j++)
		{
			float tempSize = 0.7f;
			fCenterX = pTexInfo->tImgInfo.Width * tempSize;
			fCenterY = pTexInfo->tImgInfo.Height * tempSize;

			float tempY = 0.f;
			m_tLogo_Back1[i][j].vSize = { tempSize ,tempSize ,0.f};
			if (i % 2 == 0)
			{
				m_tLogo_Back1[i][j].m_fAngle = 45.f*j;
			}
			else
			{
				tempY = 50.f;
				m_tLogo_Back1[i][j].m_fAngle = -45.f*j;
			}
			m_tLogo_Back1[i][j].vPos = { (float)(fCenterX * 1.5f * i + 100),(float)(j*fCenterY * 1.5f + tempY), 0.f};
		}
	}
	m_pSoundMgr->PlayBGM(L"smbtitleloop.wav");
	m_pSoundMgr->PlaySound(L"SMBTest.wav", SOUNDMGR::TITLE);
	cout << "test" << endl;
	return S_OK;
}

void CLogo::Release()
{
}

CLogo* CLogo::Create(bool flag)
{
	CLogo* pInstance = new CLogo;
	pInstance->m_bTextureLoad = flag;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	
	return pInstance;
}

void CLogo::RenderSprite(D3DXMATRIX& tempMat, const TCHAR * type1, const TCHAR * type2, int Alpha)
{
	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f;
	float fCenterY = 0.f;

	pTexInfo = m_pTextureMgr->GetTexInfo(type1, type2, 0);
	NULL_CHECK(pTexInfo);
	if (type2 == L"START_GAME" || type2 == L"EXIT_GAME")
	{
		fCenterX = 0;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	}
	else
	{
		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	}
	m_pDeviceMgr->GetSprite()->SetTransform(&tempMat);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(Alpha, 255, 255, 255));

}

void CLogo::LateUpdateSprite(LOGO_INFO& info, float ChangeX)
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
