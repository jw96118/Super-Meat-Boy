#pragma once
#include "GameObject.h"
class CKillObject :
	public CGameObject
{
private:
	CKillObject();
public:
	virtual ~CKillObject();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption, const float& angle, const float& changex, const float& changey, const RECT* col);
	void MiniRender();
	void SaveKillObj(DWORD& dwBytes, const HANDLE& hFile, const TCHAR* pFilePath);
	static CKillObject* LoadKillObj(DWORD& dwBytes, const HANDLE& hFile, const TCHAR* pFilePath);
	void SetSize(float size);
	void SetSawChange();
	void SetReplay(bool flag);
	const int& GetSawColSize() const;
	const D3DXVECTOR3& GetSawPos() const;
public:
	static CKillObject* Create( KILLOBJ_TYPE obj = NO_OBJ);

private:
	void GetReplayInfo(REPLAY_KILL_INFO info);
	REPLAY_KILL_INFO SetReplayInfo();
public:
	KILLOBJ* m_pSaw;
	KILLOBJ* m_pSawAngle;
	KILLOBJ* m_pSawShoter;

	KILLOBJ_TYPE obj_Type;
	D3DXVECTOR3 tempPos;
	D3DXVECTOR3 vPos;
	bool        select;
	bool        endflag ;
	bool        moveflag = false;
	float       m_fSize = 1.f;
	float       m_fAngle = 0.f;
	
	const TEX_INFO* pSawTexInfo = nullptr;
	const TEX_INFO* pSawATexInfo = nullptr;
	const TEX_INFO* pSawSTexInfo = nullptr;
	D3DXMATRIX tempMat = {};
	list<REPLAY_KILL_INFO> m_listKill;
	list<REPLAY_KILL_INFO>::iterator iter_begin;
	bool m_bReplay = false;;
};

