#include "stdafx.h"
#include "CustomBtn.h"

/* Init static variable */
int CCustomBtn::s_nDropTargetID = -1;

/* Constructor */
CCustomBtn::CCustomBtn()
{
	m_nAnnotationID = -1;
}

/* Destructor */
CCustomBtn::~CCustomBtn()
{
}

/* Get Annotation identify				*/
int	CCustomBtn::GetAnnotationID()
{
	return m_nAnnotationID;
}

/* Set Annotation identify				*/
void CCustomBtn::SetAnnotationID(int id)
{
	m_nAnnotationID = id;
}

BEGIN_MESSAGE_MAP(CCustomBtn, CButton)
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/* Handle complete move					*/
void CCustomBtn::FinishMove()
{
	/* It is not empty button */
	if (m_nAnnotationID != -1)
	{
		/* Drop target it empty button */
		if (CCustomBtn::s_nDropTargetID == -1)
		{
			/* Move */
			m_nAnnotationID = -1;
			this->SetWindowTextW(_T(""));
		}
		else
		{
			/* Swap */
			m_nAnnotationID = CCustomBtn::s_nDropTargetID;
			this->SetWindowTextW(CAnnotationData::GetSysAnnotationByID(m_nAnnotationID)->szKey);
			/* Reset drop target */
			CCustomBtn::s_nDropTargetID = -1;
		}
	}
}

/* Handle drop							*/
BOOL CCustomBtn::OnDrop(CWnd* pWnd, COleDataObject* pDataObj,
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
	CCustomBtn::s_nDropTargetID = m_nAnnotationID;

	/* Set new value for drop target */
	m_nAnnotationID = nID;
	this->SetWindowTextW(pAnnoData->szKey);

	GlobalUnlock(hGlobal);
	return TRUE;
}

/* Handle mouse move					*/
void CCustomBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	/* Check if user is dragging? */
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		RECT rClient = {0};
		GetClientRect(&rClient);
		/* Begin dragging if current button is not empty */
		if (m_nAnnotationID != -1)
		{
			BeginDrag((DWORD)m_nAnnotationID, &rClient, &point);
		}
	}
	__super::OnMouseMove(nFlags, point);
}
