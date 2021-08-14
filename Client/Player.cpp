#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"
#define PLAYER_SPEED 150
#define PLAYER_JUMP_SPEED 60
#define JUMP_POWER   7
CPlayer::CPlayer()
	: m_pKeyMgr(CKeyMgr::GetInstance()), m_pObjectMgr(CObjectMgr::GetInstance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayer::~CPlayer()
{
	Release();
}

int CPlayer::Update()
{

	D3DXVECTOR3 tempEPos = {};
	D3DXVECTOR3 tempESize = {};
	if (!m_bReplay)
	{
		if (!m_bEndScene)
		{
			if (m_bRightCol)
			{
				m_bLeftJump = false;
				m_fChangeX = -1.f;
				m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.3f ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.3f ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			}
			if (m_bLeftCol)
			{
				m_bRightJump = false;
				m_fChangeX = 1.f;
				m_tLeftInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX * 0.3f ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.3f  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			}
			player_Info.push_back(SetReplayInfo());
			iter_begin = player_Info.begin();
			if (m_eState != DEAD)
			{
				if (m_pKeyMgr->KeyPressing(KEY_LEFT))
				{
					m_bJumpRLflag = false;
					m_eState = MOVE_LEFT;
					if (m_pKeyMgr->KeyPressing(KEY_LSHIFT))
					{
						m_fSpeed = PLAYER_SPEED * 3.f;
						m_eState = RUN_LEFT;
					}
					else
					{
						m_fSpeed = PLAYER_SPEED;
					}

					if (!m_bLeftJump)
					{
						m_tInfo.vPos.x -= m_pTimeMgr->GetDelta() * m_fSpeed;
						//	cout << "move L" << endl;
					}
					else
					{
						if (m_iJumpCount >= 3.f)
						{
							m_tInfo.vPos.x -= m_pTimeMgr->GetDelta() * m_fSpeed;
							m_bLeftJump = false;
							m_bLeftCol = false;
							m_bRightJump = false;
							//	cout << "move J L" << endl;
						}
					}

					if (!m_bLeftCol)
					{
						m_fChangeX = 1.f;
						if (!m_pKeyMgr->KeyPressing(KEY_LSHIFT))
						{
							m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
							m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
						}
						else
						{
							if (!m_bJumping)
							{
								if (m_iHandCount == 0)
								{
									m_tLeftInfo.vPos = { m_tInfo.vPos.x  ,m_tInfo.vPos.y + m_fColSizeY * 0.5f,0.f };
									m_tRightInfo.vPos = { m_tInfo.vPos.x   ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
								}
								else
								{
									m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * (int)m_iHandCount ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
									m_tRightInfo.vPos = { m_tInfo.vPos.x   ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
								}
								if (m_fHandTime >= 0.1f)
								{
									if (m_iHandCount <= -1)
									{
										m_bHandChange =false;
									}
									else if (m_iHandCount >= 1)
									{
										m_bHandChange =true;
									}

									if (!m_bHandChange)
									{
										m_iHandCount++;
									}
									else
									{
										m_iHandCount--;
									}
																	
									m_fHandTime = 0.f;
								}
								m_fHandTime += m_pTimeMgr->GetDelta() * 1.f;
								
								
							}
						}
					}
					else
					{
						//m_bLeftJump = false;
						//m_bRightJump = false;

					}
					

				}
				if (m_pKeyMgr->KeyUp(KEY_LEFT))
				{
					m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
					m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				}

				if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
				{
					m_bJumpRLflag = true;
					m_eState = MOVE_RIGHT;
					if (m_pKeyMgr->KeyPressing(KEY_LSHIFT))
					{
						m_fSpeed = PLAYER_SPEED * 3.f;
						m_eState = RUN_RIGHT;
					}
					else
					{
						m_fSpeed = PLAYER_SPEED;
					}
					if (!m_bRightJump)
					{
						m_tInfo.vPos.x += m_pTimeMgr->GetDelta() * m_fSpeed;
					}
					else
					{
						if (m_iJumpCount >= 3.f)
						{
							m_tInfo.vPos.x += m_pTimeMgr->GetDelta() * m_fSpeed;
							m_bRightJump = false;
							m_bRightCol = false;
							m_bLeftJump = false;
						}
					}

					if (!m_bRightCol)
					{
						m_fChangeX = -1.f;
						if (!m_pKeyMgr->KeyPressing(KEY_LSHIFT))
						{
							m_tLeftInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
							m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
						}
						else
						{
							if (!m_bJumping)
							{
								if (m_iHandCount == 0)
								{
									m_tLeftInfo.vPos = { m_tInfo.vPos.x  ,m_tInfo.vPos.y + m_fColSizeY * 0.5f,0.f };
									m_tRightInfo.vPos = { m_tInfo.vPos.x   ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
								}
								else
								{
									m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * (int)m_iHandCount ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
									m_tRightInfo.vPos = { m_tInfo.vPos.x   ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
								}
								if (m_fHandTime >= 0.1f)
								{
									if (m_iHandCount <= -1)
									{
										m_bHandChange = false;
									}
									else if (m_iHandCount >= 1)
									{
										m_bHandChange = true;
									}

									if (!m_bHandChange)
									{
										m_iHandCount++;
									}
									else
									{
										m_iHandCount--;
									}

									m_fHandTime = 0.f;
								}
								m_fHandTime += m_pTimeMgr->GetDelta() * 1.f;


							}
						}
					}
					else
					{
						//m_bLeftJump = false;
						//m_bRightJump = false;
						//cout << "move R" << endl;
					}
				


				}
				
				if (m_pKeyMgr->KeyUp(KEY_RIGHT))
				{
					m_tLeftInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
					m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				}


				if (!m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT))
				{
					m_eState = IDLE;
				}



				if (m_pKeyMgr->KeyDown(KEY_SPACE))
				{
					if (!m_bJumping)
					{
						//m_pSoundMgr->PlaySound(L"Data_3.wav", SOUNDMGR::PLAYER);
						//animCount = 0;
						m_bJumping = true;
						m_bColSound = false;
						tempEPos = { m_tInfo.vPos.x, m_tInfo.vPos.y , 0.f };
						tempESize = { 0.9f , 0.9f, 1.f };
						m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_JUMP);
						m_pSoundMgr->PlaySound(L"vflipup.wav", SOUNDMGR::PLAYER);
						//m_GInfo.fPower = JUMP_POWER;
						//cout << "test" << endl;
						if (m_bRightBottomCol || m_bLeftBottomCol)
						{
							m_bColSound = true;
						}
					}
					else
					{
						if (m_bRightCol)
						{
							m_fChangeX = -1.f;
							m_bRightJump = false;
							m_bLeftJump = false;
							m_GInfo.fPower = 0;
							if (!m_bRightJump)
							{
								m_pSoundMgr->PlaySound(L"vflipup.wav", SOUNDMGR::PLAYER);
								m_bRightJump = true;
								m_iJumpCount = 0;
								m_GInfo.fAcc = 0.f;
								//m_GInfo.fPower = JUMP_POWER;
								tempEPos = { m_tInfo.vPos.x  , m_tInfo.vPos.y + m_fColSizeY  , 0.f };
								tempESize = { -0.7f , 0.7f, 1.f };
								m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_JUMP_WALL);
							}
							m_bRightCol = false;
							m_bLeftCol = false;
							//cout << "right" << endl;
						}
						if (m_bLeftCol)
						{
							m_fChangeX = 1.f;
							m_bLeftJump = false;
							m_bRightJump = false;
							m_GInfo.fPower = 0;
							if (!m_bLeftJump)
							{
								m_pSoundMgr->PlaySound(L"vflipup.wav", SOUNDMGR::PLAYER);
								m_bLeftJump = true;
								m_GInfo.fAcc = 0.f;
								m_iJumpCount = 0;
								//m_GInfo.fPower = JUMP_POWER;
								tempEPos = { m_tInfo.vPos.x  , m_tInfo.vPos.y + m_fColSizeY  , 0.f };
								tempESize = { 0.7f , 0.7f, 1.f };
								m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_JUMP_WALL);
							}

							m_bRightCol = false;
							m_bLeftCol = false;
						}
					}

				}
				if (m_pKeyMgr->KeyPressing(KEY_SPACE))
				{
					float power = JUMP_POWER;
					if (m_bRightCol || m_bLeftCol)
					{
						power = JUMP_POWER * 1.3f;
					}
					if (!m_bJumping)
					{
						if (m_GInfo.fPower <= 0)
						{
							m_pSoundMgr->PlaySound(L"vflipup.wav", SOUNDMGR::PLAYER);
							tempEPos = { m_tInfo.vPos.x, m_tInfo.vPos.y , 0.f };
							tempESize = { 0.9f , 0.9f, 1.f };
							m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_JUMP);

						}
					}
					if (!m_bColTop)
					{
						if (m_GInfo.fPower <= power)
							m_GInfo.fPower += m_pTimeMgr->GetDelta()*m_fJumpSpeed;
					}
				}


				if (m_bRightJump)
				{
					m_tInfo.vPos.x -= m_pTimeMgr->GetDelta() * m_fSpeed;
					m_iJumpCount += m_pTimeMgr->GetDelta() * 10;
					if (m_eState == IDLE)
					{
						m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f ,0.f };
						m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
					}
					//JumpHand();
					if (!m_bJumping)
					{
						m_bRightJump = false;
						m_bRightCol = false;
					}
				
				}
				if (m_bLeftJump)
				{
					m_tInfo.vPos.x += m_pTimeMgr->GetDelta() * m_fSpeed;
					if (m_eState == IDLE)
					{
						m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f ,0.f };
						m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
					}
					//JumpHand();
					m_iJumpCount += m_pTimeMgr->GetDelta() * 10;
					if (!m_bJumping)
					{
						m_bLeftJump = false;
						m_bLeftCol = false;
					}
				
				}




				m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * 5.f;

				if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
				{
					m_tFrame.fCurFrame = 0.f;
					if (!m_bJumping)
					{
						switch (m_eState)
						{
						case IDLE:
							break;
						case MOVE_LEFT:
							tempEPos = { m_tInfo.vPos.x + m_fColSizeX  , m_tInfo.vPos.y + m_fColSizeY - 3.f , 0.f };
							tempESize = { -1.2f , 1.2f, 1.f };
							m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_WALK);
							break;
						case MOVE_RIGHT:
							tempEPos = { m_tInfo.vPos.x - m_fColSizeX  , m_tInfo.vPos.y + m_fColSizeY - 3.f, 0.f };
							tempESize = { 1.2f , 1.2f, 1.f };
							m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_WALK);
							break;
						case RUN_LEFT:
							tempEPos = { m_tInfo.vPos.x + m_fColSizeX  , m_tInfo.vPos.y , 0.f };
							tempESize = { 0.9f , 0.9f, 1.f };
							m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_DASH);
							break;
						case RUN_RIGHT:
							tempEPos = { m_tInfo.vPos.x - m_fColSizeX  , m_tInfo.vPos.y , 0.f };
							tempESize = { -0.9f , 0.9f, 1.f };
							m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_DASH);
							break;
						case JUMP:
							break;
						case DOWN:
							break;
						}
					}
				}


				Jump();

			}
		}

	}
	else
	{
		if (!m_bReplay_End)
		{
			if (iter_begin != player_Info.end())
			{
				GetReplayInfo(*iter_begin);
				if ((*iter_begin).m_eState == DEAD)
				{
					m_pObjectMgr->CreateEffect(m_tInfo.vPos, m_tInfo.vSize, PLAYER_DEAD);
					m_bReplay_End = true;
				}
				else if ((*iter_begin).m_eState == END)
				{
					m_bReplay_End = true;
				}
				else
					iter_begin++;
			}
		}
	}
	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	if (m_eState != DEAD)
	{

		D3DXMATRIX matScale, matTrans;
		D3DXMatrixScaling(&matScale,
			m_tInfo.vSize.x * m_fChangeX,
			m_tInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수

		m_tInfo.matWorld = matScale * matTrans;

		D3DXMatrixScaling(&matScale,
			m_tLeftInfo.vSize.x,
			m_tLeftInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tLeftInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tLeftInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수

		m_tLeftInfo.matWorld = matScale * matTrans;


		D3DXMatrixScaling(&matScale,
			m_tRightInfo.vSize.x,
			m_tRightInfo.vSize.y,
			0.f); // 다이렉트 크기행렬 함수
		D3DXMatrixTranslation(&matTrans,
			m_tRightInfo.vPos.x - CScrollMgr::GetScrollPos().x,
			m_tRightInfo.vPos.y - CScrollMgr::GetScrollPos().y,
			0.f); // 다이렉트 이동행렬 함수

		m_tRightInfo.matWorld = matScale * matTrans;
	}
}

void CPlayer::Render()
{
	if (m_eState != DEAD)
	{
		const TEX_INFO* pTexInfo = nullptr;

		pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Hand", 0);
		NULL_CHECK(pTexInfo);
		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tRightInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		switch (m_eState)
		{
		case IDLE:

			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Idle", 0);
			NULL_CHECK(pTexInfo);
			break;
		case MOVE_LEFT:
		case MOVE_RIGHT:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Walk", (int)m_tFrame.fCurFrame);
			NULL_CHECK(pTexInfo);
			break;
		case RUN_LEFT:
		case RUN_RIGHT:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Run", (int)m_tFrame.fCurFrame);
			NULL_CHECK(pTexInfo);
			break;
		case JUMP:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Jump", 0);
			NULL_CHECK(pTexInfo);
			break;
		case DOWN:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Down", 0);
			NULL_CHECK(pTexInfo);
			break;
		case END:
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"End", 0);
			NULL_CHECK(pTexInfo);
			break;
		}
		if (m_bRightCol)
		{
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Wall", 0);
		}
		if (m_bLeftCol)
		{
			pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Wall", 0);
		}
		NULL_CHECK(pTexInfo);
		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
		m_fColSizeX = fCenterX * m_fSize;
		m_fColSizeY = fCenterY * m_fSize;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Hand", 0);
		NULL_CHECK(pTexInfo);
		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tLeftInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CPlayer::LineRender()
{
}

HRESULT CPlayer::Initialize()
{

	return S_OK;
}

HRESULT CPlayer::Initialize(D3DXVECTOR3 vPos)
{
	// 행렬 초기화 -> 항등행렬(I)
//CMathMgr::MyMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixIdentity(&m_tInfo.matWorld); // 다이렉트 항등행렬 함수

	m_tInfo.vPos = vPos; // x, y, z
	m_tfirstvPos = vPos;
	m_fSize = 0.7f;
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_tInfo.vSize = { m_fSize,m_fSize, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 2.f;
	m_eState = IDLE;
	m_fSpeed = PLAYER_SPEED;
	m_fJumpSpeed = PLAYER_JUMP_SPEED;
	m_fChangeX = 1.f;
	m_GInfo.fPower = 0.f;
	const TEX_INFO* pTexInfo = nullptr;
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Idle", 0);
	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	//cout << fCenterX << endl;
	m_fColSizeX = fCenterX * m_fSize;
	//cout << m_fColSizeX << endl;
	m_fColSizeY = fCenterY * m_fSize;

	m_pType = OBJECT_PLAYER;

	//스크롤
	SetScrollPos(m_tInfo.vPos);
	fY = 3000;

	m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f ,0.f };
	m_tLeftInfo.vSize = { m_fSize,m_fSize, 0.f };

	m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
	m_tRightInfo.vSize = { m_fSize,m_fSize, 0.f };

	return S_OK;
}

void CPlayer::Release()
{
}

CPlayer* CPlayer::Create(D3DXVECTOR3 vPos)
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize(vPos)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::SetScrollPos(D3DXVECTOR3 vPos)
{
	//스크롤
	D3DXVECTOR3 tempPos = {};
	if (vPos.x >= CScrollMgr::GetScrollPos().x + WINCX - 500.f)
	{
		tempPos = { vPos.x + 500.f - WINCX,CScrollMgr::GetScrollPos().y,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.x <= CScrollMgr::GetScrollPos().x + 500.f)
	{
		tempPos = { vPos.x - 500.f,CScrollMgr::GetScrollPos().y,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.y <= CScrollMgr::GetScrollPos().y + 300.f)
	{
		tempPos = { CScrollMgr::GetScrollPos().x,vPos.y - 300.f,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
	if (vPos.y >= CScrollMgr::GetScrollPos().y + WINCY - 300.f)
	{
		tempPos = { CScrollMgr::GetScrollPos().x,vPos.y - WINCY + 300.f,0.f };
		CScrollMgr::SetScrollPos(tempPos);
	}
}

PLAYER_INFO CPlayer::SetReplayInfo()
{
	PLAYER_INFO info;
	info.m_tInfo = m_tInfo;
	info.m_tRightInfo = m_tRightInfo;
	info.m_tLeftInfo = m_tLeftInfo;
	info.m_tFrame = m_tFrame;
	info.m_eState = m_eState;
	info.m_tfirstvPos = m_tfirstvPos;
	info.m_fSpeed = m_fSpeed;
	info.m_fJumpSpeed = m_fJumpSpeed;
	info.m_fChangeX = m_fChangeX;
	info.m_fColSizeX = m_fColSizeX;
	info.m_fColSizeY = m_fColSizeY;
	info.fY = fY;
	info.m_bJumping = m_bJumping;
	info.m_bRightCol = m_bRightCol;
	info.m_bLeftCol = m_bLeftCol;
	info.m_bLeftJump = m_bLeftJump;
	info.m_bRightJump = m_bRightJump;
	info.m_iJumpCount = m_iJumpCount;
	info.m_fSize = m_fSize;
	info.m_GInfo = m_GInfo;
	return info;
}

void CPlayer::GetReplayInfo(PLAYER_INFO info)
{
	m_tInfo = info.m_tInfo;
	m_tRightInfo = info.m_tRightInfo;
	m_tLeftInfo = info.m_tLeftInfo;
	m_tFrame = info.m_tFrame;
	m_eState = info.m_eState;
	m_tfirstvPos = info.m_tfirstvPos;
	m_fSpeed = info.m_fSpeed;
	m_fJumpSpeed = info.m_fJumpSpeed;
	m_fChangeX = info.m_fChangeX;
	m_fColSizeX = info.m_fColSizeX;
	m_fColSizeY = info.m_fColSizeY;
	fY = info.fY;
	m_bJumping = info.m_bJumping;
	m_bRightCol = info.m_bRightCol;
	m_bLeftCol = info.m_bLeftCol;
	m_bLeftJump = info.m_bLeftJump;
	m_bRightJump = info.m_bRightJump;
	m_iJumpCount = info.m_iJumpCount;
	m_fSize = info.m_fSize;
	m_GInfo = info.m_GInfo;
}

void CPlayer::SetJumpY(float fy)
{
	fY = fy;
}

void CPlayer::SetPos(D3DXVECTOR3 vPos)
{
	m_tInfo.vPos = vPos;
}

void CPlayer::SetPower(float power)
{
	m_GInfo.fPower = power;
}

void CPlayer::SetAcc(float acc)
{
	m_GInfo.fAcc = acc;
}

void CPlayer::SetLeftCol(bool flag)
{
	m_bLeftCol = flag;
}

void CPlayer::SetRightCol(bool flag)
{
	m_bRightCol = flag;
}

void CPlayer::SetPosFirst()
{
	m_tInfo.vPos = m_tfirstvPos;
	m_eState = IDLE;
}

void CPlayer::SetDead()
{
	m_eState = DEAD;
	m_pSoundMgr->PlaySound(L"Retro_death0.wav", SOUNDMGR::PLAYER);
	m_pObjectMgr->CreateEffect(m_tInfo.vPos, m_tInfo.vSize, PLAYER_DEAD);

}

void CPlayer::SetEnd()
{
	m_eState = END;
	player_Info.push_back(SetReplayInfo());
	m_bEndScene = true;
}

void CPlayer::SetReplay(bool flag)
{
	m_bReplay = flag;
}

void CPlayer::SetColTop(bool flag)
{
	m_bColTop = flag;
}



void CPlayer::CreateDeadEffect()
{
	m_pObjectMgr->CreateEffect(m_tInfo.vPos, m_tInfo.vSize, PLAYER_DEAD);
}

void CPlayer::CreateStartEffect()
{
	SetScrollPos(m_tfirstvPos);
	m_pSoundMgr->PlaySound(L"Retro_respawn 02.wav", SOUNDMGR::PLAYER);
	m_pObjectMgr->CreateEffect(m_tfirstvPos, m_tInfo.vSize, PLAYER_START);

}

void CPlayer::PlayColSound()
{
	if (!m_bColSound)
	{
		m_pSoundMgr->PlaySound(L"vflipup.wav", SOUNDMGR::PLAYER);
		m_bColSound = true;
	}
}

void CPlayer::SetStageLoad()
{
	m_StageLoad = true;
}

void CPlayer::SetRightBottomCol(bool flag)
{
	m_bRightBottomCol = flag;
}		   

void CPlayer::SetLeftBottomCol(bool flag)
{
	m_bLeftBottomCol = flag;
}



const bool & CPlayer::GetJump() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bJumping;
}

const bool & CPlayer::GetReplay() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bReplay;
}

const bool & CPlayer::GetReplayEnd() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bReplay_End;
}

const bool & CPlayer::GetStageLoad() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_StageLoad;
}

const bool & CPlayer::GetLeftBottomCol() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bLeftBottomCol;
}

const bool & CPlayer::GetRightBottomCol() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bRightBottomCol;
}

const INFO & CPlayer::GetInfo() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

const float & CPlayer::GetColX() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_fColSizeX;
}

const float & CPlayer::GetColY() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_fColSizeY;
}

const PLAYER_STATE & CPlayer::GetState() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_eState;
}

const D3DXVECTOR3 & CPlayer::GetFirstPos() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tfirstvPos;
}



void CPlayer::Jump()
{
	// 지형 충돌
	if (m_GInfo.fAcc < 2.f)
	{
		m_GInfo.fAcc += m_pTimeMgr->GetDelta() * 1.5f;
	}

	m_tInfo.vPos.y -= CPhysicMgr::ConvertGravity(&m_tInfo.vPos, m_GInfo.fPower, m_GInfo.fAcc);
	if (m_bJumping)
	{
		if (CPhysicMgr::ConvertGravity(&m_tInfo.vPos, m_GInfo.fPower, m_GInfo.fAcc) > 0)
		{
			m_eState = JUMP;
			JumpHand();
		}
		else
		{
			m_eState = DOWN;
			JumpHand();
		}
	}
	m_tLeftInfo.vPos = { m_tLeftInfo.vPos.x  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
	m_tRightInfo.vPos = { m_tRightInfo.vPos.x  ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
	// 착지할 때
	if (m_tInfo.vPos.y > (fY - m_fColSizeY * 0.99f))
	{
		if (m_bJumping)
		{
			D3DXVECTOR3 tempEPos = {};
			D3DXVECTOR3 tempESize = {};
			tempEPos = { m_tInfo.vPos.x  , m_tInfo.vPos.y - m_fColSizeX * 0.5f  , 0.f };
			tempESize = { 0.7f , 0.7f , 1.f };
			m_pObjectMgr->CreateEffect(tempEPos, tempESize, PLAYER_LAND);
		}
		m_bJumping = false;
		m_GInfo.fAcc = 0.f;
		m_GInfo.fPower = 0.f;
		m_tInfo.vPos.y = (fY - m_fColSizeY * 0.99f);
	}
	else
	{
		m_bJumping = true;
		if (!m_bLeftCol && !m_bRightCol)
			m_bColSound = false;
	}
	if (!m_bJumping)
	{
		m_tInfo.vPos.y = (fY - m_fColSizeY * 0.99f);
	}
}

void CPlayer::JumpHand()
{

	if (!m_bLeftCol && !m_bRightCol)
	{
		if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		{
			m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			m_bJumpRLflag = false;
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		{
			m_tLeftInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			m_bJumpRLflag = true;
		}
		if (m_pKeyMgr->KeyPressing(KEY_LSHIFT))
		{
			if (!m_bJumpRLflag)
			{
				m_tLeftInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				m_tRightInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			}
			else
			{
				m_tLeftInfo.vPos = { m_tInfo.vPos.x - m_fColSizeX * 0.5f,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
				m_tRightInfo.vPos = { m_tInfo.vPos.x + m_fColSizeX ,m_tInfo.vPos.y + m_fColSizeY * 0.3f,0.f };
			}
		}
	}
}

