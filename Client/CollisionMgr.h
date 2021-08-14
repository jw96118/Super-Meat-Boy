#pragma once

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionObject(OBJECT_LIST& dstList);
	static void CollisionFloor(CGameObject* pDest, OBJECT_LIST& srcList);
	static void CollisionSaw(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static bool CollisionBandage(CGameObject* pDest, CGameObject* pSource);
private:
	static bool IntersectSphere(CGameObject* pDest, CGameObject* pSource);
	static void ColObject(CGameObject* pDest, RECT pSource);
};

