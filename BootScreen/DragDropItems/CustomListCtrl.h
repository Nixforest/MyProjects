#pragma once
#include "afxcmn.h"
#include "DropTarget.h"
#include "DropSource.h"

class CCustomListCtrl :
	public CListCtrl, public CDropTarget, public CDropSource
{
public:
	CCustomListCtrl(void);
	virtual ~CCustomListCtrl(void);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObj,
		DROPEFFECT dropEffect, CPoint point);
protected:
	virtual void CompleteMove();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

