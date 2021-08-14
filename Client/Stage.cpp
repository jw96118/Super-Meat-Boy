#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"
#include "TileObject.h"
#include "Bandage.h"
#include "ScrollMgr.h"
CStage::CStage()
	: m_pObjectMgr(CObjectMgr::GetInstance()) , m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{

	if (m_pObjectMgr->Update()== NEXT_STAGE)
	{
		g_bClaer[m_eNowStageInfo] = true;
		m_pObjectMgr->PlayerReplay();
		
	}
	if (m_pKeyMgr->KeyDown(KEY_SPACE))
	{
		if (dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->GetReplayEnd())
		{
			m_bTestflag = true;
		}

	}
	if (!dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->GetReplay())
	{
		g_fTime[m_eNowStageInfo] += m_pTimeMgr->GetDelta();
	}
	else
	{
		if (!dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->GetReplayEnd())
		{
			m_fReplayTime += m_pTimeMgr->GetDelta();
		}
		else
		{
			m_fReplayTime = g_fTime[m_eNowStageInfo];
		}
	}
	return NO_EVENT;
}

void CStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale,
		m_tTimeInfo.vSize.x ,
		m_tTimeInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수

	D3DXMatrixTranslation(&matTrans,
		m_tTimeInfo.vPos.x,
		m_tTimeInfo.vPos.y,
		0.f); // 다이렉트 이동행렬 함수

	m_tTimeInfo.matWorld = matScale  * matTrans;
}

void CStage::Render()
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
			m_pSceneMgr->SceneChange(SCENE_STAGE, SCENE_STAGE_SELECT);
			return;
		}
	}


	m_pObjectMgr->Render();



	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f;
	float fCenterY = 0.f;

	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"TIME", 0);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tTimeInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	if (!dynamic_cast<CPlayer*>(m_pObjectMgr->GetPlayer())->GetReplay())
	{
		swprintf_s(m_szTime, L"%.2f", g_fTime[m_eNowStageInfo]);
	}
	else
	{
		swprintf_s(m_szTime, L"%.2f", m_fReplayTime);
	}
	

	// 다이렉트 폰트 출력
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX * 0.19f, WINCY * 0.05f, 0.f);

	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);


	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_szTime, /* 출력할 문자열 */
		lstrlen(m_szTime), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		D3DCOLOR_ARGB(255, 255, 0, 0));

}

void CStage::LineRender()
{
	if(m_bDebugFlag)
	  m_pObjectMgr->LineRender();
}

HRESULT CStage::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	if (!m_bTextureLoad)
	{
		//// Player Attack Texture
		HRESULT hr;



		// Player Dash Texture
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimRun%d.png",
			L"Player",
			L"Run",
			2);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Run LoadTexture Failed", E_FAIL);

		// Player Dash Texture
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimWalk%d.png",
			L"Player",
			L"Walk",
			2);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Walk LoadTexture Failed", E_FAIL);

		// Player Dash Texture
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimIdle.png",
			L"Player",
			L"Idle", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Idle LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/BANDAGE/bandage%d.png",
			L"Bandage",
			L"help", 2);
		FAILED_CHECK_MSG_RETURN(hr, L"Bandage LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimWall.png",
			L"Player",
			L"Wall", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Idle LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanim1_15.png",
			L"Player",
			L"Hand", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Hand LoadTexture Failed", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimJump.png",
			L"Player",
			L"Jump", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Hand LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimJumpDown.png",
			L"Player",
			L"Down", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Hand LoadTexture Failed", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/meatboyanimEnd.png",
			L"Player",
			L"End", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player Idle LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/meatboyWalkBlood%d.png",
			L"Effect",
			L"PlayerWalk", 2);
		FAILED_CHECK_MSG_RETURN(hr, L"Player walk E LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/RunBlood%d.png",
			L"Effect",
			L"PlayerRun", 4);
		FAILED_CHECK_MSG_RETURN(hr, L"Player run E LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/JumpBlood%d.png",
			L"Effect",
			L"PlayerJump", 4);
		FAILED_CHECK_MSG_RETURN(hr, L"Player run E LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/Dead/Dead%d.png",
			L"Effect", L"PlayerDead", 9);
		FAILED_CHECK_MSG_RETURN(hr, L"Dead Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/Start/Start%d.png",
			L"Effect", L"PlayerStart", 9);
		FAILED_CHECK_MSG_RETURN(hr, L"Start Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/meatboyWallJump%d.png",
			L"Effect", L"PlayerWallJump", 4);
		FAILED_CHECK_MSG_RETURN(hr, L"Start Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/Effect/meatboyLand%d.png",
			L"Effect", L"PlayerLand", 4);
		FAILED_CHECK_MSG_RETURN(hr, L"Start Texture Load Failed", E_FAIL);




		hr = m_pSpriteMgr->LoadTexture(
			pGraphicDev,
			L"../SMBTexture/TILE/foresttiles01.png",
			L"TILE", 600, 600);
		FAILED_CHECK_MSG_RETURN(hr, L"Tile LoadTexture Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/BACK/bg%d.png",
			L"BackGround", L"BACK", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"Back Texture Load Failed", E_FAIL);
		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/OBJECT/FOREST/forestset%d.png",
			L"TileObject", L"FOREST", 28);
		FAILED_CHECK_MSG_RETURN(hr, L"FObject Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/KILLOBJECT/SAW/Saw_%d.png",
			L"KillObject", L"SAW", 4);
		FAILED_CHECK_MSG_RETURN(hr, L"KObject Saw Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/KILLOBJECT/SAW_PIVOT/Saw_Pivot%d.png",
			L"KillObject", L"SAW_PIVOT", 1);
		FAILED_CHECK_MSG_RETURN(hr, L"KObject Saw_Pivot Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/PLAYER/MeatBoy/tileBlood%d.png",
			L"Blood", L"blood", 3);
		FAILED_CHECK_MSG_RETURN(hr, L"tileBlood Texture Load Failed", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
			L"../SMBTexture/UI/TIME_UI.png",
			L"UI", L"TIME", 3);
		FAILED_CHECK_MSG_RETURN(hr, L"tileBlood Texture Load Failed", E_FAIL);

		hr = m_pObjectMgr->AddObject(OBJECT_TERRAIN, CTileObject::Create());
		FAILED_CHECK_MSG_RETURN(hr, L"Terrain Create Failed", E_FAIL);
	}
	m_pSoundMgr->PlayBGM(L"forestmenu.wav");
	m_tTimeInfo.vPos = { WINCX * 0.2f,WINCX * 0.025f, 0.f };
	m_tTimeInfo.vSize = { 1.f,1.f,0.f };
	return S_OK;
}

void CStage::Release()
{
}

void CStage::InitStage(STAGE_INFO eStageInfo)
{
	HRESULT hr;
	switch (eStageInfo)
	{
	case STAGE_1:
		m_pObjectMgr->InitTile(L"../MapData/testStage1.dat");
 
		hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetMeatPos()));
		FAILED_CHECK_MSG(hr, L"Player Create Failed");

		hr = m_pObjectMgr->AddObject(OBJECT_BANDAGE, CBandage::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetBandPos()));
		FAILED_CHECK_MSG(hr, L"Terrain Create Failed");

		m_eStageInfo = STAGE_2;
		m_eNowStageInfo = STAGE_1;
		break;
	case STAGE_2:
		m_pObjectMgr->InitTile(L"../MapData/testStage2.dat");
		 hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetMeatPos()));
		FAILED_CHECK_MSG(hr, L"Player Create Failed");

		hr = m_pObjectMgr->AddObject(OBJECT_BANDAGE, CBandage::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetBandPos()));
		FAILED_CHECK_MSG(hr, L"Terrain Create Failed");

		m_eStageInfo = STAGE_3;

		m_eNowStageInfo = STAGE_2;
		break;
	case STAGE_3:
		m_pObjectMgr->InitTile(L"../MapData/testStage3.dat");
		 hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetMeatPos()));
		FAILED_CHECK_MSG(hr, L"Player Create Failed");
		hr = m_pObjectMgr->AddObject(OBJECT_BANDAGE, CBandage::Create(dynamic_cast<CTileObject*>(m_pObjectMgr->GetTileInfo())->GetBandPos()));
		FAILED_CHECK_MSG(hr, L"Terrain Create Failed");

		m_eStageInfo = STAGE_END;

		m_eNowStageInfo = STAGE_3;
		break;
	}
}

CStage* CStage::Create(int Stage, bool flag)
{
	CStage* pInstance = new CStage;
	pInstance->m_bTextureLoad = flag;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	pInstance->InitStage((STAGE_INFO)Stage);
	return pInstance;
}