#pragma once
#include <afxwin.h>
class CBackTool :
	public CDialog
{
	DECLARE_DYNAMIC(CBackTool)

public:
	CBackTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBackTool();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
public:
	const float& GetSize() const;

private:
	void BackRender();
	afx_msg void OnBnClickedSetsize();
public: // Control Variables
	CListBox m_ListBox;
	CStatic  m_Picture;

	int iIndex;

	CDeviceMgr* m_pDeviceMgr;
	CSpriteMgr* m_pSpriteMgr;
	CTextureMgr*	m_pTextureMgr;
	float Size;
	afx_msg void OnLbnSelchangeBack();
};