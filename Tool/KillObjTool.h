#pragma once

#include <afxwin.h>
// CKillObjTool 대화 상자

class CKillObjTool : public CDialog
{
	DECLARE_DYNAMIC(CKillObjTool)

public:
	CKillObjTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CKillObjTool();
public:
	virtual BOOL OnInitDialog();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KILLOBJTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void DeleteAll();
	void InputList(int _count);
public:
	CListBox m_ImageListBox;
	CListBox m_ObjectListBox;
	int iImageIndex;
	int iListIndex;
	int count = 0;
	CDeviceMgr*    m_pDeviceMgr;
	CTextureMgr*   m_pTextureMgr;
	bool check = false;
	float m_fSize;
	bool update = false;
	afx_msg void OnLbnSelchangeKillobjList();
	afx_msg void OnLbnSelchangeNowKillobjectList();
	afx_msg void OnBnClickedInsertKill();
	afx_msg void OnBnClickedSetKill();
	afx_msg void OnBnClickedDeleteKiill();
	afx_msg void OnBnClickedSetUpdate();
	afx_msg void OnBnClickedSetStop();
	float m_fAngle;
};
