
// BootScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BootScreen.h"
#include "BootScreenDlg.h"
#include "afxdialogex.h"

#define	WND_WIDTH		900
#define	WND_HEIGHT		700
#define SCREEN_WIDTH	1366
#define SCREEN_HEIGHT	768
#define	WND_NAME		_T("Boot Screen")
#define CHECK_BOOTSCREEN	1
#define TIMER_CHECK_BS		5000
#define	MSG_CREATOR_WND_NAME			_T("MsgCreator")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBootScreenDlg dialog

/* Global module */
HMODULE	hDLL;
HHOOK CBootScreenDlg::s_HookMsgBox = NULL;

typedef VOID(*LOADPROC)(HHOOK hHook);



CBootScreenDlg::CBootScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBootScreenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsShowMsg = FALSE;
	if (!InstallHook())
	{
		MessageBox(_T("Install hook error"), _T("Error"), NULL);
	}
}
BOOL CBootScreenDlg::InstallHook()
{
	if (LoadLibrary(_T("HookMessageBox.dll")) == NULL)
	{
		MessageBox(_T("Load library error"), _T("Error"), NULL);
		return FALSE;
	}
	hDLL = GetModuleHandle(_T("HookMessageBox"));
	if (!hDLL)
	{
		return FALSE;
	}
	s_HookMsgBox = SetWindowsHookEx(WH_CBT/*WH_MSGFILTER*/,
		(HOOKPROC)GetProcAddress(hDLL, "HookMessageBoxProc"), hDLL, 0);
	LOADPROC fPtrFcnt;
	fPtrFcnt = (LOADPROC)GetProcAddress(hDLL, "SetGlobalHookHandle");
	if (!fPtrFcnt)
	{
		return FALSE;
	}
	fPtrFcnt(s_HookMsgBox);
	return TRUE;
}
void CBootScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBootScreenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CBootScreenDlg message handlers

BOOL CBootScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	this->SetWindowTextW(WND_NAME);
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST,
		(SCREEN_WIDTH - WND_WIDTH) / 2,
		(SCREEN_HEIGHT - WND_HEIGHT) / 2, WND_WIDTH, WND_HEIGHT, NULL);
		
	//SetTimer(CHECK_BOOTSCREEN, TIMER_CHECK_BS, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBootScreenDlg::OnPaint()
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
HCURSOR CBootScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBootScreenDlg::OnOK()
{
	/* Un-Install hook */
	/*HINSTANCE hInstance;
	hInstance = LoadLibrary(_T("HookMessageBox.dll"));
	if (hInstance)
	{
		auto UnInstall = (LRESULT(*)(HWND)) GetProcAddress(hInstance, "UnInstallHook");
		if (UnInstall)
		{
			UnInstall(this->GetSafeHwnd());
		}
	}*/
	if (s_HookMsgBox && UnhookWindowsHookEx(s_HookMsgBox))
	{
		s_HookMsgBox = NULL;
	}

	CDialogEx::OnOK();
}


void CBootScreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case CHECK_BOOTSCREEN:
		{
			CWnd* hBS = FindWindow(NULL, MSG_CREATOR_WND_NAME);
			if (!hBS)
			{
				if (!m_bIsShowMsg)
				{
					m_bIsShowMsg = TRUE;
					//int nRet = MessageBox(_T("Content"), _T("Error"), MB_OK);
					int nRet = MessageBox(_T("Content"), _T("Error"), MB_OK | MB_SETFOREGROUND);
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
