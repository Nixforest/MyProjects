
// DialogCreateMSGDlg.h : header file
//

#pragma once

typedef BOOL(WINAPI* InstanceFunc)(HWND);

// CDialogCreateMSGDlg dialog
class CDialogCreateMSGDlg : public CDialogEx
{
// Construction
public:
	CDialogCreateMSGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DIALOGCREATEMSG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	BOOL	m_bIsShowMsg;
	virtual void OnOK();
};
