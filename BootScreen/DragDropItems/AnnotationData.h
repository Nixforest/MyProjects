#pragma once
#include "dragdropitems_defs.h"
class CAnnotationData
{
private:
	static ANNOTATION_DATA_t*	s_arrSystemData;					/* List System annotations				*/
	unsigned int				m_unNumberOfRecord;					/* Number of System annotations			*/
	int							m_arrPresetData[TOGGLE_BTN_NUM];	/* List assigned annotations (keep id of system annotation)	*/
public:
	CAnnotationData();												/* Constructor							*/
	~CAnnotationData();												/* Destructor							*/
	static ANNOTATION_DATA_t*	GetSysAnnotationByID(int unID);		/* Get system annotation from id		*/
	void				ReadSysAnnotationData();					/* Read System annotations form file	*/
	void				ReadPreAnnotationData();					/* Read Preset annotations form file	*/
	void				WritePreAnnotationData();					/* Write Preset annotations to file		*/
	int					GetAnnoIdByPos(int unPos);					/* Get Annotation id from position in preset */
	void				SetAnnoIdByPos(int unPos, int unID);		/* Set Annotation id to position in preset	 */
	unsigned int		GetSysAnnotationNum();						/* Get number of System annotations		*/
};

