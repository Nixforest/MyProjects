#pragma once
#include "afxwin.h"
class CCustomBtn :
	public CButton
{
public:
	CCustomBtn();
	~CCustomBtn();
	int		GetAnnotationID();
	void	SetAnnotationID(int id);
private:
	int		m_nAnnotationID;
};

