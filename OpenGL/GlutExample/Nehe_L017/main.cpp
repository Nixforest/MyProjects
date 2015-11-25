#include <windows.h>
#include <stdio.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <gl\GLAUX.H>
#pragma comment(linker, "/subsystem:\"windows\"")


//----------Defines constant----------//
#define		KEYNUMBER							256							// Number of keys input
#define		DEFAULT_PERSPECTIVE_FOVY			45.0f						// Default perspective fovy
#define		CLASSNAME							"OpenGL"					// Class name
#define		DEPTHBUFFER							16							// Depth buffer
#define		ARTIST_NAME							"Nixforest"					// Artist name
#define		WINDOW_TITLE						"NeHe's OpenGL Framework"	// Window title
#define		WINDOW_WIDTH						640							// Window width
#define		WINDOW_HEIGHT						480							// Window hight
#define		WINDOW_BIT							16							// Window bit
#define		NUMBER_TEXTURE						1							// Number of textures
#define		NUMBER_FILTER						3							// Number of filters

//----------Define messages----------//
#define		MSG_RELEASEDCRCFAILED				"Release Of DC And RC Failed."
#define		MSG_RELEASERCFAILED					"Release Rendering Context Failed."
#define		MSG_RELEASEDCFAILED					"Release Device Context Failed."
#define		MSG_RELEASEHWNDFAILED				"Could Not Release hWnd."
#define		MSG_UNREGISTERCLASSFAILED			"Could not unregister class."
#define		MSG_REGISTERCLASSFAILED				"Failed To Register The Window Class."
#define		MSG_FULLSCREENNOTSUPPORT			"The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?"
#define		MSG_PROGRAMNOTCLOSE					"Program will not close."
#define		MSG_CREATEWINDOWFAILED				"Window Creation Error."
#define		MSG_CREATEGLDCFAILED				"Can't create a GL device context."
#define		MSG_FINDPIXELFORMATFAILED			"Can't Find A Suitable PixelFormat."
#define		MSG_SETPIXELFORMATFAILED			"Can't Set The PixelFormat."
#define		MSG_CREATEGLRCFAILED				"Can't Create A GL Rendering Context."
#define		MSG_ACTIVEGLRCFAILED				"Can't Activate The GL Rendering Context."
#define		MSG_INITFAILED						"Initialization Failed."
#define		MSG_RUNINFULLSCREEN					"Would You Like To Run In Fullscreen Mode?"
#define		MSG_STARTFULLSCREEN					"Start FullScreen?"

//----------Define error messages----------//
#define		ERR_SHUTDOWN_ERROR					"SHUTDOWN ERROR"
#define		ERR_ERROR							"ERROR"

//----------Define enum	----------//
/* Normal of cube sides */
typedef enum CUBE_NORMAL
{
	CUBE_NORMAL_FRONT = 0,
	CUBE_NORMAL_LEFT,
	CUBE_NORMAL_BEHIND,
	CUBE_NORMAL_RIGHT,
	CUBE_NORMAL_TOP,
	CUBE_NORMAL_BOTTOM,
	CUBE_NORMAL_NUM
};
/* Color enum */
typedef enum COLOR
{
	RED = 0,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
	ORANGE,
	GREY,
	COLOR_NUM
};
/* Type of key on keyboard */
typedef enum KEYTYPE
{
	NORMAL = 0,									/* Normal type, can press	*/
	TOGGLE,										/* Turn on and turn off		*/
	KEYTYPE_NUM									/* Number of tyoe of key	*/
};

//----------Define structure----------//
typedef struct _Keyboard
{
	GLuint		uType;							/* Type of key on keyboard			*/
	GLvoid		(*KeyboardFunc)(GLvoid);		/* Function handle when press key	*/
	_Keyboard()									/* Constructor						*/
	{
		this->uType = NORMAL;					/* Default type is normal			*/
		this->KeyboardFunc = NULL;				/* Default handle is NULL			*/
	}
}KEYBOARD_t;

//----------Global variable----------//
HDC				g_hDC						= NULL;								// Private GDI Device Context
HGLRC			g_hRC						= NULL;								// Permanent Rendering Context
HWND			g_hWnd						= NULL;								// Holds Our Window Handle
HINSTANCE		hInstance;														// Holds the instance of the application

bool			g_bKeysArr[KEYNUMBER];											// Array used for the keyboard routine
bool			g_bKeyPress[KEYNUMBER];											// Array used for check the keyboard is pressed
KEYBOARD_t		g_KeyData[KEYNUMBER];											// Array used for check the keyboard data
bool			g_bActive					= TRUE;								// Window Active flag set to TRUE by default
bool			g_bFullscreen				= TRUE;								// Full screen flag set to Full screen Mode by default
GLfloat			g_MoveX						= 0.5f;								// Move distance by x axis
GLfloat			g_MoveY						= 0.0f;								// Move distance by y axis
GLfloat			g_MoveZ						= -5.0f;							// Move distance by z axis
GLfloat			g_MDeltaX					= 0.05f;							// Move distance step by x axis
GLfloat			g_MDeltaY					= 0.05f;							// Move distance step by y axis
GLfloat			g_MDeltaZ					= 0.05f;							// Move distance step by z axis
GLfloat			g_RotateX					= 0.0f;								// Rotate angle by x axis
GLfloat			g_RotateY					= 0.0f;								// Rotate angle by y axis
GLfloat			g_RotateZ					= 0.0f;								// Rotate angle by z axis
GLfloat			g_RDeltaX					= 0.05f;							// Rotate angle step by x axis
GLfloat			g_RDeltaY					= 0.05f;							// Rotate angle step by y axis
GLfloat			g_RDeltaZ					= 0.05f;							// Rotate angle step by z axis
GLuint			g_Texture[NUMBER_TEXTURE];										// Textures in program

GLuint			g_uFilter					= 0;								// Which Filter To Use
GLuint			g_uFogFilter				= 0;								// Which Fog To Use
GLuint			g_uFogColor					= GREY;								// Which Fog color to use
BOOL			g_bLight					= FALSE;							// Lighting ON/OFF
BOOL			g_bPause					= FALSE;							// Pause?
GLfloat			g_LightAmbient[]			= {0.5f, 0.5f, 0.5f, 1.0f};			// Ambient Light values
GLfloat			g_LightDiffuse[]			= {1.0f, 1.0f, 1.0f, 1.0f};			// Diffuse Light values
GLfloat			g_LightPosition[]			= {0.0f, 0.0f, 2.0f, 1.0f};			// Light position

/* Color */
GLfloat			s_RedColor[3]				= {1.0f, 0.0f, 0.0f};				// Red color
GLfloat			s_GreenColor[3]				= {0.0f, 1.0f, 0.0f};				// Green color
GLfloat			s_BlueColor[3]				= {0.0f, 0.0f, 1.0f};				// Blue color
GLfloat			s_WhiteColor[3]				= {1.0f, 1.0f, 1.0f};				// White color
GLfloat			s_YellowColor[3]			= {1.0f, 1.0f, 0.0f};				// Yellow color
GLfloat			s_OrangeColor[3]			= {1.0f, 0.5f, 0.0f};				// Orange color

/* Pointer */
const static	GLfloat						s_fA[3]	= { 1.0f, 1.0f,-1.0f};
const static	GLfloat						s_fB[3]	= {-1.0f, 1.0f,-1.0f};
const static	GLfloat						s_fC[3]	= {-1.0f, 1.0f, 1.0f};
const static	GLfloat						s_fD[3]	= { 1.0f, 1.0f, 1.0f};
const static	GLfloat						s_fE[3]	= { 1.0f,-1.0f,-1.0f};
const static	GLfloat						s_fF[3]	= {-1.0f,-1.0f,-1.0f};
const static	GLfloat						s_fG[3]	= {-1.0f,-1.0f, 1.0f};
const static	GLfloat						s_fH[3]	= { 1.0f,-1.0f, 1.0f};
const static	GLfloat						s_fI[3]	= { 1.0f, 1.0f, 0.0f};
const static	GLfloat						s_fK[3]	= {-1.0f, 1.0f, 0.0f};
const static	GLfloat						s_fL[3]	= {-1.0f,-1.0f, 0.0f};
const static	GLfloat						s_fM[3]	= { 1.0f,-1.0f, 0.0f};
const static	GLfloat						s_fO[3]	= { 0.0f, 1.0f, 0.0f};
const static	GLfloat						s_fFogColor[COLOR_NUM][4] =
{
	{s_RedColor[0],		s_RedColor[1],		s_RedColor[2],		1.0f},
	{s_GreenColor[0],	s_GreenColor[1],	s_GreenColor[2],	1.0f},
	{s_BlueColor[0],	s_BlueColor[1],		s_BlueColor[2],		1.0f},
	{s_WhiteColor[0],	s_WhiteColor[1],	s_WhiteColor[2],	1.0f},
	{s_YellowColor[0],	s_YellowColor[1],	s_YellowColor[2],	1.0f},
	{s_OrangeColor[0],	s_OrangeColor[1],	s_OrangeColor[2],	1.0f},
	{0.5,				0.5,				0.5,				1.0f},
};
const static	GLfloat						s_fCubeNormal[CUBE_NORMAL_NUM][3] = 
{
	{ 0.0f, 0.0f, 1.0f},
	{-1.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f,-1.0f},
	{ 1.0f, 0.0f, 0.0f},
	{ 0.0f, 1.0f, 0.0f},
	{ 0.0f,-1.0f, 0.0f},
};
const static	GLuint						s_FogMode[] =								// Storage For Three Types Of Fog
{
	GL_EXP,
	GL_EXP2,
	GL_LINEAR
};

/* ----- Define prototypes ----- */
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// Declare for WndProc
GLvoid				KillGLWindow(GLvoid);
BOOL				CreateGLWindow(char* title, int width, int height, int bits, bool fullScreenFlag);
GLvoid				ProcessKeyboard();
GLvoid				OnPressP(GLvoid);
GLvoid				OnPressL(GLvoid);
GLvoid				OnPressF(GLvoid);
GLvoid				OnPressF1(GLvoid);
GLvoid				OnPressLEFT(GLvoid);
GLvoid				OnPressRIGHT(GLvoid);
GLvoid				OnPressUP(GLvoid);
GLvoid				OnPressDOWN(GLvoid);
GLvoid				OnPressINSERT(GLvoid);
GLvoid				OnPressDELETE(GLvoid);
GLvoid				OnPressHOME(GLvoid);
GLvoid				OnPressEND(GLvoid);
GLvoid				OnPressPRIOR(GLvoid);
GLvoid				OnPressNEXT(GLvoid);
AUX_RGBImageRec*	LoadBMP(char* pFileName);
int					LoadGLTextures();
GLvoid				ReSizeGLScene(GLsizei width, GLsizei height);
int					InitGL(GLvoid);
void				DrawTriAngles(const GLfloat* d1, const GLfloat* d2, const GLfloat* d3,
						const GLfloat* c1, const GLfloat* c2, const GLfloat* c3);
void				DrawQuads(const GLfloat* d1, const GLfloat* d2,
						const GLfloat* d3, const GLfloat* d4, const GLfloat* color);
int					DrawGLScene(GLvoid);
/* Load a bitmap image */
AUX_RGBImageRec*	LoadBMP(char* pFileName)				// Load a bitmap image
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
		return auxDIBImageLoad(pFileName);				// Load the bitmap and return the pointer
	}
	return NULL;
}
int					LoadGLTextures()
{
	int nStatus = TRUE;									// Status Indicator

	AUX_RGBImageRec *pTextureImage[1];                   // Create Storage Space For The Texture
	memset(pTextureImage, 0 ,sizeof(void *)*1);                // Set The Pointer To NULL
	if (pTextureImage[0] = LoadBMP("data\\Crate.bmp"))
	{
		nStatus = TRUE;
		glGenTextures(3, &g_Texture[0]);
		// Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, g_Texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX,
			pTextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
			pTextureImage[0]->data);
		
		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, g_Texture[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX,
			pTextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
			pTextureImage[0]->data);

		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, g_Texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pTextureImage[0]->sizeX,
			pTextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
			pTextureImage[0]->data);
	}
	if (pTextureImage[0])
	{
		if (pTextureImage[0]->data)
		{
			free(pTextureImage[0]->data);
		}
		free(pTextureImage[0]);
	}
	return nStatus;                                        // Return Success
}
/* Resize and initialize the GL Window */
GLvoid				ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)									// Prevent a divide by zero by
	{													// making height equal one
		height = 1;
	}
	glViewport(0, 0, width, height);					// Reset the current view-port
	glMatrixMode(GL_PROJECTION);						// Select the projection matrix
	glLoadIdentity();									// Reset the projection matrix

	// Calculate the aspect ration of the window
	gluPerspective(DEFAULT_PERSPECTIVE_FOVY, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);							// Select the model-view matrix
	glLoadIdentity();									// Reset the model-view matrix
}
int					InitGL(GLvoid)										// All setup for openGL goes here
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black background
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);				// Black background
	glClearDepth(1.0f);									// Depth buffer setup
	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calcutations
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, g_LightAmbient);	// Setup the ambient light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, g_LightDiffuse);	// Setup the diffuse light
	glLightfv(GL_LIGHT1, GL_POSITION, g_LightPosition);	// Position the light
	glEnable(GL_LIGHT1);								// Enable light one


	glFogi(GL_FOG_MODE, s_FogMode[g_uFogFilter]);		// Fog mode
	glFogfv(GL_FOG_COLOR, s_fFogColor[g_uFogColor]);	// Set fog color
	glFogf(GL_FOG_DENSITY, 0.35f);						// How dense will the fog be
	glHint(GL_FOG_HINT, GL_DONT_CARE);					// Fog hint value
	glFogf(GL_FOG_START, 1.0f);							// Fog start depth
	glFogf(GL_FOG_END, 5.0f);							// Fog end depth
	glEnable(GL_FOG);									// Enables GL_FOG

	/* Handle keyboard */
	ProcessKeyboard();
	return TRUE;										// Initialization went OK
}
// Draw a triangle
void				DrawTriAngles(const GLfloat* d1, const GLfloat* d2, const GLfloat* d3,	// Point 
	const GLfloat* c1, const GLfloat* c2, const GLfloat* c3)				// Color
{
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
	{
		glColor3fv(c1);
		glVertex3fv(d1);
		glColor3fv(c2);
		glVertex3fv(d2);
		glColor3fv(c3);
		glVertex3fv(d3);
	}
	glEnd();
}
void				DrawQuads(const GLfloat* d1, const GLfloat* d2,
	const GLfloat* d3, const GLfloat* d4, const GLfloat* color)
{
	//glColor3fv(color);
	glBegin(GL_QUADS);									// Draw A Quad
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(d1);								// Top Left
		glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(d2);								// Top Right
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(d3);								// Bottom Right
		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(d4);								// Bottom Left
	}
	glEnd();											// Done Drawing The Quad
}
int					DrawGLScene(GLvoid)									// Here's where we do all the drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
	/* Start draw cube */
	glLoadIdentity();
	glTranslatef(g_MoveX, g_MoveY, g_MoveZ);			// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(g_RotateX, 1.0f, 0.0f, 0.0f);				// Rotate The Triangle On The X axis
	glRotatef(g_RotateY, 0.0f, 1.0f, 0.0f);             // Rotate The Triangle On The Y axis
	glRotatef(g_RotateZ, 0.0f, 0.0f, 1.0f);             // Rotate The Triangle On The Z axis
	glBindTexture(GL_TEXTURE_2D, g_Texture[g_uFilter]);
	// Front
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_FRONT]);
	DrawQuads(s_fG, s_fH, s_fD, s_fC, s_GreenColor);
	// Left
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_LEFT]);
	DrawQuads(s_fF, s_fG, s_fC, s_fB, s_OrangeColor);
	// Behind
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_BEHIND]);
	DrawQuads(s_fE, s_fF, s_fB, s_fA, s_RedColor);
	// Right
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_RIGHT]);
	DrawQuads(s_fH, s_fE, s_fA, s_fD, s_YellowColor);
	// Top
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_TOP]);
	DrawQuads(s_fC, s_fD, s_fA, s_fB, s_BlueColor);
	// Bottom
	glNormal3fv(s_fCubeNormal[CUBE_NORMAL_BOTTOM]);
	DrawQuads(s_fF, s_fE, s_fH, s_fG, s_WhiteColor);

	g_RotateX += g_RDeltaX;
	g_RotateY -= g_RDeltaY;
	g_RotateZ += g_RDeltaZ;
	return TRUE;										// Everything went OK
}
GLvoid				ProcessKeyboard()
{
	ZeroMemory(g_bKeyPress, KEYNUMBER);						/* Initialize keypress array				*/
	g_KeyData['P'].uType				= TOGGLE;			/* P key is toggle: Pause ON/OFF			*/
	g_KeyData['P'].KeyboardFunc			= &OnPressP;		/* Function handle of 'P' key				*/
	g_KeyData['L'].uType				= TOGGLE;			/* L key is toggle: light ON/OFF			*/
	g_KeyData['L'].KeyboardFunc			= &OnPressL;		/* Function handle of 'L' key				*/
	g_KeyData['F'].uType				= NORMAL;			/* F key is toggle: Change filter			*/
	g_KeyData['F'].KeyboardFunc			= &OnPressF;		/* Function handle of 'F' key				*/
	g_KeyData[VK_F1].uType				= NORMAL;			/* F1 key is normal: change to fullscreen	*/
	g_KeyData[VK_F1].KeyboardFunc		= &OnPressF1;		/* Function handle of 'F1' key				*/
	g_KeyData[VK_LEFT].uType			= NORMAL;			/* LEFT key is normal:						*/
	g_KeyData[VK_LEFT].KeyboardFunc		= &OnPressLEFT;		/* Function handle of 'LEFT' key			*/
	g_KeyData[VK_RIGHT].uType			= NORMAL;			/* RIGHT key is normal:						*/
	g_KeyData[VK_RIGHT].KeyboardFunc	= &OnPressRIGHT;	/* Function handle of 'RIGHT' key			*/
	g_KeyData[VK_UP].uType				= NORMAL;			/* UP key is normal:						*/
	g_KeyData[VK_UP].KeyboardFunc		= &OnPressUP;		/* Function handle of 'UP' key				*/
	g_KeyData[VK_DOWN].uType			= NORMAL;			/* DOWN key is normal:						*/
	g_KeyData[VK_DOWN].KeyboardFunc		= &OnPressDOWN;		/* Function handle of 'DOWN' key			*/
	g_KeyData[VK_INSERT].uType			= NORMAL;			/* INSERT key is normal:					*/
	g_KeyData[VK_INSERT].KeyboardFunc	= &OnPressINSERT;	/* Function handle of 'INSERT' key			*/
	g_KeyData[VK_DELETE].uType			= NORMAL;			/* DELETE key is normal:					*/
	g_KeyData[VK_DELETE].KeyboardFunc	= &OnPressDELETE;	/* Function handle of 'DELETE' key			*/
	g_KeyData[VK_HOME].uType			= NORMAL;			/* HOME key is normal:						*/
	g_KeyData[VK_HOME].KeyboardFunc		= &OnPressHOME;		/* Function handle of 'HOME' key			*/
	g_KeyData[VK_END].uType				= NORMAL;			/* END key is normal:						*/
	g_KeyData[VK_END].KeyboardFunc		= &OnPressEND;		/* Function handle of 'END' key				*/
	g_KeyData[VK_PRIOR].uType			= NORMAL;			/* PRIOR key is normal:						*/
	g_KeyData[VK_PRIOR].KeyboardFunc	= &OnPressPRIOR;	/* Function handle of 'PRIOR' key			*/
	g_KeyData[VK_NEXT].uType			= NORMAL;			/* NEXT key is normal:						*/
	g_KeyData[VK_NEXT].KeyboardFunc		= &OnPressNEXT;		/* Function handle of 'NEXT' key			*/
}
/* Handle when press 'P' */
GLvoid				OnPressP(GLvoid)
{
	g_bPause = !g_bPause;			/* Turn ON/OFF pause status */
}
/* Handle when press 'F1' */
GLvoid				OnPressF1(GLvoid)
{
	KillGLWindow();							// Kill Our Current Window
	g_bFullscreen = !g_bFullscreen;			// Toggle Full screen / Windowed Mode
	// Recreate Our OpenGL Window
	if (!CreateGLWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT, g_bFullscreen))
	{
		return;								// Quit If Window Was Not Created
	}
}
/* Handle when press 'L' */
GLvoid				OnPressL(GLvoid)
{
	g_bLight = !g_bLight;			// Toggle light TRUE/FALSE
	if (!g_bLight)
	{
		glDisable(GL_LIGHTING);		// Disable lighting
	}
	else
	{
		glEnable(GL_LIGHTING);		// Enable lighting
	}
}
/* Handle when press 'F' */
GLvoid				OnPressF(GLvoid)
{
	g_uFilter++;						/* Change filter selection	*/
	if (g_uFilter >= NUMBER_FILTER)		/* Greater than max			*/
	{
		g_uFilter = 0;					/* Set to zero				*/
	}
}
/* Handle when press 'LEFT' */
GLvoid				OnPressLEFT(GLvoid)
{
	g_MoveX -= g_MDeltaX;
}
/* Handle when press 'RIGHT' */
GLvoid				OnPressRIGHT(GLvoid)
{
	g_MoveX += g_MDeltaX;
}
/* Handle when press 'UP' */
GLvoid				OnPressUP(GLvoid)
{
	g_MoveY += g_MDeltaY;
}
/* Handle when press 'DOWN' */
GLvoid				OnPressDOWN(GLvoid)
{
	g_MoveY -= g_MDeltaY;
}
/* Handle when press 'INSERT' */
GLvoid				OnPressINSERT(GLvoid)
{
	g_RotateX += g_RDeltaX;
}
/* Handle when press 'DELETE' */
GLvoid				OnPressDELETE(GLvoid)
{
	g_RotateX -= g_RDeltaX;
}
/* Handle when press 'HOME' */
GLvoid				OnPressHOME(GLvoid)
{
	g_RotateY += g_RDeltaY;
}
/* Handle when press 'END' */
GLvoid				OnPressEND(GLvoid)
{
	g_RotateY -= g_RDeltaY;
}
/* Handle when press 'PRIOR' */
GLvoid				OnPressPRIOR(GLvoid)
{
	g_RotateZ += g_RDeltaZ;
}
/* Handle when press 'NEXT' */
GLvoid				OnPressNEXT(GLvoid)
{
	g_RotateZ -= g_RDeltaZ;
}
GLvoid				KillGLWindow(GLvoid)								// Properly kill the window
{
	if (g_bFullscreen)									// Are we in fullscreen mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If so switch back to the desktop
		ShowCursor(TRUE);								// Show mouse pointer
	}
	if (g_hRC)											// Do we have a rendering context
	{
		if (!wglMakeCurrent(NULL, NULL))				// Are we able to release the DC and RC contexts?
		{
			MessageBox(NULL, MSG_RELEASEDCRCFAILED,
				ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(g_hRC))					// Are we able to delete the RC?
		{
			MessageBox(NULL, MSG_RELEASERCFAILED,
				ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		}
		g_hRC = NULL;									// Set RC to NULL
	}
	if (g_hDC && !ReleaseDC(g_hWnd, g_hDC))				// Are we able to release the DC
	{
		MessageBox(NULL, MSG_RELEASEDCFAILED,
			ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		g_hDC = NULL;									// Set DC to NULL
	}

	if (g_hWnd && !DestroyWindow(g_hWnd))				// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, MSG_RELEASEHWNDFAILED,
			ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		g_hWnd = NULL;									// Set g_hWnd To NULL
	}

	if (!UnregisterClass(CLASSNAME, hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, MSG_UNREGISTERCLASSFAILED,
			ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;								// Set hInstance to NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Full screen Mode			*
*	height			- Height Of The GL Window Or Full screen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Full screen Mode (TRUE) Or Windowed Mode (FALSE)	*/
BOOL				CreateGLWindow(char* title, int width, int height, int bits, bool fullScreenFlag)
{
	GLuint		PixelFormat;				// Holds the results after searching for a match
	WNDCLASS	wc;							// Windows class structure
	DWORD		dwExStyle;					// Window extended style
	DWORD		dwStyle;					// Window style
	RECT		WindowRect;					// Grabs rectangle upper left/lower right values
	WindowRect.left = (long)0;				// Set left value to 0
	WindowRect.right = (long)width;			// Set right value to requested width
	WindowRect.top = (long)0;				// Set top value to 0
	WindowRect.bottom = (long)height;		// Set bottom value to requested height

	g_bFullscreen = fullScreenFlag;			// Set the global full screen flag

	hInstance = GetModuleHandle(NULL);								// Grab an instance for out window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;					// Redraw on size, and own DC for window
	wc.lpfnWndProc = (WNDPROC)WndProc;								// WndProc handles messages
	wc.cbClsExtra = 0;												// No extra window data
	wc.cbWndExtra = 0;												// No extra window data
	wc.hInstance = hInstance;										// Set the instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);							// Load the default icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);						// Load the arrow pointer
	wc.hbrBackground = NULL;										// No background required for GL
	wc.lpszMenuName = NULL;											// We don't want a menu
	wc.lpszClassName = CLASSNAME;									// Set the class name

	if (!RegisterClass(&wc))										// Attempt to register the window class
	{
		MessageBox(NULL, MSG_REGISTERCLASSFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}
	if (g_bFullscreen)
	{
		DEVMODE dmScreenSettings;									// Device mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));		// Makes sure memory's cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Size of the devmode structure
		dmScreenSettings.dmPelsWidth = width;						// Selected screen width
		dmScreenSettings.dmPelsHeight = height;						// Selected screen height
		dmScreenSettings.dmBitsPerPel = bits;						// Selected bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// Try to set selected mode and get results. NOTE: CDS_FULLSCREEN gets rid of start bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If the mode failed, offer two options. Quit or use windowed mode.
			if (MessageBox(NULL, MSG_FULLSCREENNOTSUPPORT,
				ARTIST_NAME, MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				g_bFullscreen = FALSE;								// Windowed mode selected. Fullscreen = FALSE
			}
			else
			{
				// Pop up a message box letting user know the program is closing.
				MessageBox(NULL, MSG_PROGRAMNOTCLOSE,
					ERR_ERROR, MB_OK | MB_ICONSTOP);
				return FALSE;					// Return FALSE
			}
		}
	}
	if (g_bFullscreen)												// Are we still in fullscreen mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window extended style
		dwStyle = WS_POPUP;											// Windows Style
		ShowCursor(FALSE);											// Hide mouse pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;				// Windows Extended style
		dwStyle = WS_OVERLAPPEDWINDOW;								// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust window to true requested size
	// Create the window
	if (!(g_hWnd = CreateWindowEx(dwExStyle,						// Extended style for the window
		CLASSNAME,													// Class name
		title,														// Window title
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,				// Defined window style
		0, 0,														// Window position
		WindowRect.right - WindowRect.left,							// Calculate window width
		WindowRect.bottom - WindowRect.top,							// Calculate window height
		NULL,														// No parent window
		NULL,														// No menu
		hInstance,													// Instance
		NULL)))														// Don't pass anything to WM_CREATE
	{
		KillGLWindow();												// Reset the display
		MessageBox(NULL, MSG_CREATEWINDOWFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}
	static PIXELFORMATDESCRIPTOR pfd =								// pfd tells widows how we want things to be
	{
		sizeof(PIXELFORMATDESCRIPTOR),								// Size of this pixel format descriptor
		1,															// Version number
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	// Format must support window/opengl/double buffering
		PFD_TYPE_RGBA,												// Request an RGBA format
		bits,														// Select our color depth
		0, 0, 0, 0, 0, 0,											// Color bits ignored
		0,															// No Alpha buffer
		0,															// Shift bit ignored
		0,															// No accumulation buffer
		0, 0, 0, 0,													// Accumulation bits ignored
		DEPTHBUFFER,												// 16bit z-buffer (depth buffer)
		0,															// No stencil buffer
		0,															// No auxiliary buffer
		PFD_MAIN_PLANE,												// Main drawing layer
		0,															// Reserved
		0, 0, 0														// Layer masks ignored
	};
	if (!(g_hDC = GetDC(g_hWnd)))									// Did we get a device context
	{
		KillGLWindow();												// Reset the display
		MessageBox(NULL, MSG_CREATEGLDCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}
	if (!(PixelFormat = ChoosePixelFormat(g_hDC, &pfd)))			// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_FINDPIXELFORMATFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!SetPixelFormat(g_hDC, PixelFormat, &pfd))					// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_SETPIXELFORMATFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!(g_hRC = wglCreateContext(g_hDC)))							// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_CREATEGLRCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!wglMakeCurrent(g_hDC, g_hRC))								// Try To Activate The Rendering Context
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_ACTIVEGLRCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	ShowWindow(g_hWnd, SW_SHOW);									// Show The Window
	SetForegroundWindow(g_hWnd);									// Slightly Higher Priority
	SetFocus(g_hWnd);												// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);									// Set Up Our Perspective GL Screen

	if (!InitGL())													// Initialize Our Newly Created GL Window
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_INITFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK	WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				g_bActive = TRUE;					// Program Is Active
			}
			else
			{
				g_bActive = FALSE;					// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			g_bKeysArr[wParam] = TRUE;				// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			g_bKeysArr[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		default: break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(
	_In_		HINSTANCE	hInstance,				// Instance
	_In_opt_	HINSTANCE	hPrevInstance,			// Previous Instance
	_In_		LPSTR		lpCmdLine,				// Command Line Parameters
	_In_		int			nCmdShow)				// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	bDone = FALSE;							// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL, MSG_RUNINFULLSCREEN,
		MSG_STARTFULLSCREEN, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		g_bFullscreen = FALSE;						// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow(WINDOW_TITLE, WINDOW_WIDTH,
		WINDOW_HEIGHT, WINDOW_BIT, g_bFullscreen))
	{
		return 0;										// Quit If Window Was Not Created
	}

	while (!bDone)										// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)					// Have We Received A Quit Message?
			{
				bDone = TRUE;							// If So done=TRUE
			}
			else										// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);					// Translate The Message
				DispatchMessage(&msg);					// Dispatch The Message
			}
		}
		else											// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (g_bActive)								// Program Active?
			{
				if (g_bKeysArr[VK_ESCAPE])				// Was ESC Pressed?
				{
					bDone = TRUE;						// ESC Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					if (!g_bPause)						// Was programe is paused?
					{
						DrawGLScene();					// Draw The Scene
						SwapBuffers(g_hDC);				// Swap Buffers (Double Buffering)
					}
				}
			}
			/* Loop through all keyboard */
			for (GLuint i = 0; i < KEYNUMBER; i++)
			{
				if (g_bKeysArr[i])									/* Is key i being pressed?				*/
				{
					switch (g_KeyData[i].uType)						/* Switch type of key					*/
					{
					case NORMAL:									/* Normal key							*/
						g_bKeysArr[i] = FALSE;						/* If So Make Key FALSE					*/
						if (NULL != g_KeyData[i].KeyboardFunc)		/* Check if function handle is not NULL	*/
						{
							g_KeyData[i].KeyboardFunc();			/* Execute function handle				*/
						}
						break;
					case TOGGLE:									/* ON/OFF key							*/
						if (!g_bKeyPress[i])						/* Key is not pressed yet				*/
						{
							g_bKeyPress[i] = TRUE;						/* Become TRUE							*/
							if (NULL != g_KeyData[i].KeyboardFunc)	/* Check if function handle is not NULL	*/
							{
								g_KeyData[i].KeyboardFunc();		/* Execute function handle				*/
							}
						}
						break;
					default:
						break;
					}
				}
				else												/* Has i key been released?				*/
				{
					switch (g_KeyData[i].uType)						/* Switch type of key					*/
					{
					case NORMAL:									/* Normal key							*/
						break;
					case TOGGLE:									/* ON/OFF key							*/
						g_bKeyPress[i] = FALSE;						/* Key has released						*/
						break;
					default:
						break;
					}
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}