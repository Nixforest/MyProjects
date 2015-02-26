
// DragDropItemsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "dragdropitems_defs.h"
#include "CustomBtn.h"
#include "AnnotationData.h"
#include "afxcmn.h"
#include "CustomListCtrl.h"
#include "CustomListBox.h"


// CDragDropItemsDlg dialog
class CDragDropItemsDlg : public CDialogEx
{
// Construction
public:
	CDragDropItemsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DRAGDROPITEMS_DIALOG };

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
private:
	CCustomBtn		m_arrToggleBtnList[TOGGLE_BTN_NUM];
	CAnnotationData m_Data;
	void			LoadListToggleButtonData();					/* Load list toggle buttons data	*/
	void			LoadListControlData();						/* Load list control data			*/
	void			LoadListSystemAnnoData();					/* Load list system annotation data */
public:
	CCustomListCtrl m_ListCtrlAnno;
	CCustomListBox	m_ListBoxSysAnno;
	virtual void OnOK();
	afx_msg void OnBnClickedSave2();
};
