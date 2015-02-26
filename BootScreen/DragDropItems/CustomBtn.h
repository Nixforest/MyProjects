#pragma once
#include "afxwin.h"
#include "DropTarget.h"
#include "DragSource.h"
#include "dragdropitems_defs.h"
#include "AnnotationData.h"

class CCustomBtn :
	public CButton, public CDropTarget, public CDragSource
{
public:
	CCustomBtn();													/* Constructor							*/
	virtual ~CCustomBtn();											/* Destructor							*/
	int		GetAnnotationID();										/* Get Annotation identify				*/
	void	SetAnnotationID(int id);								/* Set Annotation identify				*/
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObj,		/* Handle drop							*/
		DROPEFFECT dropEffect, CPoint point);
protected:
	virtual void FinishMove();										/* Handle complete move					*/
private:
	int			m_nAnnotationID;									/* Annotation identify					*/
	static int	s_nDropTargetID;									/* Annotation identify of drop target	*/
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);			/* Handle mouse move					*/
};

