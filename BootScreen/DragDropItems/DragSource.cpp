#include "stdafx.h"
#include "DragSource.h"

/* Constructor */
CDragSource::CDragSource(void)
{
}

/* Destructor */
CDragSource::~CDragSource(void)
{
}

/* Handle start dragging */
DROPEFFECT CDragSource::BeginDrag(DWORD dwData, RECT* rClient, CPoint* pCursorPos)
{
	/* Init global handle */
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, DATASOURCE_BUFFER);
	ASSERT(hGlobal != NULL);

	/* Create global data */
	LPCTSTR szData = (LPCTSTR)GlobalLock(hGlobal);
	ASSERT(szData != NULL);
	_ltoa_s(dwData, (char*)szData, DATASOURCE_BUFFER, DATASOURCE_BUFFER);

	/* Set global data */
	CacheGlobalData(CF_OWNERDISPLAY, hGlobal);

	/* Drag and drop */
	DROPEFFECT dropEffect = DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, (LPCRECT)rClient);

	if (dropEffect == DROPEFFECT_MOVE)
	{
		FinishMove();
	}
	LPARAM lParam;
	lParam = pCursorPos->y;
	lParam = lParam << 16;
	lParam &= pCursorPos->x;
	SendMessage(GetActiveWindow(), WM_LBUTTONUP, 0, lParam);
	Empty();

	return dropEffect;
}
