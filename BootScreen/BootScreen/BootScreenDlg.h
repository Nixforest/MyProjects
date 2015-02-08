
// BootScreenDlg.h : header file
//

#pragma once
typedef BOOL (WINAPI* InstanceFunc)(HWND);

// CBootScreenDlg dialog
class CBootScreenDlg : public CDialogEx
{
// Construction
public:
	CBootScreenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BOOTSCREEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
private:
	virtual void OnOK();
	BOOL m_bIsShowMsg;
};
