#pragma once
#include "GameObject.h"
class CEffect :
	public CGameObject
{
private:
	CEffect();
public:
	~CEffect();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void LineRender() override;
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:	
	static CEffect* Create();
	const bool& GetEnable() const;
	void SetEnable(bool flag);
	void SetInfo(D3DXVECTOR3& vPos, D3DXVECTOR3& vSize, EFFECT_TYPE RenderType);
private:
	INFO       m_tInfo;
	bool       m_bEnable;
	EFFECT_TYPE m_RenderType;
	float      m_NowFrame;
	float      m_MaxFrame;
	CObjectMgr*	m_pObjectMgr;
};

