#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX matWorld; // 월드행렬 = 스(케일) * 자(전) * 이(동) * 공(전) * 부(모행렬)

}INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
	float Size;
}TILE_INFO;

typedef struct tagSpriteTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
	float m_fAngle;
	float changeX;
	float changeY;
	RECT Col[COL_END];
	bool endflag;
}SPRITE_INFO;

typedef struct tagKillObjInfo
{
	D3DXVECTOR3 vPos = {};
	D3DXVECTOR3 vSize = {};
	D3DXMATRIX  matWorld = {};
	D3DXMATRIX  matMiniWorld = {};
	BYTE byDrawID;
	float m_fAngle;
	float m_fSize;
	RECT Col;
	bool endflag;
	KILLOBJ_TYPE obj_Type;
}KILLOBJ;

typedef struct tagFrame
{
	float fCurFrame;
	float fMaxFrame;
	
}FRAME;

typedef struct tagUnit
{
	wstring wstrName;
	int iAtt;
	int iDef;
	int iJobIndex;
}UNIT_DATA;

typedef struct tagGravityINFO
{
	float fAcc;
	float fPower;
}GRAVITY_INFO;

typedef struct tagTileBlood
{
	D3DXVECTOR3 vPos = {};
	bool  m_bDrawBlood;
	float   nowFrame;
	const float maxFrame = 2;
}BLOOD_INFO;

typedef struct tagLogoInfo
{
	D3DXVECTOR3 vPos = {};
	D3DXVECTOR3 vSize = {};
	float       m_fAngle = 0.f;
	D3DXMATRIX  matWorld = {};
}LOGO_INFO;
typedef struct tagPlayerInfo
{
	INFO			m_tInfo;
	INFO			m_tLeftInfo;
	INFO			m_tRightInfo;
	FRAME			m_tFrame;
	PLAYER_STATE    m_eState;
	D3DXVECTOR3     m_tfirstvPos;
	float           m_fSpeed;
	float           m_fJumpSpeed;
	float           m_fChangeX;
	float           m_fColSizeX;
	float           m_fColSizeY;
	float           fY = 3000.f;
	bool            m_bJumping = false;
	bool            m_bRightCol = false;
	bool            m_bLeftCol = false;
	bool            m_bLeftJump = false;
	bool            m_bRightJump = false;
	float           m_iJumpCount = 0;
	float           m_fSize;
	GRAVITY_INFO    m_GInfo;

}PLAYER_INFO;


typedef struct tagReplayKillInfo
{
	KILLOBJ m_pSaw;
	KILLOBJ m_pSawAngle;
	KILLOBJ m_pSawShoter;

	bool        moveflag = false;
	D3DXVECTOR3 tempPos;
}REPLAY_KILL_INFO;
