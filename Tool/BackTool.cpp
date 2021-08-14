#include "stdafx.h"

#include "Tool.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "BackTool.h"

#include "Texture.h"
#include "TileObject.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"

IMPLEMENT_DYNAMIC(CBackTool, CDialog)

CBackTool::CBackTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent), m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pSpriteMgr(CSpriteMgr::GetInstance()), m_pTextureMgr(CTextureMgr::GetInstance()),Size(1.f)
{

}

CBackTool::~CBackTool()
{
}

void CBackTool::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SIZE, Size);
	DDX_Control(pDX, IDC_BACK, m_ListBox);
	DDX_Control(pDX, IDC_BACK_PICTURE, m_Picture);
}

BOOL CBackTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString wstring;

	wstring = "Back";
	m_ListBox.AddString(wstring);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�
}

const float & CBackTool::GetSize() const
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return Size;
}

void CBackTool::BackRender()
{

	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	pTexInfo = m_pTextureMgr->GetTexInfo(L"BackGround", L"BACK", iIndex);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&matScale,
		(float)WINCX / pTexInfo->tImgInfo.Width ,
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
	m_pDeviceMgr->Render_End(m_Picture.m_hWnd);
	m_pDeviceMgr->Render_Line_Begin();
	m_pDeviceMgr->Render_Line_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
}
BEGIN_MESSAGE_MAP(CBackTool, CDialog)
	ON_BN_CLICKED(ID_SETSIZE, &CBackTool::OnBnClickedSetsize)
	ON_LBN_SELCHANGE(IDC_BACK, &CBackTool::OnLbnSelchangeBack)
END_MESSAGE_MAP()


void CBackTool::OnBnClickedSetsize()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTileObj->SetBackGroundSize(Size);
	BackRender();
	UpdateData(false);
	pView->Invalidate(FALSE);
}


void CBackTool::OnLbnSelchangeBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	iIndex = m_ListBox.GetCurSel(); // ������ ����� �ε����� ����.

	if (-1 == iIndex) // ���� ����� �������� ��
		return;
	BackRender();
}
