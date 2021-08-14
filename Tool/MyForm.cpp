// MyForm.cpp : ���� �����Դϴ�.
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


// CMyForm �����Դϴ�.

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


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// MFC ��Ʈ ������Ʈ ����.
	m_Font.CreatePointFont(200, L"consolas");

	// ID���� ���ؼ� ���� ���̾�α׿� ��ġ�� ����� ���� �� �ִ�.
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�


	// ���̾�α� ����
	m_UnitTool.Create(IDD_UNITTOOL);
	m_TileTool.Create(IDD_TILETOOL);
	m_BackTool.Create(IDD_BACKTOOL);
	m_KillObjTool.Create(IDD_KILLOBJTOOL);
	m_BackObjTool.Create(IDD_BACKOBJTOOL);

	m_Radio[0].SetCheck(TRUE);

}

void CMyForm::OnBnClickedUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//::AfxMessageBox(L"Unit Tool"); // MFC �޽����ڽ� �Լ�.

	// ���� �������� �ʾҴٸ� GetSafeHwnd�Լ��� nullptr�� ��ȯ.
	NULL_CHECK_MSG(m_UnitTool.GetSafeHwnd(), L"UnitTool is null");
	m_UnitTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}

const CTileTool & CMyForm::GetTileIndex() const
{
	return m_TileTool;
}


void CMyForm::OnBnClickedTileTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_TileTool.GetSafeHwnd(), L"TileTool is null");
	m_TileTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_BackTool.GetSafeHwnd(), L"BackTool is null");
	m_BackTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_BackObjTool.GetSafeHwnd(), L"BackObjTool is null");
	m_BackObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NULL_CHECK_MSG(m_KillObjTool.GetSafeHwnd(), L"KillObjTool is null");
	m_KillObjTool.ShowWindow(SW_SHOW);
}
