// ToolTipDlg.h : header file
//

#if !defined(AFX_TOOLTIPDLG_H__10A12DAB_C959_4C35_8D88_FB56A280D628__INCLUDED_)
#define AFX_TOOLTIPDLG_H__10A12DAB_C959_4C35_8D88_FB56A280D628__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TTComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg dialog

class CToolTipDlg : public CDialog
{
// Construction
public:
	CToolTipDlg(CWnd* pParent = NULL);	// standard constructor
	CToolTipDlg::~CToolTipDlg();

// Dialog Data
	//{{AFX_DATA(CToolTipDlg)
	enum { IDD = IDD_TOOLTIP_DIALOG };
	CEdit	m_edit;
	CTTComboBox	m_combo;
	CTTComboBox	m_combo2;
	CTTComboBox	m_combo3;
	CComboBox	m_combo4;
	CTTComboBox	m_combo5;
	CTTComboBox	m_combo6;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	//}}AFX_VIRTUAL

	// The callback function is used with the API function - EnumFontFamilies
	// it received data describing available fonts.
	static int CALLBACK EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam);

// Implementation
protected:
//	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CToolTipDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPDLG_H__10A12DAB_C959_4C35_8D88_FB56A280D628__INCLUDED_)
