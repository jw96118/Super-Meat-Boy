#pragma once
#include "GameObject.h"

class CSpriteTerrain :
	public CGameObject
{
private:
	CSpriteTerrain();

public:
	virtual ~CSpriteTerrain();
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
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption, const float& angle, const float& changex, const float& changey,  const RECT* col);
	void SaveTile(DWORD& dwBytes,const HANDLE& hFile,const TCHAR* pFilePath);
	void LoadTile(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath);
	void SetReplay();
	SPRITE_INFO* GetSpriteTerrain(const D3DXVECTOR3& vPos);
	BLOOD_INFO* GetBloodTerrain(const D3DXVECTOR3& vPos,  const int& index);
private:
	bool IsPicking(const D3DXVECTOR3& vPos, int iIndex);
	int GetTileIndex(const D3DXVECTOR3& vPos);
public:
	static CSpriteTerrain* Create();

private:
	vector<SPRITE_INFO*>	m_vecTile;
	RECT         DrawPoint;
	vector<BLOOD_INFO*>     m_vecBlood[COL_END];
};

