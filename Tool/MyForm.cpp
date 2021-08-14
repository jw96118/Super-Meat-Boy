// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NO_SELECT, m_Radio[0]);
	DDX_Control(pDX, IDC_MEAT_POS, m_Radio[1]);
	DDX_Control(pDX, IDC_BAND_POS, m_Radio[2]);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnBnClickedTileTool)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// MFC 폰트 오브젝트 생성.
	m_Font.CreatePointFont(200, L"consolas");

	// ID값을 통해서 현재 다이얼로그에 배치된 대상을 얻어올 수 있다.
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font); // 버튼에 폰트 적용하기


	// 다이얼로그 생성
	m_UnitTool.Create(IDD_UNITTOOL);
	m_TileTool.Create(IDD_TILETOOL);
	m_BackTool.Create(IDD_BACKTOOL);
	m_KillObjTool.Create(IDD_KILLOBJTOOL);
	m_BackObjTool.Create(IDD_BACKOBJTOOL);

	m_Radio[0].SetCheck(TRUE);

}

void CMyForm::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//::AfxMessageBox(L"Unit Tool"); // MFC 메시지박스 함수.

	// 아직 생성되지 않았다면 GetSafeHwnd함수는 nullptr을 반환.
	NULL_CHECK_MSG(m_UnitTool.GetSafeHwnd(), L"UnitTool is null");
	m_UnitTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}

const CTileTool & CMyForm::GetTileIndex() const
{
	return m_TileTool;
}


void CMyForm::OnBnClickedTileTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_TileTool.GetSafeHwnd(), L"TileTool is null");
	m_TileTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_BackTool.GetSafeHwnd(), L"BackTool is null");
	m_BackTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_BackObjTool.GetSafeHwnd(), L"BackObjTool is null");
	m_BackObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NULL_CHECK_MSG(m_KillObjTool.GetSafeHwnd(), L"KillObjTool is null");
	m_KillObjTool.ShowWindow(SW_SHOW);
}
