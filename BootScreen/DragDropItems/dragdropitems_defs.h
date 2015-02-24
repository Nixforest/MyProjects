#pragma once
#include <tchar.h>

#define	TOGGLE_BTN_NUM				60
#define	ANNOTATION_DATA_PATH		_T("data.csv")
#define	ANNO_ASSIGN_DATA_PATH		_T("assigndata.csv")
#define LIST_COLUM_CLASS			_T("Class")
#define LIST_COLUM_KEY				_T("Key")
#define LIST_COLUM_WORD				_T("Word")

/* Define struct of annotation data */
typedef struct
{
	unsigned int		unID;
	unsigned short		unClassID;
	_TCHAR*				szKey;
	_TCHAR*				szWord;
}ANNOTATION_DATA_t;