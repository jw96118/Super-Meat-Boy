// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MiniView.h"
#include "ToolView.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "SpriteTerrain.h"
#include "TileObject.h"
// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTerrain(nullptr) , m_pSTerrain(nullptr),m_pTileObj(nullptr)
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	//pDC->Rectangle(100, 100, 200, 200);

	m_pDeviceMgr->Render_Begin();

	//m_pSTerrain->MiniRender();
	//m_pTerrain->Render();
	m_pTileObj->MiniRender();

	m_pDeviceMgr->Render_End();

	m_pDeviceMgr->Render_Line_Begin();
	//m_pSTerrain->LineRender();
	//m_pTileObj->LineRender();
	m_pDeviceMgr->Render_Line_End(m_hWnd);

}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.


void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	/*m_pTerrain = pView->m_pTerrain;
	NULL_CHECK(m_pTerrain);*/

	/*m_pSTerrain = pView->m_pSTerrain;
	NULL_CHECK(m_pSTerrain);*/

	m_pTileObj = pView->m_pTileObj;
	NULL_CHECK(m_pTileObj);

}
