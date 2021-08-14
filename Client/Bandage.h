#pragma once
#include "GameObject.h"
class CBandage :
	public CGameObject
{
private:
	CBandage();
public:
	~CBandage();
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
	static CBandage* Create(D3DXVECTOR3 Pos);
	const INFO& GetInfo() const;
	const float& GetColX() const;
	const float& GetColY() const;
	void SetPos(D3DXVECTOR3& Pos);
	void SetEndflag(bool flag);
	void SetReplay();
	const  float& GetAlpa() const;
private:
	FRAME			m_tFrame;
	INFO            m_tInfo;
	float           m_fColSizeX;
	float           m_fColSizeY;
	float           m_fSize;
	bool            m_bEnd;
	float           m_fAlpa;
	bool            m_bReplay;
	list<float>     m_listAlpa;
	list<float>::iterator iter_begin;
};

