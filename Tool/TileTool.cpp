#include "stdafx.h"

#include "Tool.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "TileTool.h"

#include "Sprite.h"
#include "SpriteTerrain.h"
#include "TileObject.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"

// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent), m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pSpriteMgr(CSpriteMgr::GetInstance()), fangle(0.f),
changeX (1.f),
changeY (1.f)
, angle(0)
{

}



CTileTool::~CTileTool()
{
}

void CTileTool::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_CHECK1, m_Check[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Check[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckCol[LEFT]);//왼쪽
	DDX_Control(pDX, IDC_CHECK4, m_CheckCol[RIGHT]);//오른쪽
	DDX_Control(pDX, IDC_CHECK5, m_CheckCol[TOP]);//위쪽
	DDX_Control(pDX, IDC_CHECK6, m_CheckCol[BOTTOM]);//아래쪽
	DDX_Control(pDX, IDC_CHECK7, m_CheckCol[UPBOTTOM]);//아래쪽
	DDX_Control(pDX, IDC_CHECK8, m_CheckCol[BOTTOMUP]);//아래쪽
	DDX_Text(pDX, IDC_EDIT1, angle);
}

BEGIN_MESSAGE_MAP(CTileTool, CDialog)

	ON_LBN_SELCHANGE(IDC_LIST2, &CTileTool::OnLbnSelchangeTile)
	ON_BN_CLICKED(ID_SAVE, &CTileTool::OnBnClickedSave)
	ON_BN_CLICKED(ID_LOAD, &CTileTool::OnBnClickedLoad)
	ON_EN_CHANGE(IDC_EDIT1, &CTileTool::OnEnChangeAngle)
	ON_BN_CLICKED(IDC_CHECK1, &CTileTool::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTileTool::OnBnClickedCheck2)
	ON_BN_CLICKED(ID_SETANGLE, &CTileTool::OnBnClickedSetangle)
	ON_BN_CLICKED(IDC_CHECK3, &CTileTool::OnBnClickedCheckLeft)
	ON_BN_CLICKED(IDC_CHECK4, &CTileTool::OnBnClickedRight)
	ON_BN_CLICKED(IDC_CHECK5, &CTileTool::OnBnClickedTop)
	ON_BN_CLICKED(IDC_CHECK6, &CTileTool::OnBnClickedBottom)
	ON_BN_CLICKED(IDC_CHECK7, &CTileTool::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CTileTool::OnBnClickedCheck8)
END_MESSAGE_MAP()

BOOL CTileTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString wstring;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wstring = to_string ( (i * 10) + j).c_str();
			m_ListBox.AddString(wstring);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다
}

const int & CTileTool::GetTile() const
{
	return iIndex;
}

const float & CTileTool::GetAngle() const
{
	return angle;
}

const float & CTileTool::GetChangeX() const
{
	return changeX;
}

const float & CTileTool::GetChangeY() const
{
	return changeY;
}

const RECT * CTileTool::GetCol() const
{
	return Col;
}


void CTileTool::OnLbnSelchangeTile()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	iIndex = m_ListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iIndex) // 없는 대상을 선택했을 때
		return;
	TileRender();
}


void CTileTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pView);

		
		pView->m_pTileObj->SaveObj(Dlg.GetPathName());
	}
}


void CTileTool::OnBnClickedLoad()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pView);

		
		pView->m_pTileObj->LoadObj(Dlg.GetPathName());
		pView->Invalidate(FALSE);
	}
}

void CTileTool::TileRender()
{
	if (m_Check[0].GetCheck())
		changeX = -1.f;
	else
		changeX = 1.f;
	if (m_Check[1].GetCheck())
		changeY = -1.f;
	else
		changeY = 1.f;
	
	D3DXMATRIX matScale, matTrans, matRotZ;
	const CSprite* pTexInfo = nullptr;

	m_pDeviceMgr->Render_Begin();

	float fCenterX = 0.f, fCenterY = 0.f;

	pTexInfo = m_pSpriteMgr->GetSpriteInfo(L"TILE");
	NULL_CHECK(pTexInfo);
	D3DXMatrixScaling(&matScale,
		(float)WINCX / STILECX * changeX ,
		(float)WINCY / STILECY * changeY,
		0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));

	D3DXMatrixTranslation(&matTrans,
		(float)WINCX * 0.5f,
		(float)WINCY * 0.5f,
		0.f);

	RECT	DrawPoint = { STILECX * (iIndex % 10),STILECY * (iIndex / 10),
			 STILECX * ((iIndex % 10) + 1),  STILECY * ((iIndex + 10) / 10) };

	fCenterX = 60 * 0.5f;
	fCenterY = 60 * 0.5f;
	m_pDeviceMgr->Render_Begin();
	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matRotZ * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->GetTex(), &DrawPoint,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pDeviceMgr->Render_End(m_Picture.m_hWnd);
	m_pDeviceMgr->Render_Line_Begin();
	m_pDeviceMgr->Render_Line_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
}


void CTileTool::OnEnChangeAngle()
{
	//cout << m_angle << endl;
}


void CTileTool::OnBnClickedCheck1()
{
	TileRender();
}


void CTileTool::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TileRender();
}


void CTileTool::OnBnClickedSetangle()
{
	UpdateData(TRUE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TileRender();
	UpdateData(false);
}


void CTileTool::OnBnClickedCheckLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CheckCol[LEFT].GetCheck())
	{
		Col[LEFT] = { -STILECX / 2,-STILECY / 2,-STILECX / 2,STILECY / 2 };
	}
	else
		Col[LEFT] = { 0,0,0,0};
}


void CTileTool::OnBnClickedRight()
{
	if (m_CheckCol[RIGHT].GetCheck())
	{
		Col[RIGHT] = { STILECX / 2 ,-STILECY / 2 , STILECX / 2 ,  STILECY / 2 };
	}
	else
		Col[RIGHT] = { 0,0,0,0 };
}


void CTileTool::OnBnClickedTop()
{

	if (m_CheckCol[TOP].GetCheck())
	{
		Col[TOP] = { -STILECX / 2,-STILECY / 2, STILECX / 2 ,  -STILECY / 2 };
		
	}
	else
		Col[TOP] = { 0,0,0,0 };
}


void CTileTool::OnBnClickedBottom()
{

	if (m_CheckCol[BOTTOM].GetCheck())
	{
		Col[BOTTOM] = { -STILECX / 2, STILECY / 2 ,STILECX / 2,  STILECY / 2 };
	}
	else
		Col[BOTTOM] = { 0,0,0,0 };
}


void CTileTool::OnBnClickedCheck7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CheckCol[UPBOTTOM].GetCheck())
	{
		Col[UPBOTTOM] = { -STILECX / 2 - 1, -STILECY / 2 - 1,STILECX / 2 + 1,  STILECY / 2 + 1 };
	}
	else
		Col[UPBOTTOM] = { 0,0,0,0 };
}


void CTileTool::OnBnClickedCheck8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CheckCol[BOTTOMUP].GetCheck())
	{
		Col[BOTTOMUP] = { -STILECX / 2 -1 , STILECY / 2 + 1,STILECX / 2 + 1, - STILECY / 2 -1};
	}
	else
		Col[BOTTOMUP] = { 0,0,0,0 };
}
