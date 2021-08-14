#pragma once

class CGameObject;
class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	HRESULT AddObject(OBJECT_TYPE eType, CGameObject* pObject);
	void    CreateEffect(D3DXVECTOR3& vPos, D3DXVECTOR3& vSize, EFFECT_TYPE type);
	int Update();
	void LateUpdate();
	void Render();
	void LineRender();
	CGameObject* GetTileInfo();
	CGameObject* GetPlayer();
	void PlayerReplay();
	void DeleteMeatBand();
	void InitTile(const TCHAR* pFilePath);
	void InitPos(D3DXVECTOR3& vMeatPos, D3DXVECTOR3& vBandPos);
private:
	void Release();
private:
	void SetScrollPos(D3DXVECTOR3 vPos);
private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
	CKeyMgr*		m_pKeyMgr;
};

