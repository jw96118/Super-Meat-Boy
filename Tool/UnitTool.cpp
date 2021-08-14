// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedPush()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// UpdateData함수: DoDataExchange함수를 실행.
	// TRUE: 데이터 교환 방향이 "컨트롤 -> 변수"로 진행.
	UpdateData(TRUE);

	m_strOutput = m_strInput;

	// FALSE: 데이터 교환 방향이 "변수 -> 컨트롤"로 진행.
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);	

	// CString::GetString()함수는 wstring::c_str()과 같은 기능을 한다.
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
		if (m_Radio[i].GetCheck()) // 현재 버튼이 체크되어 있으면 TRUE 반환.
		{
			pUnit->iJobIndex = i;
			break;
		}
	}	

	m_mapUnit.insert(make_pair(pUnit->wstrName, pUnit));

	// 리스트박스 목록에 문자열을 추가한다.
	m_ListBox.AddString(m_strName);
}


void CUnitTool::OnLbnSelchangeList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iIndex = m_ListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iIndex) // 없는 대상을 선택했을 때
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // 인덱스에 해당하는 이름을 얻어옴.

	auto iter_find = m_mapUnit.find(strName.GetString());

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // 모든 버튼 체크 해제

	// 현재 유닛이 갖고있는 직업에 체크.
	m_Radio[iter_find->second->iJobIndex].SetCheck(TRUE); 

	UpdateData(FALSE);
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Radio[0].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iIndex = m_ListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iIndex) // 없는 대상을 선택했을 때
		return;

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName); // 인덱스에 해당하는 이름을 얻어옴.

	auto iter_find = m_mapUnit.find(strName.GetString());

	

	if (m_mapUnit.end() == iter_find)
		return;

	m_strName = "";
	m_iAtt = 0;
	m_iDef = 0;
	m_ListBox.DeleteString(iIndex);
	m_mapUnit.erase(strName.GetString());
	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // 모든 버튼 체크 해제

	UpdateData(FALSE);
}


void CUnitTool::OnFindName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);


	auto iter_find = m_mapUnit.find(m_strSearch.GetString());

	if (m_mapUnit.end() == iter_find)
		return;
	m_strName = iter_find->second->wstrName.c_str();
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE); // 모든 버튼 체크 해제

	// 현재 유닛이 갖고있는 직업에 체크.
	m_Radio[iter_find->second->iJobIndex].SetCheck(TRUE);

	UpdateData(FALSE);
}
