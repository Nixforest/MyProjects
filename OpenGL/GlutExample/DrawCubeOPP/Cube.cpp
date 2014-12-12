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
	// Initialize filter flag
	this->m_uMAGFilter = GL_NEAREST;
	this->m_uMINFilter = GL_NEAREST;
	// Initialize filename array
	for (int i = 0; i < FACE_NUM; i++)
	{
		this->m_cTextureArr[i] = NULL;
	}
}
// Destructor
CCube::~CCube()
{
}
// Set filter when load textures of cube
void CCube::SetFilter(GLuint nMAGFilter, GLuint nMINFilter)
{
	this->m_uMAGFilter = nMAGFilter;
	this->m_uMINFilter = nMINFilter;
}
// Load textures of cube's faces
bool CCube::LoadGLTextures()
{
	bool bRet = TRUE;													// Return indicator
	AUX_RGBImageRec	*pTextureImage[FACE_NUM];							// Create Storage Space For The Texture
	memset(pTextureImage, 0, sizeof(void *) * FACE_NUM);				// Set The Pointer To NULL
	glGenTextures(FACE_NUM, &this->m_uTextureArr[0]);					// Generate texture
	for (int i = 0; i < FACE_NUM; i++)
	{
		if (this->m_cTextureArr[i])
		{
			pTextureImage[i] = CUtility::LoadBMP(this->m_cTextureArr[i]);	// Load texture from bitmap
		}		
		if (pTextureImage[i])
		{
			bRet = TRUE;
			glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[i]->sizeX,
				pTextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
				pTextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_uMAGFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_uMINFilter);
		}
		else
		{
			bRet = FALSE;
		}
	}
	for (int i = 0; i < FACE_NUM; i++)
	{
		if (pTextureImage[i])
		{
			if (pTextureImage[i]->data)
			{
				free(pTextureImage[i]->data);
			}
			free(pTextureImage[i]);
		}
	}
	return bRet;
}
// Draw cube
bool CCube::Draw()
{
	glLoadIdentity();									// Reset the current model-view matrix
	glTranslatef(this->m_fPosition[X_AXIS],
		this->m_fPosition[Y_AXIS],
		this->m_fPosition[Z_AXIS]);
	glScalef(this->m_fSize[X_AXIS],
		this->m_fSize[Y_AXIS],
		this->m_fSize[Z_AXIS]);
	// Up face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fA);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fB);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fC);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fD);
	glEnd();
	// Left face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fC);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fB);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fF);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fG);
	glEnd();
	// Right face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fA);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fD);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fH);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fE);
	glEnd();
	// Front face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fD);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fC);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fG);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fH);
	glEnd();
	// Back face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fA);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fE);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fF);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fB);
	glEnd();
	// Bottom face
	glBindTexture(GL_TEXTURE_2D, this->m_uTextureArr[5]);
	glBegin(GL_QUADS);
	 glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(s_fE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(s_fF);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(s_fG);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(s_fH);
	glEnd();
	return TRUE;										// Everything went OK
}
// Set texture filename
void CCube::SetTexture(char * cTextureArr[])
{
	for (int i = 0; i < FACE_NUM; i++)
	{
		this->m_cTextureArr[i] = cTextureArr[i];
	}
}
// Set position of cube
void CCube::SetPosition(GLfloat fX, GLfloat fY, GLfloat fZ)
{
	this->m_fPosition[X_AXIS] = fX;
	this->m_fPosition[Y_AXIS] = fY;
	this->m_fPosition[Z_AXIS] = fZ;
}
// Set size of cube
void CCube::SetSize(GLfloat fWidth, GLfloat fHeight, GLfloat fDeep)
{
	this->m_fSize[X_AXIS] = fWidth;
	this->m_fSize[Y_AXIS] = fHeight;
	this->m_fSize[Z_AXIS] = fDeep;
}