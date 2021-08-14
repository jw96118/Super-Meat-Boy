#pragma once
#include <afxwin.h>
class CTileTool :
	public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTileTool();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
public:
	const int& GetTile() const;
	const float& GetAngle() const;
	const float& GetChangeX() const;
	const float& GetChangeY() const;
	const RECT* GetCol() const;
	afx_msg void OnLbnSelchangeTile();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
private:
	void TileRender();
public: // Control Variables
	CListBox m_ListBox;
	CStatic  m_Picture;
	CButton m_Check[2];
	CButton m_CheckCol[COL_END];
	int iIndex;

	CDeviceMgr* m_pDeviceMgr;
	CSpriteMgr* m_pSpriteMgr;

	float fangle;
	float changeX;
	float changeY;
	RECT Col[COL_END];

	afx_msg void OnEnChangeAngle();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedSetangle();


	float angle;
	afx_msg void OnBnClickedCheckLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedTop();
	afx_msg void OnBnClickedBottom();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
};

