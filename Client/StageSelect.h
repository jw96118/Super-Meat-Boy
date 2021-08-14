#pragma once
#include "Scene.h"
class CStageSelect :
	public CScene
{
private:
	CStageSelect();
public :
	~CStageSelect();
public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

private:
	void RenderSprite(D3DXMATRIX& tempMat, const TCHAR* type1, const TCHAR* type2, int Alpha,float frame = 0);
	void LateUpdateSprite(LOGO_INFO& info, float ChangeX);
public :
	static CStageSelect* CStageSelect::Create(bool flag);

private:

	CKeyMgr*	    m_pKeyMgr;
	LOGO_INFO m_tSelect_Back;
	LOGO_INFO m_tSelect_Back_Front;
	LOGO_INFO m_tSelect_Stage1;
	LOGO_INFO m_tSelect_Stage2;
	LOGO_INFO m_tSelect_Stage3;
	LOGO_INFO m_tSelect_Stage_Line1;
	LOGO_INFO m_tSelect_Stage_Line2;
	LOGO_INFO m_tSelect_Player;
	LOGO_INFO m_tSelect_Shadow;
	LOGO_INFO m_tSelect_Blood;
	LOGO_INFO m_tSelect_Saw1;
	LOGO_INFO m_tSelect_Saw2;

	FRAME			m_tFrame_Player;
	FRAME			m_tFrame_Blood;
	int m_iSelectCount = 0;
	bool m_bMoveFlag;
	bool m_bGoStage = false;
	float moveLength = 0.f;
	float PlayerImageY = 0.f;
	bool m_bTextureLoad;

	bool m_bChangeX;
	bool m_bChange2;
	bool m_bSceneMeat;


	TCHAR m_szTime[MIN_STR] = L"";
	TCHAR* m_szStage = L"";
};

