#pragma once



// CMyForm �� ���Դϴ�.
#include "UnitTool.h"
#include "TileTool.h"
#include "BackTool.h"
#include "BackObjTool.h"
#include "KillObjTool.h"
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

public: // Message Functions
	afx_msg void OnBnClickedTileTool();
	afx_msg void OnBnClickedUnitTool();
	const CTileTool& GetTileIndex() const;
public:
	CFont		m_Font;	
	CButton m_Radio[3];
	CUnitTool	m_UnitTool;
	CTileTool	m_TileTool;
	CBackTool   m_BackTool;
	CBackObjTool   m_BackObjTool;
	CKillObjTool m_KillObjTool;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};


