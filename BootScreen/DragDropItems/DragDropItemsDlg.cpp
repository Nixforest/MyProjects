/************************* Reference *****************************/
/* http://flylib.com/books/en/4.348.1.88/1/ */
/* http://www.codeproject.com/Articles/1951/Drag-and-Drop-between-and-within-a-CListCtrl?rp=/KB/list/dragtest/DragTest_demo.zip */
/* http://www.codeguru.com/cpp/misc/misc/draganddrop/article.php/c255/Drag-and-Drop-Between-Any-CWndDerived-Window.htm */
/* http://www.codeguru.com/cpp/misc/misc/draganddrop/article.php/c349/Drag-And-Drop-between-Window-Controls.htm */
/* http://www.codeproject.com/Articles/840/How-to-Implement-Drag-and-Drop-Between-Your-Progra */
/* http://www.codeproject.com/Questions/64426/How-to-change-the-default-cursor-during-drag-and-d */
/************************* Reference *****************************/

// DragDropItemsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DragDropItems.h"
#include "DragDropItemsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDragDropItemsDlg dialog



CDragDropItemsDlg::CDragDropItemsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDragDropItemsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDragDropItemsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_arrToggleBtnList[0]);
	DDX_Control(pDX, IDC_CHECK2, m_arrToggleBtnList[1]);
	DDX_Control(pDX, IDC_CHECK3, m_arrToggleBtnList[2]);
	DDX_Control(pDX, IDC_CHECK4, m_arrToggleBtnList[3]);
	DDX_Control(pDX, IDC_CHECK5, m_arrToggleBtnList[4]);
	DDX_Control(pDX, IDC_CHECK6, m_arrToggleBtnList[5]);
	DDX_Control(pDX, IDC_CHECK7, m_arrToggleBtnList[6]);
	DDX_Control(pDX, IDC_CHECK8, m_arrToggleBtnList[7]);
	DDX_Control(pDX, IDC_CHECK9, m_arrToggleBtnList[8]);
	DDX_Control(pDX, IDC_CHECK10, m_arrToggleBtnList[9]);
	DDX_Control(pDX, IDC_CHECK11, m_arrToggleBtnList[10]);
	DDX_Control(pDX, IDC_CHECK12, m_arrToggleBtnList[11]);
	DDX_Control(pDX, IDC_CHECK13, m_arrToggleBtnList[12]);
	DDX_Control(pDX, IDC_CHECK14, m_arrToggleBtnList[13]);
	DDX_Control(pDX, IDC_CHECK15, m_arrToggleBtnList[14]);
	DDX_Control(pDX, IDC_CHECK16, m_arrToggleBtnList[15]);
	DDX_Control(pDX, IDC_CHECK17, m_arrToggleBtnList[16]);
	DDX_Control(pDX, IDC_CHECK18, m_arrToggleBtnList[17]);
	DDX_Control(pDX, IDC_CHECK19, m_arrToggleBtnList[18]);
	DDX_Control(pDX, IDC_CHECK20, m_arrToggleBtnList[19]);
	DDX_Control(pDX, IDC_CHECK21, m_arrToggleBtnList[20]);
	DDX_Control(pDX, IDC_CHECK22, m_arrToggleBtnList[21]);
	DDX_Control(pDX, IDC_CHECK23, m_arrToggleBtnList[22]);
	DDX_Control(pDX, IDC_CHECK24, m_arrToggleBtnList[23]);
	DDX_Control(pDX, IDC_CHECK25, m_arrToggleBtnList[24]);
	DDX_Control(pDX, IDC_CHECK26, m_arrToggleBtnList[25]);
	DDX_Control(pDX, IDC_CHECK27, m_arrToggleBtnList[26]);
	DDX_Control(pDX, IDC_CHECK28, m_arrToggleBtnList[27]);
	DDX_Control(pDX, IDC_CHECK29, m_arrToggleBtnList[28]);
	DDX_Control(pDX, IDC_CHECK30, m_arrToggleBtnList[29]);
	DDX_Control(pDX, IDC_CHECK31, m_arrToggleBtnList[30]);
	DDX_Control(pDX, IDC_CHECK32, m_arrToggleBtnList[31]);
	DDX_Control(pDX, IDC_CHECK33, m_arrToggleBtnList[32]);
	DDX_Control(pDX, IDC_CHECK34, m_arrToggleBtnList[33]);
	DDX_Control(pDX, IDC_CHECK35, m_arrToggleBtnList[34]);
	DDX_Control(pDX, IDC_CHECK36, m_arrToggleBtnList[35]);
	DDX_Control(pDX, IDC_CHECK37, m_arrToggleBtnList[36]);
	DDX_Control(pDX, IDC_CHECK38, m_arrToggleBtnList[37]);
	DDX_Control(pDX, IDC_CHECK39, m_arrToggleBtnList[38]);
	DDX_Control(pDX, IDC_CHECK40, m_arrToggleBtnList[39]);
	DDX_Control(pDX, IDC_CHECK41, m_arrToggleBtnList[40]);
	DDX_Control(pDX, IDC_CHECK42, m_arrToggleBtnList[41]);
	DDX_Control(pDX, IDC_CHECK43, m_arrToggleBtnList[42]);
	DDX_Control(pDX, IDC_CHECK44, m_arrToggleBtnList[43]);
	DDX_Control(pDX, IDC_CHECK45, m_arrToggleBtnList[44]);
	DDX_Control(pDX, IDC_CHECK46, m_arrToggleBtnList[45]);
	DDX_Control(pDX, IDC_CHECK47, m_arrToggleBtnList[46]);
	DDX_Control(pDX, IDC_CHECK48, m_arrToggleBtnList[47]);
	DDX_Control(pDX, IDC_CHECK49, m_arrToggleBtnList[48]);
	DDX_Control(pDX, IDC_CHECK50, m_arrToggleBtnList[49]);
	DDX_Control(pDX, IDC_CHECK51, m_arrToggleBtnList[50]);
	DDX_Control(pDX, IDC_CHECK52, m_arrToggleBtnList[51]);
	DDX_Control(pDX, IDC_CHECK53, m_arrToggleBtnList[52]);
	DDX_Control(pDX, IDC_CHECK54, m_arrToggleBtnList[53]);
	DDX_Control(pDX, IDC_CHECK55, m_arrToggleBtnList[54]);
	DDX_Control(pDX, IDC_CHECK56, m_arrToggleBtnList[55]);
	DDX_Control(pDX, IDC_CHECK57, m_arrToggleBtnList[56]);
	DDX_Control(pDX, IDC_CHECK58, m_arrToggleBtnList[57]);
	DDX_Control(pDX, IDC_CHECK59, m_arrToggleBtnList[58]);
	DDX_Control(pDX, IDC_CHECK60, m_arrToggleBtnList[59]);

	DDX_Control(pDX, IDC_LIST_ANNO_ASSIGN, m_ListCtrlAnno);
}

BEGIN_MESSAGE_MAP(CDragDropItemsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDragDropItemsDlg message handlers

BOOL CDragDropItemsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MAXIMIZE);

	/* Load data for list of toggle buttons */
	LoadListToggleButtonData();
	/* Load data for list control */
	LoadListControlData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragDropItemsDlg::LoadListToggleButtonData()
{
	for (int i = 0; i < TOGGLE_BTN_NUM; i++)
	{
		m_arrToggleBtnList[i].SetAnnotationID(m_Data.GetIdByPosition(i));
		ANNOTATION_DATA_t* pAnnoData = m_Data.GetAnnotationByID(m_arrToggleBtnList[i].GetAnnotationID());
		if (pAnnoData)
		{
			m_arrToggleBtnList[i].SetWindowTextW(pAnnoData->szKey);
		}
		else
		{
			m_arrToggleBtnList[i].SetWindowTextW(_T(""));
		}
	}
}
void CDragDropItemsDlg::LoadListControlData()
{
	LVCOLUMN lvCol;
	int nCol;
	/* Index column */
	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 110;
	lvCol.pszText = _T("");
	nCol = m_ListCtrlAnno.InsertColumn(0, &lvCol);

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 60;
	lvCol.pszText = LIST_COLUM_CLASS;
	nCol = m_ListCtrlAnno.InsertColumn(1, &lvCol);

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 100;
	lvCol.pszText = LIST_COLUM_KEY;
	m_ListCtrlAnno.InsertColumn(2, &lvCol);

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 300;
	lvCol.pszText = LIST_COLUM_WORD;
	m_ListCtrlAnno.InsertColumn(3, &lvCol);
	LVITEM lvItem;
	int nItem;

	for (int i = 0; i < TOGGLE_BTN_NUM; i++)
	{
		int nIndex = m_Data.GetIdByPosition(i);
		CString szClass;
		ANNOTATION_DATA_t* pAnnoData = m_Data.GetAnnotationByID(nIndex);
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		if (pAnnoData)
		{
			szClass.Format(_T("%d"), pAnnoData->unID);
			lvItem.pszText = (LPTSTR)(LPCTSTR)szClass;
		}
		else
		{
			lvItem.pszText = _T("");
		}
		nItem = m_ListCtrlAnno.InsertItem(&lvItem);

		if (pAnnoData)
		{
			szClass.Format(_T("%d"), pAnnoData->unClassID);
			m_ListCtrlAnno.SetItemText(nItem, 1, szClass);
			m_ListCtrlAnno.SetItemText(nItem, 2, pAnnoData->szKey);
			m_ListCtrlAnno.SetItemText(nItem, 3, pAnnoData->szWord);
		}
		else
		{
			m_ListCtrlAnno.SetItemText(nItem, 1, _T(""));
			m_ListCtrlAnno.SetItemText(nItem, 2, _T(""));
		}
	}
	m_ListCtrlAnno.SetExtendedStyle(LVS_EX_FULLROWSELECT /*| LVS_EX_GRIDLINES*/);
	m_ListCtrlAnno.Initialize(&m_ListCtrlAnno);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDragDropItemsDlg::OnPaint()
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
HCURSOR CDragDropItemsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
