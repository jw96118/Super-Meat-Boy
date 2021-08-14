#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public: // Message Functions
	afx_msg void OnBnClickedPush();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedDelete();
public:
	virtual BOOL OnInitDialog();

public:	// Value Variables
	CString m_strInput; // ù��° EditControl�� �Էº���	
	CString m_strOutput; // �ι�° EditControl�� ��º���	
						
	CString m_strName;  // ĳ�����̸�	
	CString m_strSearch;  // ĳ�����̸�	
	int m_iAtt; // ĳ���� ���ݷ�	
	int m_iDef; // ĳ���� ����

public: // Control Variables
	CListBox m_ListBox;
	CButton m_Radio[3];

public: // User Variables
	map<wstring, UNIT_DATA*>	m_mapUnit;	
	
	
	afx_msg void OnFindName();
};
