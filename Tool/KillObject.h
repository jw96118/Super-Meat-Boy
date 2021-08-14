#pragma once
#include "GameObject.h"
#include "ToolView.h"
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
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption, const float& angle, const float& changex, const float& changey, const RECT* col);
	void MiniRender();
	void LineRender();
	void SaveKillObj(DWORD& dwBytes, const HANDLE& hFile, const TCHAR* pFilePath);
	static CKillObject* LoadKillObj(DWORD& dwBytes, const HANDLE& hFile, const TCHAR* pFilePath, CToolView* pView = nullptr);
	void SetSize(float size);
public:
	static CKillObject* Create(CToolView* pView = nullptr, KILLOBJ_TYPE obj = NO_OBJ);

public:
	KILLOBJ* m_pSaw;
	KILLOBJ* m_pSaw2;
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
	CToolView*			m_pView;
	const TEX_INFO* pSawTexInfo = nullptr;
	const TEX_INFO* pSawATexInfo = nullptr;
	const TEX_INFO* pSawSTexInfo = nullptr;
	
};

