#include "stdafx.h"
#include "CustomListBox.h"

/* Constructor */
CCustomListBox::CCustomListBox()
{
}

/* Destructor */
CCustomListBox::~CCustomListBox()
{
}
BEGIN_MESSAGE_MAP(CCustomListBox, CListBox)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/* Handle mouse move					*/
void CCustomListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	/* Check if user is dragging? */
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		/* Get current selection */
		int nPos = GetCurSel();
		if (nPos == LB_ERR)
		{
			return;
		}
		RECT rClient;
		GetClientRect(&rClient);
		ANNOTATION_DATA_t* pData = (ANNOTATION_DATA_t*)GetItemDataPtr(nPos);
		/* Begin dragging */
		BeginDrag((DWORD)pData->unID, &rClient, &point);
	}
	__super::OnMouseMove(nFlags, point);
}