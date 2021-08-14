#include "stdafx.h"
#include "ScrollMgr.h"

D3DXVECTOR3 CScrollMgr::m_vScrollPos = { 0.f, 0.f, 0.f };

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

const D3DXVECTOR3& CScrollMgr::GetScrollPos()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vScrollPos;
}

const void CScrollMgr::SetScrollPos(D3DXVECTOR3 & Pos)
{
	D3DXVECTOR3 temp = {};
	m_vScrollPos = Pos;
	if (Pos.x < 0)
	{
		m_vScrollPos.x = 0.f;
	}
	if (Pos.y < 0)
	{
		m_vScrollPos.y = 0.f;
	}

	if (float(TILEX * STILECX * 0.7f - WINCX) < m_vScrollPos.x )
		m_vScrollPos.x = float(TILEX * STILECX * 0.7f - WINCX);
	if (float(TILEY * STILECY * 0.7f - WINCY) < m_vScrollPos.y)
		m_vScrollPos.y = float(TILEY * STILECY * 0.7f - WINCY);

}

const void CScrollMgr::Vibration()
{
	m_vScrollPos = { m_vScrollPos.x + rand() % 3 - 1, m_vScrollPos.y + rand() % 3 - 1 , m_vScrollPos.z };
	if (m_vScrollPos.x < 0)
	{
		m_vScrollPos.x = 0.f;
	}
	if (m_vScrollPos.y < 0)
	{
		m_vScrollPos.y = 0.f;
	}

	if (float(TILEX * STILECX * 0.7f - WINCX) < m_vScrollPos.x)
		m_vScrollPos.x = float(TILEX * STILECX * 0.7f - WINCX);
	if (float(TILEY * STILECY * 0.7f - WINCY) < m_vScrollPos.y)
		m_vScrollPos.y = float(TILEY * STILECY * 0.7f - WINCY);
}

const void CScrollMgr::SetEnd(D3DXVECTOR3 & Pos)
{
	D3DXVECTOR3 tempPos =
	{
		(Pos.x - m_vScrollPos.x) /10,
		(Pos.y - m_vScrollPos.y) / 10,
		0.f
	};
	m_vScrollPos = { m_vScrollPos.x +tempPos.x,m_vScrollPos.y + tempPos.y,0.f };
	if (m_vScrollPos.x < 0)
	{
		m_vScrollPos.x = 0.f;
	}
	if (m_vScrollPos.y < 0)
	{
		m_vScrollPos.y = 0.f;
	}

	if (float(TILEX * STILECX * 0.7f - WINCX) < m_vScrollPos.x)
		m_vScrollPos.x = float(TILEX * STILECX * 0.7f - WINCX);
	if (float(TILEY * STILECY * 0.7f - WINCY) < m_vScrollPos.y)
		m_vScrollPos.y = float(TILEY * STILECY * 0.7f - WINCY);


	return void();
}

void CScrollMgr::MoveScrollPos(const D3DXVECTOR3& vMove)
{
	m_vScrollPos += vMove;
}
