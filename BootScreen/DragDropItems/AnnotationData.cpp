#include "stdafx.h"
#include "AnnotationData.h"

/* Initial static variable */
ANNOTATION_DATA_t*	CAnnotationData::s_arrSystemData = NULL;

/* Read data from data.csv file */
CAnnotationData::CAnnotationData()
{
	/* Read System annotations */
	ReadSysAnnotationData();
	/* Read Preset annotations */
	ReadPreAnnotationData();
}

/* Read System annotations */
void CAnnotationData::ReadSysAnnotationData()
{
	CArray<CString> arrLines;
	CString	strLine;
	TRY
	{
		/* Read annotation data file */
		CStdioFile file(ANNOTATION_DATA_PATH, CFile::modeRead);
		/* Add all lines into arrLines variable */
		while (file.ReadString(strLine))
		{
			arrLines.Add(strLine);
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL

	if (arrLines.GetCount())
	{
		m_unNumberOfRecord = arrLines.GetCount();
		/* Get data success */
		s_arrSystemData = new ANNOTATION_DATA_t[m_unNumberOfRecord];
		for (unsigned int i = 0; i < m_unNumberOfRecord; i++)
		{
			int nTokenPos = 0;
			/* Get index */
			CString strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				s_arrSystemData[i].unID = _ttoi(strToken);
			}
			/* Get class */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				s_arrSystemData[i].unClassID = _ttoi(strToken);
			}
			/* Get key */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				s_arrSystemData[i].szKey = (_TCHAR*)malloc(sizeof(_TCHAR)*(strToken.GetLength() + 1));
				_tcscpy_s(s_arrSystemData[i].szKey, strToken.GetLength() + 1, strToken);
			}
			/* Get word */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				s_arrSystemData[i].szWord = (_TCHAR*)malloc(sizeof(_TCHAR)*(strToken.GetLength() + 1));
				_tcscpy_s(s_arrSystemData[i].szWord, strToken.GetLength() + 1, strToken);
			}
		}
	}
}

/* Read Preset annotations */
void CAnnotationData::ReadPreAnnotationData()
{
	CString	strLine;
	TRY
	{
		/* Read annotation data file */
		CStdioFile file(ANNO_ASSIGN_DATA_PATH, CFile::modeRead);
		int i = 0;
		/* Add all lines into arrLines variable */
		while (file.ReadString(strLine))
		{
			m_arrPresetData[i++] = _ttoi(strLine);
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL
}

/* Write Preset annotations to file */
void CAnnotationData::WritePreAnnotationData()
{
	CString	strLine;
	TRY
	{
		/* Read annotation data file */
		CStdioFile file(ANNO_ASSIGN_DATA_PATH, CFile::modeWrite);
		int i = 0;
		/* Add all lines into arrLines variable */
		for (int i = 0; i < TOGGLE_BTN_NUM; i++)
		{
			strLine.Format(_T("%d\n"), m_arrPresetData[i]);
			file.WriteString(strLine);
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL
}

CAnnotationData::~CAnnotationData()
{
	/* Free annotation data */
	if (s_arrSystemData)
	{
		for (unsigned int i = 0; i < m_unNumberOfRecord; i++)
		{
			/* Delete Key string */
			free(s_arrSystemData[i].szKey);
			/* Delete Word string */
			free(s_arrSystemData[i].szWord);
		}
		delete[] s_arrSystemData;
	}
}

/* Get system annotation from id		*/
ANNOTATION_DATA_t*	CAnnotationData::GetSysAnnotationByID(int unID)
{
	ANNOTATION_DATA_t* pRet = NULL;
	if (unID >= 0)
	{
		pRet = &s_arrSystemData[unID];
	}
	return pRet;
}

/* Get Annotation id from position in preset */
int CAnnotationData::GetAnnoIdByPos(int unPos)
{
	if (unPos >= 0)
	{
		return m_arrPresetData[unPos];
	}
	else
	{
		return -1;
	}
}

/* Set Annotation id to position in preset	 */
void CAnnotationData::SetAnnoIdByPos(int unPos, int unID)
{
	if (unPos >= 0)
	{
		m_arrPresetData[unPos] = unID;
	}
	else
	{
		m_arrPresetData[unPos] = -1;
	}
}

/* Get number of System annotations		*/
unsigned int CAnnotationData::GetSysAnnotationNum()
{
	return m_unNumberOfRecord;
}