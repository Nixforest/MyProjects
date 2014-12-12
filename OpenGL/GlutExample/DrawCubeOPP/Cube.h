#ifndef CUBE_H
#define CUBE_H
#include "gl\gl.h"
#include "Utility.h"
#define		X_AXIS		0									// x axis index
#define		Y_AXIS		1									// y axis index
#define		Z_AXIS		2									// z axis index
#define		FACE_NUM	6									// Number of faces in a cube
// Cube vertexes
//     B_____________A
//    /|            /|
//   / |           / |
//  /  |          /  |
// C___|_________D   |
// |   |         |   |
// |   F_________|___E
// |  /          |  /
// | /           | /
// |/            |/
// G_____________H

const static	GLfloat		s_fA[3]		= { 0.5f, 0.5f,-0.5f};
const static	GLfloat		s_fB[3]		= {-0.5f, 0.5f,-0.5f};
const static	GLfloat		s_fC[3]		= {-0.5f, 0.5f, 0.5f};
const static	GLfloat		s_fD[3]		= { 0.5f, 0.5f, 0.5f};
const static	GLfloat		s_fE[3]		= { 0.5f,-0.5f,-0.5f};
const static	GLfloat		s_fF[3]		= {-0.5f,-0.5f,-0.5f};
const static	GLfloat		s_fG[3]		= {-0.5f,-0.5f, 0.5f};
const static	GLfloat		s_fH[3]		= { 0.5f,-0.5f, 0.5f};
class CCube
{
private:
	GLfloat m_fPosition[3];									// Position of cube
	GLfloat m_fSize[3];										// Size width, height and deep of cube
	GLuint	m_uTextureArr[FACE_NUM];						// Textures of all faces in cube
	GLuint	m_uMAGFilter;									// MAG Filter of texture
	GLuint	m_uMINFilter;									// MIN Filter of texture
	char*	m_cTextureArr[FACE_NUM];						// Array of filename texture
public:
	CCube();												// Constructor
	~CCube();												// Destructor
	void SetFilter(GLuint nMAGFilter, GLuint nMinFilter);	// Set filter when load textures of cube
	bool LoadGLTextures();									// Load textures of cube's faces
	bool Draw();											// Draw cube
	void SetTexture(char * cTextureArr[]);					// Set texture filename
	void SetPosition(GLfloat fX, GLfloat fY, GLfloat fZ);	// Set position of cube
	void SetSize(GLfloat fWidth,							// Set size of cube
		GLfloat fHeight, GLfloat fDeep);
};
#endif /* CUBE_H */