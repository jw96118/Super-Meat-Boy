
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// 전역변수
HWND g_hWnd;

// CToolView 생성/소멸

CToolView::CToolView()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()), m_pSpriteMgr(CSpriteMgr::GetInstance()),
	m_pTerrain(nullptr), m_pSTerrain(nullptr),m_pTileObj(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.	
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

// WM_PAINT 메시지가 있을 때마다 호출.
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

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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
	
	pMiniView->Invalidate(FALSE); // 미니뷰 갱신
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWnd = m_hWnd;

	// 스크롤 범위 지정
	int iCX = TILEX * STILECX;
	int iCY = TILEY * STILECY;

	CScrollView::SetScrollSizes(MM_TEXT, CSize(iCX, iCY));


	// View 크기를 조정하기 위해서는 프레임 원도우의 크기를 건드린다.
	// 프레임 윈도우의 포인터 얻어오는 방법.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK_MSG(pFrameWnd, L"pFrameWnd is null");

	RECT rcFrame = {};

	// 윈도우의 크기(테두리 + 클라이언트 영역) 얻어오는 함수.(스크린 좌표 기준)
	pFrameWnd->GetWindowRect(&rcFrame); 
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rcView = {};

	// 윈도우의 클라이언트 영역(테두리를 포함하지 않은) 크기 얻어오는 함수. (클라이언트 좌표 기준)
	GetClientRect(&rcView); 

	// 현재 프레임윈도우와 View 사이의 갭들을 구한다.
	int iGapX = rcFrame.right - rcView.right;
	int iGapY = rcFrame.bottom - rcView.bottom;

	// 프레임윈도우의 크기를 새로 설정.
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

// WM_LBUTTONDOWN 메시지 발생할 때 호출됨.
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// 화면 갱신 (WM_PAINT 발생)
	Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);
}

// WM_MOUSEMOVE 메시지 발생 시 호출됨.
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
		// 화면 갱신 (WM_PAINT 발생)
		Invalidate(FALSE);
	}

	CScrollView::OnMouseMove(nFlags, point);
}
