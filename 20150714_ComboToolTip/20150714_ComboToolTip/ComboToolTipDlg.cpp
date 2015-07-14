
// ComboToolTipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "20150714_ComboToolTip.h"
#include "ComboToolTipDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComboToolTipDlg dialog




CComboToolTipDlg::CComboToolTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComboToolTipDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboToolTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbProtocol);
}

BEGIN_MESSAGE_MAP(CComboToolTipDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CComboToolTipDlg message handlers

BOOL CComboToolTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	/* Create data for combobox */
	m_cbProtocol.AddString(_T("Item 123423423423432423"));
	m_cbProtocol.AddString(_T("Item 2"));
	m_cbProtocol.AddString(_T("Item 34444444"));
	m_cbProtocol.AddString(_T("Item 423424234234234"));
	m_cbProtocol.AddString(_T("Item 5"));
	m_cbProtocol.AddString(_T("Item 6dddddddddd"));
	m_cbProtocol.SetToolTip(1);
	m_cbProtocol.SetTipText(0, _T("This is a customized tip text!"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComboToolTipDlg::OnPaint()
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
HCURSOR CComboToolTipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComboToolTipDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* pWnd = ChildWindowFromPoint(point);
	if (pWnd)
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))
		{
			
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
