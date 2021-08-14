#pragma once
#define BACK1X 10
#define BACK1Y 8
#include "Scene.h"
class CLogo : public CScene
{
private:
	CLogo();

public:
	virtual ~CLogo();


public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CLogo* Create(bool flag);
private:
	void RenderSprite(D3DXMATRIX& tempMat, const TCHAR* type1, const TCHAR* type2, int Alpha);
	void LateUpdateSprite(LOGO_INFO& info, float ChangeX);
private:
	CKeyMgr*	    m_pKeyMgr;
	LOGO_INFO       m_tLogo_Saw;
	LOGO_INFO       m_tLogo_Face;
	LOGO_INFO       m_tLogo_Back;
	LOGO_INFO       m_tLogo_Back_Bottom;
	LOGO_INFO       m_tLogo_Title;
	LOGO_INFO       m_tLogo_Cur1;
	LOGO_INFO       m_tLogo_Cur2;
	LOGO_INFO       m_tLogo_Select;
	LOGO_INFO       m_tLogo_Now_Select;
	LOGO_INFO       m_tLogo_Exit_Game;
	LOGO_INFO       m_tLogo_Start_Game;

	LOGO_INFO       m_tLogo_Back1[BACK1X][BACK1Y];


	bool            m_bStartflag;
	bool            m_bTextureLoad;
};

