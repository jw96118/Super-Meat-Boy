#pragma once

class CGameObject
{
protected:
	CGameObject();

public:
	virtual ~CGameObject();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void LineRender() PURE;
protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;
public :
	const OBJECT_TYPE GetType() const;
protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;	
	CTimeMgr*		m_pTimeMgr;
	CSpriteMgr*     m_pSpriteMgr;
	CSceneMgr*      m_pSceneMgr;
	CSoundMgr*      m_pSoundMgr;
	OBJECT_TYPE     m_pType;
};

