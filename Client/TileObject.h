#pragma once

#include "GameObject.h"
class CSpriteTerrain;
class CBackGround;
class CBackObject;
class CKillObject;
class CTileObject : public CGameObject
{
private:
	CTileObject();

public:
	virtual ~CTileObject();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;
private:
	void Release();
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
public:
	void Init(const TCHAR* pFilePath);

	CKillObject* GetKillObj(int index, bool back =false);
	void SetSawRenderChange(int index);
	const int& GetKillObjSize() const;
	const D3DXVECTOR3 GetMeatPos() const;
	const D3DXVECTOR3 GetBandPos() const;
public:
	void SaveObj(const TCHAR* pFilePath);
	void LoadObj(const TCHAR* pFilePath);
	static CTileObject* Create();
	CSpriteTerrain* GetSTerrain() const;
	void SetReaplay();
private:
	CSpriteTerrain* m_pSTerrain;
	CBackGround*    m_pBack;
	vector<CBackObject*> m_pBackObj;
	vector<CKillObject*> m_pKillObj;

	CDeviceMgr*		m_pDeviceMgr;
	D3DXVECTOR3     meatPos;
	D3DXVECTOR3     bandPos;


};

