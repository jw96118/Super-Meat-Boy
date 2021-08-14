
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"
#include "Terrain.h"
#include "SpriteTerrain.h"
#include "MiniView.h"
#include "MyForm.h"
#include "TileTool.h"
#include "TileObject.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// ��������
HWND g_hWnd;

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()), m_pSpriteMgr(CSpriteMgr::GetInstance()),
	m_pTerrain(nullptr), m_pSTerrain(nullptr),m_pTileObj(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.	
}

CToolView::~CToolView()
{
	//SafeDelete(m_pTerrain);
	//SafeDelete(m_pSTerrain);
	SafeDelete(m_pTileObj);
	m_pTextureMgr->DestroyInstance();
	m_pSpriteMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �׸���

// WM_PAINT �޽����� ���� ������ ȣ��.
void CToolView::OnDraw(CDC* pDC)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pMyView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pMyView);

	if (pMyView->m_KillObjTool.update)
		m_pTileObj->Update();

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	/*pDC->Rectangle(100, 100, 200, 200);
	pDC->Ellipse(100, 100, 200, 200);*/
	m_pTileObj->LateUpdate();
	m_pDeviceMgr->Render_Begin();

	//m_pSTerrain->Render();
	//m_pTerrain->Render();
	m_pTileObj->Render();
	m_pDeviceMgr->Render_End();

	m_pDeviceMgr->Render_Line_Begin();
	//m_pSTerrain->LineRender();
	m_pTileObj->LineRender();
	m_pDeviceMgr->Render_Line_End();

	
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pFrameWnd->m_SecondSplitter.GetPane(0, 0));
	NULL_CHECK(pMiniView);
	
	pMiniView->Invalidate(FALSE); // �̴Ϻ� ����
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWnd = m_hWnd;

	// ��ũ�� ���� ����
	int iCX = TILEX * STILECX;
	int iCY = TILEY * STILECY;

	CScrollView::SetScrollSizes(MM_TEXT, CSize(iCX, iCY));


	// View ũ�⸦ �����ϱ� ���ؼ��� ������ �������� ũ�⸦ �ǵ帰��.
	// ������ �������� ������ ������ ���.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK_MSG(pFrameWnd, L"pFrameWnd is null");

	RECT rcFrame = {};

	// �������� ũ��(�׵θ� + Ŭ���̾�Ʈ ����) ������ �Լ�.(��ũ�� ��ǥ ����)
	pFrameWnd->GetWindowRect(&rcFrame); 
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rcView = {};

	// �������� Ŭ���̾�Ʈ ����(�׵θ��� �������� ����) ũ�� ������ �Լ�. (Ŭ���̾�Ʈ ��ǥ ����)
	GetClientRect(&rcView); 

	// ���� ������������� View ������ ������ ���Ѵ�.
	int iGapX = rcFrame.right - rcView.right;
	int iGapY = rcFrame.bottom - rcView.bottom;

	// �������������� ũ�⸦ ���� ����.
	pFrameWnd->SetWindowPos(nullptr, 0, 0, WINCX + iGapX, WINCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	HRESULT hr = m_pDeviceMgr->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG(hr, L"InitDevice Failed");

	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG(pGraphicDev, L"pGraphicDev is null");


	hr = m_pSpriteMgr->LoadTexture(
		pGraphicDev,
		L"../SMBTexture/TILE/foresttiles01.png",
		L"TILE", 600, 600);
	FAILED_CHECK_MSG(hr, L"Tile LoadTexture Failed", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../SMBTexture/BACK/bg%d.png",
		L"BackGround", L"BACK", 1);
	FAILED_CHECK_MSG(hr, L"Back Texture Load Failed");
	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../SMBTexture/OBJECT/FOREST/forestset%d.png",
		L"TileObject", L"FOREST", 28);
	FAILED_CHECK_MSG(hr, L"FObject Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../SMBTexture/KILLOBJECT/SAW/Saw_%d.png",
		L"KillObject", L"SAW", 4);
	FAILED_CHECK_MSG(hr, L"KObject Texture Load Failed");

	hr = m_pTextureMgr->LoadTexture(pGraphicDev, TEXTURE_MULTI,
		L"../SMBTexture/KILLOBJECT/SAW_PIVOT/Saw_Pivot%d.png",
		L"KillObject", L"SAW_PIVOT", 1);
	FAILED_CHECK_MSG(hr, L"KObject Texture Load Failed");
	/*m_pTerrain = CTerrain::Create(this);
	NULL_CHECK_MSG(m_pTerrain, L"Terrain Create Failed");
*/
	//m_pSTerrain = CSpriteTerrain::Create(this);
	//NULL_CHECK_MSG(m_pSTerrain, L"Terrain Create Failed");
	
	m_pTileObj = new CTileObject;
	m_pTileObj->Init(this);
	NULL_CHECK_MSG(m_pTileObj, L"TileObj Create Failed");
}

// WM_LBUTTONDOWN �޽��� �߻��� �� ȣ���.
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	D3DXVECTOR3 vPoint = 
	{ 
		(float)point.x + CScrollView::GetScrollPos(0), 
		(float)point.y + CScrollView::GetScrollPos(1),
		0.f 
	};

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pMyView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pMyView);
	if (pMyView->m_Radio[0].GetCheck())
	{
		if (pMyView->m_TileTool.IsWindowVisible())
		{
			//m_pSTerrain->TileChange(vPoint, pMyView->GetTileIndex().GetTile(), 0, pMyView->GetTileIndex().GetAngle(), pMyView->GetTileIndex().GetChangeX(), pMyView->GetTileIndex().GetChangeY(), pMyView->GetTileIndex().GetCol());
			m_pTileObj->SpriteTileChange(vPoint, pMyView->GetTileIndex().GetTile(), 0, pMyView->GetTileIndex().GetAngle(), pMyView->GetTileIndex().GetChangeX(), pMyView->GetTileIndex().GetChangeY(), pMyView->GetTileIndex().GetCol());
			//m_pTerrain->TileChange(vPoint, 3);
		}
		else if (pMyView->m_BackObjTool.IsWindowVisible())
		{
			m_pTileObj->SetBackObjPos(pMyView->m_BackObjTool.iListIndex, vPoint);
		}
		else if (pMyView->m_KillObjTool.IsWindowVisible())
		{
			m_pTileObj->SetKillPos(pMyView->m_KillObjTool.iListIndex, vPoint);
		}
	}
	else if (pMyView->m_Radio[1].GetCheck())
	{
		m_pTileObj->SetMeatPos(vPoint);
	}
	else if (pMyView->m_Radio[2].GetCheck())
	{
		m_pTileObj->SetBandPos(vPoint);
	}

	// ȭ�� ���� (WM_PAINT �߻�)
	Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);
}

// WM_MOUSEMOVE �޽��� �߻� �� ȣ���.
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		D3DXVECTOR3 vPoint =
		{
			(float)point.x + CScrollView::GetScrollPos(0),
			(float)point.y + CScrollView::GetScrollPos(1),
			0.f
		};
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CMyForm* pMyView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
		NULL_CHECK(pMyView);
		if (pMyView->m_Radio[0].GetCheck())
		{
			//m_pSTerrain->TileChange(vPoint, pMyView->GetTileIndex().GetTile(), 0, pMyView->GetTileIndex().GetAngle(), pMyView->GetTileIndex().GetChangeX(), pMyView->GetTileIndex().GetChangeY(), pMyView->GetTileIndex().GetCol());//m_pTerrain->TileChange(vPoint, 3);
			if (pMyView->m_TileTool.IsWindowVisible())
			{
				m_pTileObj->SpriteTileChange(vPoint, pMyView->GetTileIndex().GetTile(), 0, pMyView->GetTileIndex().GetAngle(), pMyView->GetTileIndex().GetChangeX(), pMyView->GetTileIndex().GetChangeY(), pMyView->GetTileIndex().GetCol());
			}
			else if (pMyView->m_BackObjTool.IsWindowVisible())
			{
				m_pTileObj->SetBackObjPos(pMyView->m_BackObjTool.iListIndex, vPoint);
			}
			else if (pMyView->m_KillObjTool.IsWindowVisible())
			{
				m_pTileObj->SetKillPos(pMyView->m_KillObjTool.iListIndex, vPoint);
			}
		}
		else if (pMyView->m_Radio[1].GetCheck())
		{
			m_pTileObj->SetMeatPos(vPoint);
		}
		else if (pMyView->m_Radio[2].GetCheck())
		{
			m_pTileObj->SetBandPos(vPoint);
		}
		// ȭ�� ���� (WM_PAINT �߻�)
		Invalidate(FALSE);
	}

	CScrollView::OnMouseMove(nFlags, point);
}
