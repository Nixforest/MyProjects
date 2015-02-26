#pragma once
#include "afxole.h"
#include "dragdropitems_defs.h"

/* Drag source object */
class CDragSource :
	protected COleDataSource
{
public:
	CDragSource(void);																	/* Constructor				*/
	virtual ~CDragSource(void);															/* Destructor				*/
	virtual DROPEFFECT BeginDrag(DWORD dwData, RECT* rClient, CPoint* pCursorPos);		/* Handle begin drag object	*/
protected:
	virtual void FinishMove() {};														/* Handle when drop object	*/
};

