// KillObjTool.cpp: 구현 파일
//


#include "stdafx.h"
#include "Tool.h"
#include "KillObjTool.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "KillObject.h"
#include "Texture.h"
#include "TileObject.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"

// CKillObjTool 대화 상자

IMPLEMENT_DYNAMIC(CKillObjTool, CDialog)

CKillObjTool::CKillObjTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_KILLOBJTOOL, pParent), m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()), iImageIndex(0.f), iListIndex(0.f), m_fSize(0.f)
	, m_fAngle(0)
{

}

CKillObjTool::~CKillObjTool()
{
}

void CKillObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KILLOBJ_SIZE, m_fSize);
	DDX_Control(pDX, IDC_KILLOBJ_LIST, m_ImageListBox);
	DDX_Control(pDX, IDC_NOW_KILLOBJECT_LIST, m_ObjectListBox);
	DDX_Text(pDX, IDC_KILLOBJ_ANGLE, m_fAngle);
}

void CKillObjTool::DeleteAll()
{
	count = 0;
	m_ObjectListBox.ResetContent();
}

void CKillObjTool::InputList(int _count)
{
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	m_fSize = pView->m_pTileObj->GetKillObj(iListIndex, true)->m_fSize;
	m_fAngle = pView->m_pTileObj->GetKillObj(iListIndex, true)->m_fAngle;
	CString wstring;
	switch (pView->m_pTileObj->GetKillObj(iListIndex,true)->obj_Type)
	{
	case SAW:
		wstring = "SAW";
		break;
	case SAW_MOVE:
		wstring = "SAW_MOVE";
		break;
	case SAW_MOVE_ANGLE:
		wstring = "SAW_MOVE_ANGLE";
		break;
	}


	wstring += to_string(count).c_str();
	m_ObjectListBox.AddString(wstring);
	count++;


}


BOOL CKillObjTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString wstring;

	wstring = "SAW";
	m_ImageListBox.AddString(wstring);
	wstring = "SAW_MOVE";
	m_ImageListBox.AddString(wstring);	
	wstring = "SAW_MOVE_ANGLE";
	m_ImageListBox.AddString(wstring);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다
}
BEGIN_MESSAGE_MAP(CKillObjTool, CDialog)
	ON_LBN_SELCHANGE(IDC_KILLOBJ_LIST, &CKillObjTool::OnLbnSelchangeKillobjList)
	ON_LBN_SELCHANGE(IDC_NOW_KILLOBJECT_LIST, &CKillObjTool::OnLbnSelchangeNowKillobjectList)
	ON_BN_CLICKED(ID_INSERT_KILL, &CKillObjTool::OnBnClickedInsertKill)
	ON_BN_CLICKED(ID_SET_KILL, &CKillObjTool::OnBnClickedSetKill)
	ON_BN_CLICKED(ID_DELETE_KIILL, &CKillObjTool::OnBnClickedDeleteKiill)
	ON_BN_CLICKED(ID_SET_UPDATE, &CKillObjTool::OnBnClickedSetUpdate)
	ON_BN_CLICKED(ID_SET_STOP, &CKillObjTool::OnBnClickedSetStop)
END_MESSAGE_MAP()


// CKillObjTool 메시지 처리기


void CKillObjTool::OnLbnSelchangeKillobjList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iImageIndex = m_ImageListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iImageIndex) // 없는 대상을 선택했을 때
		return;
}


void CKillObjTool::OnLbnSelchangeNowKillobjectList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iListIndex = m_ObjectListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iListIndex) // 없는 대상을 선택했을 때
	{
		check = false;
		return;
	}
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->SelectKObject(iListIndex);
	m_fSize = pView->m_pTileObj->GetKillObj(iListIndex)->m_fSize;
	m_fAngle = pView->m_pTileObj->GetKillObj(iListIndex)->m_fAngle;
	check = true;
}


void CKillObjTool::OnBnClickedInsertKill()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->InsertKillObj((KILLOBJ_TYPE)iImageIndex);
	CString wstring;
	m_ImageListBox.GetText(iImageIndex, wstring);
	wstring += to_string(count).c_str();
	m_ObjectListBox.AddString(wstring);
	count++;

	m_fSize = pView->m_pTileObj->GetKillObj(iListIndex, true)->m_fSize;
	m_fAngle = pView->m_pTileObj->GetKillObj(iListIndex, true)->m_fAngle;
	pView->Invalidate(FALSE);
}


void CKillObjTool::OnBnClickedSetKill()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!check)
		return;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->SetKillSize(iListIndex, m_fSize , m_fAngle , (KILLOBJ_TYPE)iImageIndex);
	UpdateData(false);

	pView->Invalidate(FALSE);
}


void CKillObjTool::OnBnClickedDeleteKiill()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	m_fSize = 0;
	m_fAngle = 0;
	m_ObjectListBox.DeleteString(iListIndex);
	pView->m_pTileObj->DeleteKillObj(iListIndex);
	pView->Invalidate(FALSE);
}


void CKillObjTool::OnBnClickedSetUpdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	update = true;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->Invalidate(false);
}


void CKillObjTool::OnBnClickedSetStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	update = false;
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->Invalidate(false);
}
