#pragma once
#include "GameObject.h"
class CToolView;
class CBackObject :
	public CGameObject
{
public:	
	CBackObject();
	virtual ~CBackObject();
public: 
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	void Init(CToolView* view);
private:
	virtual void Release() override;

public:
	void ObjChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID);
	void MiniRender();
	void LineRender();
	void SetSize(float size);
	void SaveBackObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath);
	void LoadBackObj(DWORD & dwBytes, const HANDLE & hFile, const TCHAR * pFilePath);
public:
	D3DXVECTOR3 vPos;	
	D3DXVECTOR3 vSize;
	D3DXMATRIX  matWorld; 
	BYTE        byDrawID;
	float       m_fAngle;
	bool        select = false;
	bool        endflag = false;
	float       m_fSize = 1.f;
	CToolView*			m_pView;
};
