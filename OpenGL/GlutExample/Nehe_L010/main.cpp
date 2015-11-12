#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <SOIL.h>
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
#define		NUMBER_STARS						100							// Number of stars
#define		COLOR_MARK							256							// Color mark when draw color for star
#define		MAXSIZE								15.0f						// Max of circle's size which star move inside
#define		WORLD_FILE_PATH						"data\\world.txt"			// File path of world file
#define		TEXTURE_FILE_PATH					"data\\texture.bmp"			// File path of texture file
#define		STRING_BUFFER						256							// String buffer
#define		LINE_FEED							'\n'						// Line feed character
#define		SLASH								'/'							// Slash character

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
#define		MSG_READFILEFAILED					"Read file world is failed!"

//----------Define error messages----------//
#define		ERR_SHUTDOWN_ERROR					"SHUTDOWN ERROR"
#define		ERR_ERROR							"ERROR"

//----------Define enum	----------//
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

//----------Define structure----------//
// Create A Structure For Star
typedef struct _Star
{
	int		r;					// Stars Color Red
	int		g;					// Stars Color Green
	int		b;					// Stars Color Blue
	GLfloat	fDist;				// Stars Distance From Center
	GLfloat	fAngle;				// Stars Current Angle
}STAR_t;

/* Build our vertex structure */
typedef struct _Vertex
{
	float	fX;					/* 3D coordinates: X value */
	float	fY;					/* 3D coordinates: Y value */
	float	fZ;					/* 3D coordinates: Z value */
	float	fU;					/* Texture coordinates: U value */
	float	fV;					/* Texture coordinates: V value */
	_Vertex()
	{
		this->fX = 0.0f;
		this->fY = 0.0f;
		this->fZ = 0.0f;
		this->fU = 0.0f;
		this->fV = 0.0f;
	}
}Vertex_t;
/* Build our triangle structure */
typedef struct _Triangle
{
	Vertex_t	vertex[3];			// Array Of Three Vertices
}Triangle_t;
/* Build our sector structure */
typedef struct _Sector
{
	UINT		uNumTriAngle;		// Number Of Triangles In Sector
	Triangle_t*	pTriangle;			// Pointer To Array Of Triangles
	_Sector()
	{
		this->uNumTriAngle = 0;
		this->pTriangle = NULL;
	}
}Sector_t;

//----------Global variable----------//
HDC			hDC						= NULL;								// Private GDI Device Context
HGLRC		hRC						= NULL;								// Permanent Rendering Context
HWND		hWnd					= NULL;								// Holds Our Window Handle
HINSTANCE	hInstance;													// Holds the instance of the application

bool		g_bKeysArr[KEYNUMBER];										// Array used for the keyboard routine
bool		g_bActive				= TRUE;								// Window Active flag set to TRUE by default
bool		g_bFullscreen			= TRUE;								// Full screen flag set to Full screen Mode by default
GLfloat		g_MoveX					= 0.5f;								// Move distance by x axis
GLfloat		g_MoveY					= 0.0f;								// Move distance by y axis
GLfloat		g_MoveZ					= 0.0f;							// Move distance by z axis
GLfloat		g_MDeltaX				= 0.05f;							// Move distance step by x axis
GLfloat		g_MDeltaY				= 0.05f;							// Move distance step by y axis
GLfloat		g_MDeltaZ				= 0.20f;							// Move distance step by z axis
GLfloat		g_RotateX				= 0.0f;								// Rotate angle by x axis
GLfloat		g_RotateY				= 0.0f;								// Rotate angle by y axis
GLfloat		g_RotateZ				= 0.0f;								// Rotate angle by z axis
GLfloat		g_RDeltaX				= 1.00f;							// Rotate angle step by x axis
GLfloat		g_RDeltaY				= 2.00f;							// Rotate angle step by y axis
GLfloat		g_RDeltaZ				= 0.001f;							// Rotate angle step by z axis

GLfloat		g_Walkbias				= 0.0f;								// Value use for walk down and up
GLfloat		g_Walkbiasangle			= 0.0f;								// Value use for walk down and up
float		g_Heading				= 0.0f;								// Heading value????
const float	PIOVER180				= 0.0174532925f;					// Value of PI/180 -> Use for convert radians to degrees

GLuint		g_Texture[NUMBER_TEXTURE];									// Textures in program
STAR_t		g_Stars[NUMBER_STARS];										// Stars list
GLuint		g_uLoop					= 0;								// General loop variable
Sector_t	g_Sector;													// Our model sector
GLuint		g_uFilter				= 2;								// Which Filter To Use
BOOL		g_bLight				= FALSE;							// Lighting ON/OFF
BOOL		g_bBlend				= FALSE;							// Blend ON/OFF
BOOL		g_bTwinkle				= FALSE;							// Twinkling Stars ON/OFF
BOOL		g_bLPress				= FALSE;							// L Pressed?
BOOL		g_bFPress				= FALSE;							// F Pressed?
BOOL		g_bBPress				= FALSE;							// B Pressed?
BOOL		g_bTPress				= FALSE;							// T Pressed?
BOOL		g_bPause				= FALSE;							// Pause?
BOOL		g_bPPress				= FALSE;							// P Pressed?
GLfloat		g_LightAmbient[]		= {0.5f, 0.5f, 0.5f, 1.0f};			// Ambient Light values
GLfloat		g_LightDiffuse[]		= {1.0f, 1.0f, 1.0f, 1.0f};			// Diffuse Light values
GLfloat		g_LightPosition[]		= {0.0f, 0.0f, 2.0f, 1.0f};			// Light position

/* Color */
GLfloat		s_RedColor[3]			= {1.0f, 0.0f, 0.0f};				// Red color
GLfloat		s_GreenColor[3]			= {0.0f, 1.0f, 0.0f};				// Green color
GLfloat		s_BlueColor[3]			= {0.0f, 0.0f, 1.0f};				// Blue color
GLfloat		s_WhiteColor[3]			= {1.0f, 1.0f, 1.0f};				// White color
GLfloat		s_YellowColor[3]		= {1.0f, 1.0f, 0.0f};				// Yellow color
GLfloat		s_OrangeColor[3]		= {1.0f, 0.5f, 0.0f};				// Orange color

/* Pointer */
const static	GLfloat		s_fA[3]	= { 1.0f, 1.0f,-1.0f};
const static	GLfloat		s_fB[3]	= {-1.0f, 1.0f,-1.0f};
const static	GLfloat		s_fC[3]	= {-1.0f, 1.0f, 1.0f};
const static	GLfloat		s_fD[3]	= { 1.0f, 1.0f, 1.0f};
const static	GLfloat		s_fE[3]	= { 1.0f,-1.0f,-1.0f};
const static	GLfloat		s_fF[3]	= {-1.0f,-1.0f,-1.0f};
const static	GLfloat		s_fG[3]	= {-1.0f,-1.0f, 1.0f};
const static	GLfloat		s_fH[3]	= { 1.0f,-1.0f, 1.0f};
const static	GLfloat		s_fI[3]	= { 1.0f, 1.0f, 0.0f};
const static	GLfloat		s_fK[3]	= {-1.0f, 1.0f, 0.0f};
const static	GLfloat		s_fL[3]	= {-1.0f,-1.0f, 0.0f};
const static	GLfloat		s_fM[3]	= { 1.0f,-1.0f, 0.0f};
const static	GLfloat		s_fO[3]	= { 0.0f, 1.0f, 0.0f};
const static	GLfloat		s_fCubeNormal[CUBE_NORMAL_NUM][3] = 
{
	{ 0.0f, 0.0f, 1.0f},
	{-1.0f, 0.0f, 0.0f},
	{ 0.0f, 0.0f,-1.0f},
	{ 1.0f, 0.0f, 0.0f},
	{ 0.0f, 1.0f, 0.0f},
	{ 0.0f,-1.0f, 0.0f},
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declare for WndProc

/* Read a string */
void ReadStr(FILE* pFile, char* pString)
{
	do
	{
		fgets(pString, STRING_BUFFER - 1, pFile);		// Read one line
	} while ((pString[0] == SLASH) || (pString[0] == LINE_FEED));	// See If It Is Worthy Of Processing
}

/* Setup our world */
void SetupWorld()
{
	FILE*		pFile			= NULL;							// Pointer of file
	int			nErr			= 0;							// Error code
	UINT		unNumTriAngles	= 0;							// Number Of Triangles In Sector
	char		arrLine[STRING_BUFFER - 1];						// String To Store Data In
	Vertex_t	vertex;

	nErr = fopen_s(&pFile, WORLD_FILE_PATH, "rt");				// Open Our File
	/* Open file is failed */
	if (nErr)
	{
		MessageBox(NULL, MSG_READFILEFAILED,					// Show message open file is failed
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
	}
	else														// Open file is success
	{
		ReadStr(pFile, arrLine);								// Get Single Line Of Data
		sscanf_s(arrLine, "NUMPOLLIES %d\n", &unNumTriAngles);	// Read In Number Of Triangles
		g_Sector.pTriangle = new Triangle_t[unNumTriAngles];	// Allocate Memory For numtriangles And Set Pointer
		g_Sector.uNumTriAngle = unNumTriAngles;					// Define the number of triangles in sector

		// Step through each triangle in sector
		for (UINT ii = 0; ii < unNumTriAngles; ii++)			// Loop through all the triangles
		{
			// Step through each vertex in triangle
			for (UINT jj = 0; jj < 3; jj++)						// Loop through all the vertices
			{
				ReadStr(pFile, arrLine);						// Read string to work with
				sscanf_s(arrLine, "%f %f %f %f %f",				// Read data into respective vertex values
					&vertex.fX, &vertex.fY, &vertex.fZ, &vertex.fU, &vertex.fV);
				g_Sector.pTriangle[ii].vertex[jj] = vertex;		// Store values into respective vertices
			}
		}
		fclose(pFile);											// Close file after done
	}
}

/* Load a bitmap image */
int LoadGLTextures()
{
	int nStatus = TRUE;									// Status Indicator

	char* arrFileName[NUMBER_TEXTURE] =
	{
		TEXTURE_FILE_PATH,
	};
	//glGenTextures(3, &g_Texture[0]);
	// Create Nearest Filtered Texture
	g_Texture[0] = SOIL_load_OGL_texture(arrFileName[0],
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (!g_Texture[0])
	{
		nStatus = FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, g_Texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Create Linear Filtered Texture
	g_Texture[1] = SOIL_load_OGL_texture(arrFileName[0],
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (!g_Texture[1])
	{
		nStatus = FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, g_Texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Create MipMapped Texture
	g_Texture[2] = SOIL_load_OGL_texture(arrFileName[0],
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (!g_Texture[2])
	{
		nStatus = FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, g_Texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return nStatus;                                        // Return Success
}

/* Resize and initialize the GL Window */
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
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

int InitGL(GLvoid)										// All setup for openGL goes here
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency Based On Source Alpha Value
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black background
	glClearDepth(1.0f);									// Depth buffer setup
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	//glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calcutations
	
	//glLightfv(GL_LIGHT1, GL_AMBIENT, g_LightAmbient);	// Setup the ambient light
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, g_LightDiffuse);	// Setup the diffuse light
	//glLightfv(GL_LIGHT1, GL_POSITION, g_LightPosition);	// Position the light
	//glEnable(GL_LIGHT1);								// Enable light one

	//glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
	//glEnable(GL_BLEND);									// Enable blending
	SetupWorld();

	return TRUE;										// Initialization went OK
}
// Draw a triangle
void DrawTriAngles(Vertex_t vertex1, Vertex_t vertex2, Vertex_t vertex3)
{
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(vertex1.fU, vertex1.fV);
		glVertex3f(vertex1.fX, vertex1.fY, vertex1.fZ);
		glTexCoord2f(vertex2.fU, vertex2.fV);
		glVertex3f(vertex2.fX, vertex2.fY, vertex2.fZ);
		glTexCoord2f(vertex3.fU, vertex3.fV);
		glVertex3f(vertex3.fX, vertex3.fY, vertex3.fZ);
	}
	glEnd();
}
void DrawQuads(const GLfloat* d1, const GLfloat* d2,
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
int DrawGLScene(GLvoid)									// Here's where we do all the drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
	glLoadIdentity();									// Reset current matrix
	GLfloat fYTrans		= -g_Walkbias - 0.25f;				// Used For Bouncing Motion Up And Down
	GLfloat fSceneRotY	= 360.0f - g_RotateY;			// 360 Degree Angle For Player Direction

	glRotatef(g_RotateX, 1.0f, 0.0f, 0.0f);				// Rotate Up And Down To Look Up And Down
	glRotatef(fSceneRotY, 0.0f, 1.0f, 0.0f);			// Rotate Depending On Direction Player Is Facing
	glTranslatef(-g_MoveX, fYTrans, -g_MoveZ);			// Translate The Scene Based On Player Position
	glBindTexture(GL_TEXTURE_2D, g_Texture[g_uFilter]);	// Select Our Texture

	// Process each triangle
	for (UINT ii = 0; ii < g_Sector.uNumTriAngle; ii++)	// Loop Through All The Triangles
	{
		DrawTriAngles(g_Sector.pTriangle[ii].vertex[0],
			g_Sector.pTriangle[ii].vertex[1],
			g_Sector.pTriangle[ii].vertex[2]);
	}
	return TRUE;										// Everything went OK
}

GLvoid KillGLWindow(GLvoid)								// Properly kill the window
{
	// Release memory
	if (g_Sector.pTriangle)
	{
		delete[] g_Sector.pTriangle;
		g_Sector.pTriangle = NULL;
		g_Sector.uNumTriAngle = 0;
	}
	if (g_bFullscreen)									// Are we in fullscreen mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If so switch back to the desktop
		ShowCursor(TRUE);								// Show mouse pointer
	}
	if (hRC)											// Do we have a rendering context
	{
		if (!wglMakeCurrent(NULL, NULL))				// Are we able to release the DC and RC contexts?
		{
			MessageBox(NULL, MSG_RELEASEDCRCFAILED,
				ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))						// Are we able to delete the RC?
		{
			MessageBox(NULL, MSG_RELEASERCFAILED,
				ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC to NULL
	}
	if (hDC && !ReleaseDC(hWnd, hDC))					// Are we able to release the DC
	{
		MessageBox(NULL, MSG_RELEASEDCFAILED,
			ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC to NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, MSG_RELEASEHWNDFAILED,
			ERR_SHUTDOWN_ERROR, MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
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
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullScreenFlag)
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
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended style for the window
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
	if (!(hDC = GetDC(hWnd)))										// Did we get a device context
	{
		KillGLWindow();												// Reset the display
		MessageBox(NULL, MSG_CREATEGLDCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))				// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_FINDPIXELFORMATFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))					// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_SETPIXELFORMATFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))								// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_CREATEGLRCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))									// Try To Activate The Rendering Context
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, MSG_ACTIVEGLRCFAILED,
			ERR_ERROR, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);										// Show The Window
	SetForegroundWindow(hWnd);										// Slightly Higher Priority
	SetFocus(hWnd);													// Sets Keyboard Focus To The Window
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

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
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
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
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
					if (true)
					{

					}
					if (!g_bPause)
					{
						DrawGLScene();						// Draw The Scene
						SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
					}
					
					/*--- Handle 'L' key ---*/
					if (g_bKeysArr['L'] && !g_bLPress)	// L key being pressed not held?
					{
						g_bLPress = TRUE;				// Become TRUE
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
					if (!g_bKeysArr['L'])				// Has L key been released?
					{
						g_bLPress = FALSE;				// If so, become FALSE
					}
					/*--- Handle 'F' key ---*/
					if (g_bKeysArr['F'] && !g_bFPress)	// Is F key being pressed not held?
					{
						g_bFPress = TRUE;
						g_uFilter += 1;
						if (g_uFilter >= NUMBER_FILTER)
						{
							g_uFilter = 0;
						}
					}
					if (!g_bKeysArr['F'])
					{
						g_bFPress = FALSE;
					}
					/*--- Handle 'B' key ---*/
					if (g_bKeysArr['B'] && !g_bBPress)
					{
						g_bBPress = TRUE;
						g_bBlend = !g_bBlend;
						if (g_bBlend)
						{
							glEnable(GL_BLEND);
							glDisable(GL_DEPTH_TEST);
						}
						else
						{
							glDisable(GL_BLEND);
							glEnable(GL_DEPTH_TEST);
						}
					}
					if (!g_bKeysArr['B'])
					{
						g_bBPress = FALSE;
					}
					/*--- Handle 'T' key ---*/
					if (g_bKeysArr['T'] && !g_bTPress)
					{
						g_bTPress = TRUE;
						g_bTwinkle = !g_bTwinkle;
					}
					if (!g_bKeysArr['T'])
					{
						g_bTPress = FALSE;
					}
					/*--- Handle 'P' key ---*/
					if (g_bKeysArr['P'] && !g_bPPress)
					{
						g_bPPress = TRUE;
						g_bPause = !g_bPause;
					}
					if (!g_bKeysArr['P'])
					{
						g_bPPress = FALSE;
					}
				}
			}

			if (g_bKeysArr[VK_F1])						// Is F1 Being Pressed?
			{
				g_bKeysArr[VK_F1] = FALSE;				// If So Make Key FALSE
				KillGLWindow();							// Kill Our Current Window
				g_bFullscreen = !g_bFullscreen;			// Toggle Full screen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT, g_bFullscreen))
				{
					return 0;							// Quit If Window Was Not Created
				}
			}
			
			// Handle move left-right
			if (g_bKeysArr[VK_LEFT])
			{
				g_bKeysArr[VK_LEFT] = FALSE;
				//g_Heading -= g_MDeltaX;
				g_MoveX -= g_MDeltaX;
			}
			if (g_bKeysArr[VK_RIGHT])
			{
				g_bKeysArr[VK_RIGHT] = FALSE;
				//g_Heading += g_MDeltaX;
				g_MoveX += g_MDeltaX;
			}
			// Handle move up-down
			if (g_bKeysArr[VK_UP])
			{
				g_bKeysArr[VK_UP] = FALSE;
				g_MoveX -= (float)sin(g_Heading * PIOVER180) * 0.05f;
				g_MoveZ -= (float)cos(g_Heading * PIOVER180) * 0.05f;
				if (g_Walkbiasangle >= 359.0f)
				{
					g_Walkbiasangle = 0.0f;
				}
				else
				{
					g_Walkbiasangle += 10.0f;
				}
				g_Walkbias = (float)sin(g_Walkbiasangle * PIOVER180) / 20.0f;
			}
			if (g_bKeysArr[VK_DOWN])
			{
				g_bKeysArr[VK_DOWN] = FALSE;
				g_MoveX += (float)sin(g_Heading * PIOVER180) * 0.05f;
				g_MoveZ += (float)cos(g_Heading * PIOVER180) * 0.05f;
				if (g_Walkbiasangle <= 1.0f)
				{
					g_Walkbiasangle = 359.0f;
				}
				else
				{
					g_Walkbiasangle -= 10.0f;
				}
				g_Walkbias = (float)sin(g_Walkbiasangle * PIOVER180) / 20.0f;
			}
			// Handle move forward-backward
			if (g_bKeysArr[VK_ADD])
			{
				g_bKeysArr[VK_ADD] = FALSE;
				g_MoveZ -= g_MDeltaZ;
			}
			// Handle rotate follow X asix
			if (g_bKeysArr[VK_INSERT])
			{
				g_bKeysArr[VK_INSERT] = FALSE;
				g_Heading += g_RDeltaY;
				g_RotateY = g_Heading;
			}
			if (g_bKeysArr[VK_DELETE])
			{
				g_bKeysArr[VK_DELETE] = FALSE;
				g_RotateX -= g_RDeltaX;
			}
			// Handle rotate follow Y asix
			if (g_bKeysArr[VK_HOME])
			{
				g_bKeysArr[VK_HOME] = FALSE;
				g_RotateX += g_RDeltaX;
			}
			if (g_bKeysArr[VK_END])
			{
				g_bKeysArr[VK_END] = FALSE;
				g_RotateX -= g_RDeltaX;
			}
			// Handle rotate follow Z axis
			if (g_bKeysArr[VK_PRIOR])
			{
				g_bKeysArr[VK_PRIOR] = FALSE;
				g_Heading -= g_RDeltaY;
				g_RotateY = g_Heading;
				//g_MoveZ -= 0.02f;
			}
			if (g_bKeysArr[VK_NEXT])
			{
				g_bKeysArr[VK_NEXT] = FALSE;
				g_RotateZ -= g_RDeltaZ;
				//g_MoveZ += 0.02f;
			}
			if (g_bKeysArr[VK_SUBTRACT])
			{
				g_bKeysArr[VK_SUBTRACT] = FALSE;
				g_MoveZ += g_MDeltaZ;
			}

			if (g_bKeysArr[VK_TAB])
			{
				g_bKeysArr[VK_TAB] = FALSE;
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}