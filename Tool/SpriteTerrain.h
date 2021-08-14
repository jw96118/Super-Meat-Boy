#pragma once
#include "GameObject.h"

class CToolView;
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
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption, const float& angle, const float& changex, const float& changey,  const RECT* col);
	void MiniRender();
	void LineRender();
	void SaveTile(DWORD& dwBytes,const HANDLE& hFile,const TCHAR* pFilePath);
	void LoadTile(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath);
private:
	bool IsPicking(const D3DXVECTOR3& vPos, int iIndex);
	int CSpriteTerrain::GetTileIndex(const D3DXVECTOR3& vPos);
public:
	static CSpriteTerrain* Create(CToolView* pView = nullptr);

private:
	vector<SPRITE_INFO*>	m_vecTile;
	CToolView*			m_pView;
	RECT         DrawPoint;
};

