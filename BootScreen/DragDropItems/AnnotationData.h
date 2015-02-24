#pragma once
#include "dragdropitems_defs.h"
class CAnnotationData
{
private:
	ANNOTATION_DATA_t*			m_arrSystemData;
	unsigned int				m_unNumberOfRecord;
	int							m_arrPresetData[TOGGLE_BTN_NUM];
public:
	CAnnotationData();
	~CAnnotationData();
	ANNOTATION_DATA_t*	GetAnnotationByID(int unID);
	void				ReadSystemData();
	void				ReadPresetData();
	int					GetIdByPosition(int unPos);
	void				SetIdByPosition(int unPos, int unID);
};

