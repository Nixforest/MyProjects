#include "StdAfx.h"
#include "CustomListCtrl.h"

/* Init static variable */
int CCustomListCtrl::s_nDropTargetID = -1;

/* Constructor */
CCustomListCtrl::CCustomListCtrl(void)
{
}

/* Destructor */
CCustomListCtrl::~CCustomListCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CCustomListCtrl, CListCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/* Handle mouse move					*/
void CCustomListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	/* Check if user is dragging? */
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		/* Get selection item position */
		int nPos = GetSelectionMark();
		/* Begin dragging if current item is not empty */
		if (nPos != -1)
		{
			RECT rClient = { 0 };
			GetClientRect(&rClient);
			ANNOTATION_DATA_t* pData = (ANNOTATION_DATA_t*)GetItemData(nPos);
			if (pData)
			{
				BeginDrag((DWORD)pData->unID, &rClient, &point);
			}
		}
	}
	__super::OnMouseMove(nFlags, point);
}

/* Handle drop							*/
BOOL CCustomListCtrl::OnDrop(CWnd* pWnd, COleDataObject* pDataObj,
		DROPEFFECT dropEffect, CPoint point)
{
	/* Get global memory */
	HGLOBAL hGlobal;
	hGlobal = pDataObj->GetGlobalData(CF_OWNERDISPLAY);
	LPCSTR pData = (LPCSTR)GlobalLock(hGlobal);
	ASSERT(pData != NULL);

	/* Convert to Annotation id	*/
	DWORD nID = (DWORD)atol(pData);
	ANNOTATION_DATA_t* pAnnoData = CAnnotationData::GetSysAnnotationByID(nID);
	ASSERT(pAnnoData != NULL);
	
	/* Get current drop target */
	CRect rect;
	GetWindowRect(rect);
	GetCursorPos(&point);
	ScreenToClient(&point);
	/* Get position of item drop target */
	int nPos = HitTest(point);
	if (nPos != -1)
	{
		/* Get data of drop target */
		ANNOTATION_DATA_t* pDropTarget = (ANNOTATION_DATA_t*)GetItemData(nPos);
		/* Check if drop target is not empty */
		if (pDropTarget)
		{
			CCustomListCtrl::s_nDropTargetID = pDropTarget->unID;
		}
		/* Set new data for drop target */
		SetItemData(nPos, (DWORD_PTR)pAnnoData);
		CString szClass;
		szClass.Format(_T("%d"), pAnnoData->unID);
		SetItemText(nPos, 0, szClass);
		szClass.Format(_T("%d"), pAnnoData->unClassID);
		SetItemText(nPos, 1, szClass);
		SetItemText(nPos, 2, pAnnoData->szKey);
		SetItemText(nPos, 3, pAnnoData->szWord);
	}

	GlobalUnlock(hGlobal);
	return TRUE;
}

/* Handle complete move					*/
void CCustomListCtrl::FinishMove()
{
	/* Get drag source item */
	int nItem = GetSelectionMark();
	if (nItem != -1)
	{
		/* Get data of drag source item */
		ANNOTATION_DATA_t* pSource = (ANNOTATION_DATA_t*)GetItemData(nItem);
		/* Check item is not empty */
		if (pSource)
		{
			/* Drop target is empty */
			if (CCustomListCtrl::s_nDropTargetID == -1)
			{
				/* Move */
				SetItemData(nItem, NULL);
				SetItemText(nItem, 0, _T(""));
				SetItemText(nItem, 1, _T(""));
				SetItemText(nItem, 2, _T(""));
				SetItemText(nItem, 3, _T(""));
			}
			else
			{
				/* Swap */
				ANNOTATION_DATA_t* pAnnoData = CAnnotationData::GetSysAnnotationByID(CCustomListCtrl::s_nDropTargetID);
				SetItemData(nItem, (DWORD_PTR)pAnnoData);
				CString szClass;
				szClass.Format(_T("%d"), pAnnoData->unID);
				SetItemText(nItem, 0, szClass);
				szClass.Format(_T("%d"), pAnnoData->unClassID);
				SetItemText(nItem, 1, szClass);
				SetItemText(nItem, 2, pAnnoData->szKey);
				SetItemText(nItem, 3, pAnnoData->szWord);
				/* Reset drop target */
				CCustomListCtrl::s_nDropTargetID = -1;
			}
		}
		/* Drag source item is empty (maybe drag from another control) */
		else
		{
			/* Reset drop target */
			CCustomListCtrl::s_nDropTargetID = -1;
		}
	}
}
