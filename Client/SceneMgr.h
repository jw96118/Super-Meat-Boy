#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	CSceneMgr();
	~CSceneMgr();

public:
	HRESULT SceneChange(SCENE_TYPE eCurType, SCENE_TYPE eNextType,int Stage =0);
	int Update();
	void LateUpdate();
	void Render();
	void LineRender();
	bool SceneChangeSaw(bool flag);
private:
	void Release();

private:
	CScene*	m_pScene;
	bool m_bTextureLoad[SCENE_END];
	CTextureMgr*	m_pTextureMgr;
	CDeviceMgr*		m_pDeviceMgr;
	CTimeMgr*       m_pTimeMgr;
	
	bool m_bSawLoad =false;
	bool m_bSceneChange = false;
	INFO m_tInfo;
	float m_Angle = 0.f;
	SCENE_TYPE m_eCurType;
	SCENE_TYPE m_eNextType;
	int m_iStage;
	//CSoundMgr* m_pSoundMgr;
};

