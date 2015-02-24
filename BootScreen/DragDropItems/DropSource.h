#pragma once
#include "afxole.h"
class CDropSource :
	protected COleDataSource
{
public:
	CDropSource(void);
	virtual ~CDropSource(void);
	virtual DROPEFFECT StartDragging(DWORD data, RECT* rClient, CPoint* pCursorPos);
protected:
	virtual void CompleteMove() {};
};

