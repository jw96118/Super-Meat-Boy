#include "stdafx.h"
#include "PhysicMgr.h"

D3DXVECTOR3	CPhysicMgr::vecScale{};

float CPhysicMgr::ConvertGravity(const D3DXVECTOR3* pIn, const float fPower, const float acc)
{
	if (nullptr == pIn)
	{
		return 0.f;
	}

	static const float fGravity = 9.8f;
	static const float fHalf = 0.5f;
	static const float fPI = 3.141592f;
	
	const float fUpForce = fPower * sinf(90 * fPI / 180.f);
	float test = sinf(90 * fPI / 180.f);
	const float fDownForce = powf(acc, 2.f) * fGravity * fHalf;

	return fUpForce - fDownForce;

}

void CPhysicMgr::InitializeScaleVec(D3DXVECTOR3 * pScale)
{
	vecScale.x = 1.f;
	vecScale.y = 1.f;
	vecScale.z = 0.f;
}

D3DXMATRIX CPhysicMgr::MakeWorldMatrix(const D3DXVECTOR3 * pScale, const float fAngle, const D3DXVECTOR3 * pMove)
{
	static D3DXMATRIX	matScale, matRotate, matMove;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixIdentity(&matMove);

	D3DXMatrixScaling(&matScale, pScale->x, pScale->y, 0.f);
	D3DXMatrixRotationZ(&matRotate, fAngle);
	D3DXMatrixTranslation(&matMove, pMove->x, pMove->y, 0.f);

	D3DXMATRIX	matWorld = matScale * matRotate * matMove;

	return matWorld;
}
