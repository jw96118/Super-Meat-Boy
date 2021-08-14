#pragma once
class CPhysicMgr
{
public:
	static D3DXMATRIX MakeWorldMatrix(const D3DXVECTOR3* pScale, const float fAngle, const D3DXVECTOR3* pMove);
	static float ConvertGravity(const D3DXVECTOR3* pIn, const float fPower, const float acc);

public:
	static void InitializeScaleVec(D3DXVECTOR3* pScale);
	static D3DXVECTOR3	vecScale;
};

