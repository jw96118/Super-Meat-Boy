#pragma once

#include "GameObject.h"

class CPlayer : public CGameObject
{
private:
	CPlayer();

public:
	~CPlayer();

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;

private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(D3DXVECTOR3 vPos);
	virtual void Release() override;

public:
	static CPlayer* Create(D3DXVECTOR3 vPos);
private:
	void SetScrollPos(D3DXVECTOR3 vPos);
	void GetReplayInfo(PLAYER_INFO info);
	PLAYER_INFO SetReplayInfo();
public:
	void SetJumpY(float fy);
	void SetPos(D3DXVECTOR3 vPos);
	void SetPower(float power);
	void SetAcc(float acc);
	void SetLeftCol(bool flag);
	void SetRightCol(bool flag);
	void SetPosFirst();
	void SetDead();
	void SetEnd();
	void SetReplay(bool flag);
	void SetColTop(bool flag);
	void CreateDeadEffect();
	void CreateStartEffect();
	void PlayColSound();
	void SetStageLoad();
	void SetRightBottomCol(bool flag);
	void SetLeftBottomCol(bool flag);
	const bool& GetJump() const;
	const bool& GetReplay() const;
	const bool& GetReplayEnd() const;
	const bool& GetStageLoad() const;
	const bool& GetLeftBottomCol() const;
	const bool& GetRightBottomCol() const;
	const INFO& GetInfo() const;
	const float& GetColX() const;
	const float& GetColY() const;
	const PLAYER_STATE& GetState() const;
	const D3DXVECTOR3& GetFirstPos() const;
	
private: 
	void Jump();
	void JumpHand();
private:
	INFO			m_tInfo;
	INFO			m_tLeftInfo;
	INFO			m_tRightInfo;
	FRAME			m_tFrame;
	CKeyMgr*		m_pKeyMgr;
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
	CObjectMgr*	m_pObjectMgr;
	
	list<PLAYER_INFO> player_Info;
	list<PLAYER_INFO>::iterator iter_begin;
	bool            m_bReplay = false;
	bool            m_bReplay_End = false;
	bool            m_bEndScene = false;

	int               m_iHandCount = 0;
	float             m_fHandTime = 0.f;
	bool              m_bHandChange = false;
	bool              m_bJumpRLflag = false;
	bool              m_bColTop = false;
	bool              m_bColSound = false;
	
	bool              m_StageLoad = false;
	bool              m_bRightBottomCol = false;
	bool              m_bLeftBottomCol = false;
};

