#pragma once
#include "afxwin.h"
#include "DragSource.h"
#include "dragdropitems_defs.h"
#include "AnnotationData.h"


class CCustomListBox :
	public CListBox, public CDragSource
{
public:
	CCustomListBox();										/* Constructor				*/
	virtual ~CCustomListBox();								/* Destructor				*/
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	/* Handle mouse move		*/
};

