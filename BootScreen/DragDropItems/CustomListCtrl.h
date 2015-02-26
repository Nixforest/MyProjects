#pragma once
#include "afxcmn.h"
#include "DropTarget.h"
#include "DragSource.h"
#include "dragdropitems_defs.h"
#include "AnnotationData.h"

class CCustomListCtrl :
	public CListCtrl, public CDropTarget, public CDragSource
{
public:
	CCustomListCtrl(void);											/* Constructor							*/
	virtual ~CCustomListCtrl(void);									/* Destructor							*/
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObj,		/* Handle drop							*/
		DROPEFFECT dropEffect, CPoint point);
protected:
	virtual void FinishMove();										/* Handle complete move					*/
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);			/* Handle mouse move					*/
private:
	static int	s_nDropTargetID;									/* Annotation identify of drop target	*/
};

