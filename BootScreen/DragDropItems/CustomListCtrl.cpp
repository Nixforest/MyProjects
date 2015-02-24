#include "StdAfx.h"
#include "CustomListCtrl.h"


CCustomListCtrl::CCustomListCtrl(void)
{
}


CCustomListCtrl::~CCustomListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CCustomListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCustomListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);
	int nPos = GetSelectionMark();
	if (nPos == -1)
	{
		return;
	}
	RECT rClient;
	GetClientRect(&rClient);
	CString nIndex = GetItemText(nPos, 0);
	StartDragging((DWORD)_ttoi(nIndex), &rClient, &point);
}

BOOL CCustomListCtrl::OnDrop(CWnd* pWnd, COleDataObject* pDataObj,
		DROPEFFECT dropEffect, CPoint point)
{
	HGLOBAL hGlobal;
	int nPos = -1;

	hGlobal = pDataObj->GetGlobalData(CF_OWNERDISPLAY);
	LPCTSTR pData = (LPCTSTR)GlobalLock(hGlobal);
	ASSERT(pData != NULL);

	GlobalUnlock(hGlobal);
	if (nPos < 0)
	{
		return FALSE;
	}
	return TRUE;
}

void CCustomListCtrl::CompleteMove()
{
	//POSITION pos = GetFirstSelectedItemPosition();
	int nItem = GetSelectionMark();
	if (nItem == -1)
	{
		return;
	}
	DeleteItem(nItem);
	SetSelectionMark(nItem - 1);
}