#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "TileObject.h"
#include "SpriteTerrain.h"
#include "KillObject.h"
#include "Bandage.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}



void CCollisionMgr::CollisionFloor(CGameObject* pDest, OBJECT_LIST& srcList)
{
	RECT rc = {};

	float x1 = 0.f;
	float y1 = 0.f;
	float x2 = 0.f;
	float y2 = 0.f;
	int count = 0;
	bool leftCol = false;
	bool rightCol = false;
	bool topCol = false;
	bool bottomCol = false;
	bool topbottomCol = false;
	bool bottomtopCol = false;
	float fY;
	CSpriteTerrain* temp = dynamic_cast<CTileObject*>(srcList.back())->GetSTerrain();
	D3DXVECTOR3 playerLeft = {};
	D3DXVECTOR3 playerRight = {};
	D3DXVECTOR3 playerTop = {};
	D3DXVECTOR3 playerBottom = {};
	D3DXVECTOR3 playerPos = {};

	playerLeft = { dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - dynamic_cast<CPlayer*>(pDest)->GetColX() - 1.f
		,dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y,0.f };
	playerRight = { dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x + dynamic_cast<CPlayer*>(pDest)->GetColX() + 1.f
		,dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y,0.f };
	playerTop = { dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x,
		dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y - dynamic_cast<CPlayer*>(pDest)->GetColY() ,0.f };
	playerBottom = { dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x,
		dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y + dynamic_cast<CPlayer*>(pDest)->GetColY(),0.f };
	playerPos = dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos;
	if (pDest->GetType() == OBJECT_PLAYER)
	{
		if (!dynamic_cast<CPlayer*>(pDest)->GetReplay())
		{
			if (temp->GetSpriteTerrain(playerBottom) != nullptr)
			{
				if (temp->GetSpriteTerrain(playerBottom)->Col[TOP].left -
					temp->GetSpriteTerrain(playerBottom)->Col[TOP].right
					== 0 &&
					temp->GetSpriteTerrain(playerBottom)->Col[TOP].top -
					temp->GetSpriteTerrain(playerBottom)->Col[TOP].bottom
					== 0)
				{
					bottomCol = false;
				}
				else
				{
					x1 = temp->GetSpriteTerrain(playerBottom)->Col[TOP].left;
					y1 = temp->GetSpriteTerrain(playerBottom)->Col[TOP].top;
					x2 = temp->GetSpriteTerrain(playerBottom)->Col[TOP].right;
					y2 = temp->GetSpriteTerrain(playerBottom)->Col[TOP].bottom;
					bottomCol = true;

					temp->GetBloodTerrain(playerBottom, TOP)->m_bDrawBlood = true;
				}

			}
			if (temp->GetSpriteTerrain(playerPos) != nullptr)
			{
				if (temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].left -
					temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].right
					== 0 &&
					temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].top -
					temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].bottom
					== 0)
				{
					topbottomCol = false;
				}
				else
				{
					x1 = temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].left;
					y1 = temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].top;
					x2 = temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].right;
					y2 = temp->GetSpriteTerrain(playerPos)->Col[UPBOTTOM].bottom;
					topbottomCol = true;

					temp->GetBloodTerrain(playerPos, UPBOTTOM)->m_bDrawBlood = true;
				}

				if (temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].left -
					temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].right
					== 0 &&
					temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].top -
					temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].bottom
					== 0)
				{
					bottomtopCol = false;
				}
				else
				{
					x1 = temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].left;
					y1 = temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].top;
					x2 = temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].right;
					y2 = temp->GetSpriteTerrain(playerPos)->Col[BOTTOMUP].bottom;
					bottomtopCol = true;

					temp->GetBloodTerrain(playerPos, BOTTOMUP)->m_bDrawBlood = true;
				}
			}
			if (temp->GetSpriteTerrain(playerLeft) != nullptr)
			{
				if (temp->GetSpriteTerrain(playerLeft)->Col[RIGHT].left -
					temp->GetSpriteTerrain(playerLeft)->Col[RIGHT].right
					== 0 &&
					temp->GetSpriteTerrain(playerLeft)->Col[RIGHT].top -
					temp->GetSpriteTerrain(playerLeft)->Col[RIGHT].bottom
					== 0)
				{
					leftCol = false;
					dynamic_cast<CPlayer*>(pDest)->SetLeftCol(false);
					dynamic_cast<CPlayer*>(pDest)->SetLeftBottomCol(false);
				}
				else
				{
					leftCol = true;
					temp->GetBloodTerrain(playerLeft, RIGHT)->m_bDrawBlood = true;
				}
			}
			if (temp->GetSpriteTerrain(playerRight) != nullptr)
			{
				if (temp->GetSpriteTerrain(playerRight)->Col[LEFT].left -
					temp->GetSpriteTerrain(playerRight)->Col[LEFT].right
					== 0 &&
					temp->GetSpriteTerrain(playerRight)->Col[LEFT].top -
					temp->GetSpriteTerrain(playerRight)->Col[LEFT].bottom
					== 0)
				{
					rightCol = false;
					dynamic_cast<CPlayer*>(pDest)->SetRightCol(false);
					dynamic_cast<CPlayer*>(pDest)->SetRightBottomCol(false);
				}
				else
				{
					rightCol = true;
					temp->GetBloodTerrain(playerRight, LEFT)->m_bDrawBlood = true;
				}
			}
			if (temp->GetSpriteTerrain(playerTop) != nullptr)
			{
				if (temp->GetSpriteTerrain(playerTop)->Col[BOTTOM].left -
					temp->GetSpriteTerrain(playerTop)->Col[BOTTOM].right
					== 0 &&
					temp->GetSpriteTerrain(playerTop)->Col[BOTTOM].top -
					temp->GetSpriteTerrain(playerTop)->Col[BOTTOM].bottom
					== 0)
				{
					topCol = false;
				}
				else
				{
					topCol = true;
					temp->GetBloodTerrain(playerTop, BOTTOM)->m_bDrawBlood = true;
				}
			}


			if (bottomCol)
			{
				fY = (y2 - y1) / (x2 - x1) *
					(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - x1) + y1;
				dynamic_cast<CPlayer*>(pDest)->SetJumpY(fY);
				dynamic_cast<CPlayer*>(pDest)->SetColTop(false);
				dynamic_cast<CPlayer*>(pDest)->PlayColSound();
			}
			else if (!bottomCol)
			{
				dynamic_cast<CPlayer*>(pDest)->SetJumpY(3000);
			}
			else if (bottomtopCol)
			{
				fY = (y2 - y1) / (x2 - x1) *
					(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - x1) + y1;
				dynamic_cast<CPlayer*>(pDest)->SetJumpY(fY);
			}
			else if (topbottomCol)
			{
				fY = (y2 - y1) / (x2 - x1) *
					(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - x1) + y1;
				dynamic_cast<CPlayer*>(pDest)->SetJumpY(fY);
			}




			if (leftCol)
			{
				D3DXVECTOR3 tempVec = { temp->GetSpriteTerrain(playerLeft)->Col[RIGHT].left + dynamic_cast<CPlayer*>(pDest)->GetColX() ,
					dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y,0.f };
				dynamic_cast<CPlayer*>(pDest)->SetPos(tempVec);
				if (!bottomCol)
				{
					dynamic_cast<CPlayer*>(pDest)->SetLeftCol(true);
					dynamic_cast<CPlayer*>(pDest)->SetColTop(false);
					if (dynamic_cast<CPlayer*>(pDest)->GetLeftBottomCol())
					{
						dynamic_cast<CPlayer*>(pDest)->PlayColSound();
					}
				
				}
				else
				{
					dynamic_cast<CPlayer*>(pDest)->SetLeftCol(false);
					dynamic_cast<CPlayer*>(pDest)->SetRightBottomCol(true);
				}
			}
			if (rightCol)
			{
				D3DXVECTOR3 tempVec = { temp->GetSpriteTerrain(playerRight)->Col[LEFT].left - dynamic_cast<CPlayer*>(pDest)->GetColX(),
					dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y,0.f };
				dynamic_cast<CPlayer*>(pDest)->SetPos(tempVec);

				if (!bottomCol)
				{
					dynamic_cast<CPlayer*>(pDest)->SetRightCol(true);
					dynamic_cast<CPlayer*>(pDest)->SetColTop(false);
					if (!dynamic_cast<CPlayer*>(pDest)->GetRightBottomCol())
					{
						dynamic_cast<CPlayer*>(pDest)->PlayColSound();
					}
				}
				else
				{
					dynamic_cast<CPlayer*>(pDest)->SetRightCol(false);
					dynamic_cast<CPlayer*>(pDest)->SetRightBottomCol(true);
				}
			}
			if (topCol)
			{
				D3DXVECTOR3 tempVec = { dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x,
					temp->GetSpriteTerrain(playerTop)->Col[BOTTOM].top + dynamic_cast<CPlayer*>(pDest)->GetColY(),0.f };
				dynamic_cast<CPlayer*>(pDest)->SetPos(tempVec);
				dynamic_cast<CPlayer*>(pDest)->SetPower(-5.f);
				dynamic_cast<CPlayer*>(pDest)->SetColTop(true);
				dynamic_cast<CPlayer*>(pDest)->PlayColSound();
			}
		}
	}

}


void CCollisionMgr::CollisionSaw(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (!dynamic_cast<CPlayer*>(pDest)->GetReplay())
			{
				if (pDest->GetType() == OBJECT_PLAYER && pSrc->GetType() == OBJECT_TERRAIN)
				{
					for (int i = 0; i < dynamic_cast<CTileObject*>(pSrc)->GetKillObjSize(); i++)
					{
						if (i == 2)
						{
							//cout << dynamic_cast<CKillObject*>(dynamic_cast<CTileObject*>(pSrc)->GetKillObj(i))->GetSawPos().x << endl;
							//cout << dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x <<" , " <<dynamic_cast<CKillObject*>(dynamic_cast<CTileObject*>(pSrc)->GetKillObj(i))->GetSawPos().x << endl;
						}
						if (IntersectSphere(pDest, dynamic_cast<CTileObject*>(pSrc)->GetKillObj(i)))
						{
							if (dynamic_cast<CPlayer*>(pDest)->GetState() != DEAD)
							{
								dynamic_cast<CPlayer*>(pDest)->SetDead();
								dynamic_cast<CTileObject*>(pSrc)->SetSawRenderChange(i);
							}
						}
					}
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionBandage(CGameObject* pDest, CGameObject* pSource)
{
	if (!dynamic_cast<CPlayer*>(pDest)->GetReplay())
	{
		if (pDest->GetType() == OBJECT_PLAYER)
		{
			RECT rc = {};
			RECT tempPlayer = {};
			RECT tempBandage = {};
			tempPlayer = { (int)(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - dynamic_cast<CPlayer*>(pDest)->GetColX()),
			(int)(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y - dynamic_cast<CPlayer*>(pDest)->GetColY()),
			(int)(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x + dynamic_cast<CPlayer*>(pDest)->GetColX()),
			(int)(dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y + dynamic_cast<CPlayer*>(pDest)->GetColY()) };
			tempBandage = { (int)(dynamic_cast<CBandage*>(pSource)->GetInfo().vPos.x - dynamic_cast<CBandage*>(pSource)->GetColX()),
			(int)(dynamic_cast<CBandage*>(pSource)->GetInfo().vPos.y - dynamic_cast<CBandage*>(pSource)->GetColY()),
			(int)(dynamic_cast<CBandage*>(pSource)->GetInfo().vPos.x + dynamic_cast<CBandage*>(pSource)->GetColX()),
			(int)(dynamic_cast<CBandage*>(pSource)->GetInfo().vPos.y + dynamic_cast<CBandage*>(pSource)->GetColY()) };

			if (IntersectRect(&rc, &tempPlayer, &tempBandage))
			{
				dynamic_cast<CPlayer*>(pDest)->SetEnd();
				dynamic_cast<CBandage*>(pSource)->SetEndflag(true);
				return true;
			}
		}
	}
	return false;
}

void CCollisionMgr::CollisionObject(OBJECT_LIST & dstList)
{
	//POINT tempP = {};
	//RECT rc = {};
	//RECT net = { WINCX / 2 - 20, 0 , WINCX / 2 + 20 , WINCY };
	//RECT netBall = { WINCX/2 - 20, WINCY / 2 , WINCX/2 + 20 , WINCY };
	//RECT wall1 = { -20, 0  , 0 , WINCY };
	//RECT wall2 = { WINCX , 0 , WINCX + 20 , WINCY };
	//for (auto pDest : dstList)
	//{
	//	if (pDest->GetType() == OBJECT_PLAYER)
	//	{
	//		if (IntersectRect(&rc, &pDest->GetRect(), &net))
	//		{
	//			ColObject(pDest, net);
	//		}
	//		if (IntersectRect(&rc, &pDest->GetRect(), &wall1))
	//		{
	//			ColObject(pDest, wall1);
	//		}
	//		if (IntersectRect(&rc, &pDest->GetRect(), &wall2))
	//		{
	//			ColObject(pDest, wall2);
	//		}
	//	}
	//}
}

bool CCollisionMgr::IntersectSphere(CGameObject* pDest, CGameObject* pSource)
{
	// 원충돌
	// 두 원의 반지름 합을 구한다. r1 + r2
	// 두 원의 중점 간 거리를 구한다. d
	// r1 + r2 >= d 조건을 만족하면 TRUE

	float r1 = dynamic_cast<CPlayer*>(pDest)->GetColX();
	float r2 = dynamic_cast<CKillObject*>(pSource)->GetSawColSize();

	float w = dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.x - dynamic_cast<CKillObject*>(pSource)->GetSawPos().x;
	float h = dynamic_cast<CPlayer*>(pDest)->GetInfo().vPos.y - dynamic_cast<CKillObject*>(pSource)->GetSawPos().y;

	//// sqrtf: 제곱근 구하는 함수. <cmath>에서 제공.
	float d = sqrtf(w * w + h * h);

	return r1 + r2 >= d;
}

void CCollisionMgr::ColObject(CGameObject * pDest, RECT  pSource)
{
	//RECT rc = {};
	//POINT tempP = {};
	//if (IntersectRect(&rc, &pDest->GetRect(), &pSource))
	//{
	//	if (pDest->GetRect().right < pSource.right)
	//	{
	//		tempP.x = -(rc.right - rc.left);
	//	}
	//	else
	//	{
	//		tempP.x = (rc.right - rc.left);
	//	}
	//	if (pDest->GetRect().top < pSource.top)
	//	{
	//		tempP.y = -(rc.bottom - rc.top);
	//	}
	//	else
	//	{
	//		tempP.y = (rc.bottom - rc.top);
	//	}
	//	D3DXVECTOR3 tempVec;
	//	if (rc.bottom - rc.top > rc.right - rc.left)
	//		tempVec = { pDest->GetInfo().vPos.x + tempP.x, pDest->GetInfo().vPos.y ,0};
	//	else
	//		tempVec = { pDest->GetInfo().vPos.x, pDest->GetInfo().vPos.y + tempP.y,0 };
	//	pDest->SetPos(tempVec);
	//}
}
