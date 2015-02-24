#include "stdafx.h"
#include "CustomBtn.h"


CCustomBtn::CCustomBtn()
{
	//this->SetButtonStyle(BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_TABSTOP);
	m_nAnnotationID = -1;
}


CCustomBtn::~CCustomBtn()
{
}
int	CCustomBtn::GetAnnotationID()
{
	return m_nAnnotationID;
}
void CCustomBtn::SetAnnotationID(int id)
{
	m_nAnnotationID = id;
}