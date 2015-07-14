// ToolTipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTip.h"
#include "ToolTipDlg.h"
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg dialog

CToolTipDlg::CToolTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolTipDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Here is to disable too-tip for specified combobox
//	m_combo4.SetToolTip(FALSE);
}

CToolTipDlg::~CToolTipDlg()
{

}

void CToolTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTipDlg)
	DDX_Control(pDX, IDC_COMBO5, m_combo5);
	DDX_Control(pDX, IDC_COMBO6, m_combo6);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_COMBO4, m_combo4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolTipDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTipDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	//ON_NOTIFY(TTN_NEEDTEXTW, 0, OnToolTipNotify)
	//ON_NOTIFY(TTN_NEEDTEXTA, 0, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg message handlers


BOOL CToolTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Initialize the edit-box and combo-box here.

	m_edit.SetWindowText(_T("\
horizontal scroll-bar\r\n\
Make overview of the selected font\r\n\
Make the tool-tip for the portion invisible option"));
	m_combo.ResetContent(); // Clean up all contents
	::EnumFontFamilies(GetDC()->m_hDC, NULL, (FONTENUMPROC)EnumFontFamProc, (LPARAM)this);
	m_combo.SetCurSel(0);
	m_combo2.SetCurSel(0);
	m_combo3.SetCurSel(0);
	m_combo4.SetCurSel(0);

	m_combo5.SetCurSel(0);
	m_combo5.SetDroppedWidth(150);
	m_combo5.SetAlignStyle(CTTComboBox::alignMiddle);

	m_combo6.SetCurSel(0);
	m_combo6.SetDisabledItem(1);
	m_combo6.SetDisabledItem(4);

	m_combo.SetTipText(0, _T("This is a customized tip text!"));
	//m_combo.SetTipText(0, NULL);
	m_combo5.SetTipText(0, _T("This is a customized tip text!"));
	m_combo6.SetTipText(1, _T("This is a customized tip text!"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CToolTipDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolTipDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CToolTipDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// The callback function is used with the API function - EnumFontFamilies
// it received data describing available fonts.
int CALLBACK CToolTipDlg::EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
{
	CToolTipDlg* pDlg = (CToolTipDlg*)lParam;
	int nItem = pDlg->m_combo.AddString((TCHAR*)lpelf->elfFullName);
	CFont* pFont = new CFont;
	pFont->CreateFontIndirect(&lpelf->elfLogFont);
	pDlg->m_combo.SetItemData(nItem, DWORD(pFont));

	return 1;
}

void CToolTipDlg::OnSelchangeCombo1() 
{
	int nSel = m_combo.GetCurSel();
	if (nSel == LB_ERR)
		return;

	CFont* pFont = reinterpret_cast<CFont*>(m_combo.GetItemData(nSel));
	LOGFONT logfont;
	pFont->GetLogFont(&logfont);
	logfont.lfHeight = 12;
	logfont.lfWidth = 6;
	pFont->DeleteObject();
	pFont->CreateFontIndirect(&logfont);
	m_edit.SetFont(pFont, TRUE);
	
}

void CToolTipDlg::OnDestroy() 
{
	while (m_combo.GetCount())
	{
		CFont* pFont = (CFont*)m_combo.GetItemData(0);
		if (pFont != NULL)
			delete pFont;

		m_combo.DeleteString(0);
	}

	CDialog::OnDestroy();	
}
