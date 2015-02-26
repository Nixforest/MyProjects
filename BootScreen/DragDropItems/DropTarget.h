#pragma once
#include "afxole.h"

/* Drop target object */
class CDropTarget :
	protected COleDropTarget
{
public:
	CDropTarget(void);																							/* Constructor	*/
	virtual ~CDropTarget(void);																					/* Destructor	*/
	virtual DROPEFFECT	OnDragEnter(CWnd *pWnd, COleDataObject* pDataObj, DWORD dwKeyState, CPoint point);		/* OnDragEnter	*/
	virtual DROPEFFECT	OnDragOver(CWnd *pWnd, COleDataObject* pDataObj, DWORD dwKeyState, CPoint point);		/* OnDragOver	*/
	virtual void		OnDragLeave(CWnd *pWnd);																/* OnDragLeave	*/
	virtual BOOL		OnDrop(CWnd* pWnd, COleDataObject* pDataObj, DROPEFFECT dropEffect, CPoint point);		/* OnDrop		*/
	BOOL				Initialize(CWnd* pWnd);																	/* Initialize	*/
};

