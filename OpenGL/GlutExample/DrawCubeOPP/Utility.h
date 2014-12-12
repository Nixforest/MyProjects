#ifndef UTILITY_H
#define UTILITY_H
#include <stdio.h>
#include "gl\glaux.h"
class CUtility
{
public:
	static AUX_RGBImageRec *LoadBMP(char* pFileName);
};
#endif /* UTILITY_H */