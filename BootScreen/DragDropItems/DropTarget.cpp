#include "StdAfx.h"
#include "DropTarget.h"


CDropTarget::CDropTarget(void)
{
}

CDropTarget::~CDropTarget(void)
{
}

DROPEFFECT CDropTarget::OnDragEnter(CWnd *pWnd, COleDataObject* pDataObj,
		DWORD dwKeyState, CPoint point)
{
	/* Check if hold CTRL */
	if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
	{
		return DROPEFFECT_COPY;
	}
	else
	{
		return DROPEFFECT_MOVE;
	}
}

DROPEFFECT CDropTarget::OnDragOver(CWnd *pWnd, COleDataObject* pDataObj,
		DWORD dwKeyState, CPoint point)
{
	/* Check if hold CTRL */
	if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
	{
		return DROPEFFECT_COPY;
	}
	else
	{
		return DROPEFFECT_MOVE;
	}
}

void CDropTarget::OnDragLeave(CWnd *pWnd)
{
	COleDropTarget::OnDragLeave(pWnd);
}

BOOL CDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObj,
		DROPEFFECT dropEffect, CPoint point)
{
	HGLOBAL		hGlobal;
	LPCTSTR		pData;
	/* Get global data */
	hGlobal = pDataObj->GetGlobalData(CF_OWNERDISPLAY);
	pData = (LPCTSTR)GlobalLock(hGlobal);
	ASSERT(pData != NULL);
	pWnd->SetWindowTextW(pData);
	GlobalUnlock(hGlobal);
	return TRUE;
}
BOOL CDropTarget::Initialize(CWnd* pWnd)
{
	BOOL nRet = Register(pWnd);
	if (nRet)
	{
		/* Register success */
		return TRUE;
	}
	return FALSE;
}