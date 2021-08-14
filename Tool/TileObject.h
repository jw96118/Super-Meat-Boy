#pragma once
class CSpriteTerrain;
class CBackGround;
class CToolView;
class CBackObject;
class CKillObject;
class CTileObject
{
public:
	CTileObject();

public:
	virtual ~CTileObject();
public:
	int Update() ;
	void LateUpdate() ;
	void Render();
	void MiniRender();
	void LineRender() ;
	void Init(CToolView* pView);
	void SpriteTileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption, const float& angle, const float& changex, const float& changey, const RECT* col);
	void SetBackGroundSize(float size);
	void InsertBackObj(CToolView* pView, const D3DXVECTOR3& vPos, const D3DXVECTOR3& vSize, const BYTE& byDrawID, float angle);
	void DeleteBackObj(int iIndex);
	void InsertKillObj(KILLOBJ_TYPE type);
	void DeleteKillObj(int iIndex);
	void SetBackObj(int iIndex, float& fSize, const BYTE& byDrawID, float angle);
	void SetBackObjPos(int iIndex, const D3DXVECTOR3 & vPos);
	void SetKillSize(int iIndex, float& fSize, float angle, KILLOBJ_TYPE type);
	void SetKillPos(int iIndex, const D3DXVECTOR3& vPos);
	int BObjectImage(int index);
	void SelectBObject(int index);
	void SelectKObject(int index);
	CBackObject* GetBackObj(int index, bool back = false);
	CKillObject* GetKillObj(int index, bool back =false);
	void SetMeatPos(const D3DXVECTOR3& vPos);
	void SetBandPos(const D3DXVECTOR3& vPos);
private:
	 void Release();
public:
	void SaveObj(const TCHAR* pFilePath);
	void LoadObj(const TCHAR* pFilePath);

private:
	CSpriteTerrain* m_pSTerrain;
	CBackGround*    m_pBack;
	vector<CBackObject*> m_pBackObj;
	vector<CKillObject*> m_pKillObj;
	CToolView*			m_pView;


	CDeviceMgr*		m_pDeviceMgr;
	D3DXVECTOR3     meatPos;
	D3DXVECTOR3     bandPos;
};

