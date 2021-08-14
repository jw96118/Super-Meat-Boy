// BackObjTool.cpp: 구현 파일
//
#include "stdafx.h"
#include "Tool.h"
#include "BackObjTool.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "BackObject.h"
#include "Texture.h"
#include "TileObject.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"

// CBackObjTool 대화 상자

IMPLEMENT_DYNAMIC(CBackObjTool, CDialog)

CBackObjTool::CBackObjTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BACKOBJTOOL, pParent),m_pDeviceMgr(CDeviceMgr::GetInstance()),
	 m_pTextureMgr(CTextureMgr::GetInstance()),iImageIndex(0.f), iListIndex(0.f)
	, m_Size(0)
	, m_Angle(0)
{
	

}

CBackObjTool::~CBackObjTool()
{
}
//int& index, CStatic& image
void CBackObjTool::Render(int& index, CStatic& image, bool listflag)
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";
	if (!listflag)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"TileObject", L"FOREST", index);
	}
	else
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pView);

		pTexInfo = m_pTextureMgr->GetTexInfo(L"TileObject", L"FOREST", pView->m_pTileObj->BObjectImage(index));
	}
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		(float)WINCX / pTexInfo->tImgInfo.Width,
		(float)WINCY / pTexInfo->tImgInfo.Height,
		0.f);

	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);

	m_pDeviceMgr->Render_Begin();
	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pDeviceMgr->Render_End(image.m_hWnd);
	m_pDeviceMgr->Render_Line_Begin();
	m_pDeviceMgr->Render_Line_End(image.m_hWnd);
	UpdateData(FALSE);

}

BOOL CBackObjTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString wstring;

	for (int i = 0; i < 28; i++)
	{
		wstring = to_string(i).c_str();
		m_ImageListBox.AddString(wstring);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다
}

void CBackObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_LIST, m_ImageListBox);
	DDX_Control(pDX, IDC_LISTIMAGE, m_Picture);
	DDX_Control(pDX, IDC_OBJECT_LIST, m_ObjectListBox);
	DDX_Control(pDX, IDC_OBJ_PICTURE, m_ObjectPicture);
	DDX_Text(pDX, IDC_OBJ_SIZE, m_Size);
	DDX_Text(pDX, IDC_OBJ_ANGLE, m_Angle);
}

void CBackObjTool::InputList(int _count)
{
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	CString wstring;
	wstring = to_string(count).c_str();
	m_ObjectListBox.AddString(wstring);
	count++;

	m_Angle = pView->m_pTileObj->GetBackObj(iListIndex, true)->m_fAngle;
	m_Size = pView->m_pTileObj->GetBackObj(iListIndex, true)->m_fSize;
}

void CBackObjTool::DeleteAll()
{
	count = 0;
	m_ObjectListBox.ResetContent();
}


BEGIN_MESSAGE_MAP(CBackObjTool, CDialog)
	ON_BN_CLICKED(ID_INSERT, &CBackObjTool::OnBnClickedInsert)
	ON_BN_CLICKED(ID_DELETE, &CBackObjTool::OnBnClickedDelete)
	ON_BN_CLICKED(ID_SET_ANGLE, &CBackObjTool::OnBnClickedSetAngle)
	ON_LBN_SELCHANGE(IDC_OBJECT_LIST, &CBackObjTool::OnLbnSelchangeObjectList)
	ON_LBN_SELCHANGE(IDC_IMAGE_LIST, &CBackObjTool::OnLbnSelchangeImageList)
END_MESSAGE_MAP()


// CBackObjTool 메시지 처리기


void CBackObjTool::OnBnClickedInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->InsertBackObj(pView,D3DXVECTOR3{0.f,0.f,0.f}, D3DXVECTOR3{ 1.f,1.f,0.f }, iImageIndex,0.f);
	CString wstring;
	wstring = to_string(count).c_str();
	m_ObjectListBox.AddString(wstring);
	count++;

	m_Angle = pView->m_pTileObj->GetBackObj(iListIndex,true)->m_fAngle;
	m_Size = pView->m_pTileObj->GetBackObj(iListIndex, true)->m_fSize;
	pView->Invalidate(FALSE);
}


void CBackObjTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	m_Angle = 0;
	m_Size = 0;
	m_ObjectListBox.DeleteString(iListIndex);
	pView->m_pTileObj->DeleteBackObj(iListIndex);
	pView->Invalidate(FALSE);
}


void CBackObjTool::OnBnClickedSetAngle()
{

	if (!check)
		return;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Render(iListIndex, m_ObjectPicture, true);

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->SetBackObj(iListIndex, m_Size, iImageIndex, m_Angle);
	UpdateData(false);

	pView->Invalidate(FALSE);
}


void CBackObjTool::OnLbnSelchangeObjectList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iListIndex = m_ObjectListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iListIndex) // 없는 대상을 선택했을 때
	{
		check = false;
		return;
	}
	Render(iListIndex, m_ObjectPicture,true);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->SelectBObject(iListIndex);
	m_Angle = pView->m_pTileObj->GetBackObj(iListIndex)->m_fAngle;
	m_Size = pView->m_pTileObj->GetBackObj(iListIndex)->m_fSize;
	cout << pView->m_pTileObj->GetBackObj(iListIndex)->m_fSize << endl;
	check = true;
}


void CBackObjTool::OnLbnSelchangeImageList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iImageIndex = m_ImageListBox.GetCurSel(); // 선택한 대상의 인덱스를 얻어옴.

	if (-1 == iImageIndex) // 없는 대상을 선택했을 때
		return;
	Render(iImageIndex, m_Picture,false);

}
