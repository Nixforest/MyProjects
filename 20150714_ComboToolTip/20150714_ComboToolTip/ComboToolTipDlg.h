
// ComboToolTipDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TTComboBox.h"


// CComboToolTipDlg dialog
class CComboToolTipDlg : public CDialogEx
{
// Construction
public:
	CComboToolTipDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY20150714_COMBOTOOLTIP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTTComboBox m_cbProtocol;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
