// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strInput(_T(""))
	, m_strOutput(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0),
	m_strSearch(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	for (auto& MyPair : m_mapUnit)
		SafeDelete(MyPair.second);

	m_mapUnit.clear();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInput);
	DDX_Text(pDX, IDC_EDIT2, m_strOutput);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Text(pDX, IDC_EDIT6, m_strSearch);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedPush)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_EN_UPDATE(IDC_EDIT6, &CUnitTool::OnFindName)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedPush()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// UpdateData�Լ�: DoDataExchange�Լ��� ����.
	// TRUE: ������ ��ȯ ������ "��Ʈ�� -> ����"�� ����.
	UpdateData(TRUE);

	m_strOutput = m_strInput;

	// FALSE: ������ ��ȯ ������ "���� -> ��Ʈ��"�� ����.
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);	

	// CString::GetString()�Լ��� wstring::c_str()�� ���� ����� �Ѵ�.
	auto iter_find = m_mapUnit.find(m_strName.GetString());

	if (m_mapUnit.end() != iter_find)
		return;

	UNIT_DATA* pUnit = new UNIT_DATA;
	pUnit->wstrName = m_strName.GetString();
	pUnit->iAtt = m_iAtt;
	pUnit->iDef = m_iDef;
	cout << m_iAtt << endl;
	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck()) // ���� ��ư�� üũ�Ǿ� ������ TRUE ��ȯ.
		{
			pUnit->iJobIndex = i;
			break;
		}
	}	

	m_mapUnit.insert(make_pair(pUnit->wstrName, pUnit));

	// ����Ʈ�ڽ� ��Ͽ� ���ڿ��� �߰��Ѵ�.
	m_ListBox.AddString(m_strName);
}


void CUnitTool::OnLbnSelchangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex = m_ListBox.GetCurSel(); // ������ ����� �ε����� ����.

	if (-1 == iIndex) // ���� ����� �������� ��
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // �ε����� �ش��ϴ� �̸��� ����.

	auto iter_find = m_mapUnit.find(strName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // ��� ��ư üũ ����

	// ���� ������ �����ִ� ������ üũ.
	m_Radio[iter_find->second->iJobIndex].SetCheck(TRUE); 

	UpdateData(FALSE);
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Radio[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iIndex = m_ListBox.GetCurSel(); // ������ ����� �ε����� ����.

	if (-1 == iIndex) // ���� ����� �������� ��
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // �ε����� �ش��ϴ� �̸��� ����.

	auto iter_find = m_mapUnit.find(strName.GetString());

	

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = "";
	m_iAtt = 0;
	m_iDef = 0;
	m_ListBox.DeleteString(iIndex);
	m_mapUnit.erase(strName.GetString());
	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // ��� ��ư üũ ����

	UpdateData(FALSE);
}


void CUnitTool::OnFindName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);


	auto iter_find = m_mapUnit.find(m_strSearch.GetString());

	if (m_mapUnit.end() == iter_find)
		return;
	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // ��� ��ư üũ ����

	// ���� ������ �����ִ� ������ üũ.
	m_Radio[iter_find->second->iJobIndex].SetCheck(TRUE);

	UpdateData(FALSE);
}
