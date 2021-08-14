#pragma once

#include <afxwin.h>

// CBackObjTool 대화 상자

class CBackObjTool : public CDialog
{
	DECLARE_DYNAMIC(CBackObjTool)

public:
	CBackObjTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBackObjTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKOBJTOOL };
#endif
private:
	void Render(int& index, CStatic& image, bool listflag);
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public: 
	void InputList(int _count);
	void DeleteAll();
public:
	CListBox m_ImageListBox;
	CListBox m_ObjectListBox;
	CStatic  m_Picture;
	CStatic  m_ObjectPicture;
	int iImageIndex;
	int iListIndex;
	int count = 0;
	CDeviceMgr*    m_pDeviceMgr;
	CTextureMgr*   m_pTextureMgr;
	bool check = false;
public:
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSetAngle();
	afx_msg void OnLbnSelchangeObjectList();
	afx_msg void OnLbnSelchangeImageList();
	float m_Size;
	float m_Angle;
};
