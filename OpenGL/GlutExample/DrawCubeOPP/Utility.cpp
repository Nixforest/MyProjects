#include "Utility.h"
AUX_RGBImageRec* CUtility::LoadBMP(char* pFileName)				// Load a bitmap image
{
	FILE* file = NULL;									// File handle
	if (!pFileName)										// Make sure a file name was given
	{
		return NULL;									// If not return NULL
	}
	fopen_s(&file, pFileName, "r");						// Check to see if the file exists
	if (file)
	{
		fclose(file);									// Close the handle
		return auxDIBImageLoadA(pFileName);				// Load the bitmap and return the pointer
	}
	return NULL;
}