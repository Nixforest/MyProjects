// Cube.h implement file
#include "Cube.h"
// Constructor
CCube::CCube()
{
	// Initialize position of cube is (0, 0, 0)
	this->m_fPosition[X_AXIS] = 0.0f;
	this->m_fPosition[Y_AXIS] = 0.0f;
	this->m_fPosition[Z_AXIS] = 0.0f;
	// Initialize size of cube is (1, 1, 1)
	this->m_fSize[X_AXIS] = 1.0f;
	this->m_fSize[Y_AXIS] = 1.0f;
	this->m_fSize[Z_AXIS] = 1.0f;
}
// Destructor
CCube::~CCube()
{
}