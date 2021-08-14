#pragma once
#include "GameObject.h"
class CBackGround :
	public CGameObject
{

private:
	CBackGround();

public:
	virtual ~CBackGround();
public:
	// CGameObject��(��) ���� ��ӵ�
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
	void SaveBack(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath);
	void LoadBack(DWORD& dwBytes,const HANDLE& hFile, const TCHAR* pFilePath);
	void SetSize(float size);
private:
	int CBackGround::GetBackIndex(const D3DXVECTOR3& vPos);
public:
	static CBackGround* Create();

private:
	TILE_INFO*	m_Back;
	RECT            DrawPoint;
};

