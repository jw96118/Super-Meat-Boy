#pragma once


// CMiniView ���Դϴ�.

class CTerrain;
class CSpriteTerrain;
class CTileObject;
class CMiniView : public CView
{
	DECLARE_DYNCREATE(CMiniView)

protected:
	CMiniView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMiniView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

public:
	CDeviceMgr*	m_pDeviceMgr;
	CTerrain*	m_pTerrain;
	CSpriteTerrain* m_pSTerrain;
	CTileObject*    m_pTileObj;
};


