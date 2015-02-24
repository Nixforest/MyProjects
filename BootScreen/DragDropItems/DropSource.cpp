#include "StdAfx.h"
#include "DropSource.h"


CDropSource::CDropSource(void)
{
}

CDropSource::~CDropSource(void)
{
}

DROPEFFECT CDropSource::StartDragging(DWORD data, RECT* rClient, CPoint* pCursorPos)
{
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 10);
	ASSERT(hGlobal != NULL);

	LPCTSTR szData = (LPCTSTR)GlobalLock(hGlobal);
	ASSERT(szData != NULL);
	ltoa(data, (char*)szData, 10);

	CacheGlobalData(CF_OWNERDISPLAY, hGlobal);
	DROPEFFECT dropEffect = DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, (LPCRECT)rClient);

	if ((dropEffect & DROPEFFECT_MOVE) == DROPEFFECT_MOVE)
	{
		OutputDebugString(_T("CompleteMove\n"));
		CompleteMove();
	}
	LPARAM lParam;
	lParam = pCursorPos->y;
	lParam = lParam<<16;
	lParam &= pCursorPos->x;
	SendMessage(GetActiveWindow(), WM_LBUTTONUP, 0, lParam);
	Empty();
	return dropEffect;
}