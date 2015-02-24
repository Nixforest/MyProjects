#include "stdafx.h"
#include "AnnotationData.h"

/* Read data from data.csv file */
CAnnotationData::CAnnotationData()
{
	ReadSystemData();
	ReadPresetData();
}

void CAnnotationData::ReadSystemData()
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
		m_arrSystemData = new ANNOTATION_DATA_t[m_unNumberOfRecord];
		for (unsigned int i = 0; i < m_unNumberOfRecord; i++)
		{
			int nTokenPos = 0;
			/* Get index */
			CString strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				m_arrSystemData[i].unID = _ttoi(strToken);
			}
			/* Get class */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				m_arrSystemData[i].unClassID = _ttoi(strToken);
			}
			/* Get key */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				m_arrSystemData[i].szKey = (_TCHAR*)malloc(sizeof(_TCHAR)*(strToken.GetLength() + 1));
				_tcscpy_s(m_arrSystemData[i].szKey, strToken.GetLength() + 1, strToken);
			}
			/* Get word */
			strToken = arrLines.GetAt(i).Tokenize(_T(","), nTokenPos);
			if (!strToken.IsEmpty())
			{
				m_arrSystemData[i].szWord = (_TCHAR*)malloc(sizeof(_TCHAR)*(strToken.GetLength() + 1));
				_tcscpy_s(m_arrSystemData[i].szWord, strToken.GetLength() + 1, strToken);
			}
		}
	}
}

void CAnnotationData::ReadPresetData()
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

CAnnotationData::~CAnnotationData()
{
	/* Free annotation data */
	if (m_arrSystemData)
	{
		for (unsigned int i = 0; i < m_unNumberOfRecord; i++)
		{
			free(m_arrSystemData[i].szKey);
			free(m_arrSystemData[i].szWord);
		}
		delete[] m_arrSystemData;
	}
}

ANNOTATION_DATA_t*	CAnnotationData::GetAnnotationByID(int unID)
{
	ANNOTATION_DATA_t* pRet = NULL;
	if (unID >= 0)
	{
		pRet = &m_arrSystemData[unID];
	}
	return pRet;
}
int CAnnotationData::GetIdByPosition(int unPos)
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
void CAnnotationData::SetIdByPosition(int unPos, int unID)
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