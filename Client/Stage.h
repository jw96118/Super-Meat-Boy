#pragma once
#include "Scene.h"
class CStage : public CScene
{
private:
	CStage();

public:
	virtual ~CStage();

public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;
	void InitStage(STAGE_INFO eStageInfo);
public:
	static CStage* Create(int Stage, bool flag);
	
private:
	CObjectMgr*	m_pObjectMgr;
	CKeyMgr*	m_pKeyMgr;
	bool    m_bLineFlag = false;
	STAGE_INFO m_eStageInfo;
	STAGE_INFO m_eNowStageInfo;
	bool m_bTextureLoad;

	TCHAR m_szTime[MIN_STR] = L"";
	INFO m_tTimeInfo;
	INFO m_tStageLoad;
	bool m_bStageLoad;
	float m_fStageLoadAlpa = 0.f;
	float m_fReplayTime = 0.f;
};

