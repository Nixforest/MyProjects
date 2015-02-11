
// DialogCreateMSGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DialogCreateMSG.h"
#include "DialogCreateMSGDlg.h"
#include "afxdialogex.h"

#define	WND_WIDTH			1000
#define	WND_HEIGHT			700
#define	WND_NAME			_T("MsgCreator")
#define SCREEN_WIDTH		1366
#define SCREEN_HEIGHT		768
#define CHECK_BOOTSCREEN	1
#define TIMER_CHECK_BS		5000
#define	BS_WND_NAME			_T("PCPfBootScreen")
#define	HOOKSTARTSCREEN_TITLE		_T("Start Screen: Hook Window")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDialogCreateMSGDlg dialog




CDialogCreateMSGDlg::CDialogCreateMSGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogCreateMSGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsShowMsg = FALSE;
}

void CDialogCreateMSGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialogCreateMSGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogCreateMSGDlg message handlers

BOOL CDialogCreateMSGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here
	
	this->SetWindowText(WND_NAME);
	::SetWindowPos(this->GetSafeHwnd(), HWND_NOTOPMOST,
		(SCREEN_WIDTH - WND_WIDTH) / 2,
		(SCREEN_HEIGHT - WND_HEIGHT) / 2, WND_WIDTH, WND_HEIGHT, NULL);
	SetTimer(CHECK_BOOTSCREEN, TIMER_CHECK_BS, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogCreateMSGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDialogCreateMSGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDialogCreateMSGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialogCreateMSGDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case CHECK_BOOTSCREEN:
		{
			 CWnd* hBS = FindWindow(NULL, BS_WND_NAME);
			if (hBS)
			{
				if (!m_bIsShowMsg)
				{
					m_bIsShowMsg = TRUE;
					int nRet = MessageBox(_T("Content"), _T("Error"), MB_OK);
					if(nRet == IDOK)
					{
						m_bIsShowMsg = FALSE;
					}
				}
			}
		}
		break;
	default: break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDialogCreateMSGDlg::OnOK()
{
	CDialogEx::OnOK();
}
