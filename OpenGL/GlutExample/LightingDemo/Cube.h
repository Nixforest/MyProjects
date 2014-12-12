#ifndef CUBE_H
#define CUBE_H
#include "gl\gl.h"
#define		X_AXIS		0		// x axis index
#define		Y_AXIS		1		// y axis index
#define		Z_AXIS		2		// z axis index
class CCube
{
private:
	GLfloat m_fPosition[3];		// Position of Front-Top-Left corner of cube
	GLfloat m_fSize[3];			// Size width, height and deep of cube
public:
	CCube();					// Constructor
	~CCube();					// Destructor

};
#endif /* CUBE_H */