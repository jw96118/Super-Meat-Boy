#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScrollPos();
	static const void SetScrollPos(D3DXVECTOR3& Pos);
	static const void Vibration();
	static const void SetEnd(D3DXVECTOR3& Pos);
public:
	static void MoveScrollPos(const D3DXVECTOR3& vMove);

private:
	static D3DXVECTOR3 m_vScrollPos;
};

