#pragma once

class CScene
{
protected:
	CScene();

public:
	virtual ~CScene();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void LineRender() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CTimeMgr*		m_pTimeMgr;
	CSceneMgr*		m_pSceneMgr;
	CObjectMgr*     m_pObjectMgr;
	CSpriteMgr*     m_pSpriteMgr;

	CSoundMgr*      m_pSoundMgr;

	bool            m_bTestflag = false;
	bool            m_InitSaw = false;
};

