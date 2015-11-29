/*=======================================================================================
*	Copyright (c) Nixforest Corporation. 2015 All rights reserved.
*
* File Discription:
*	main entry
*
* Note:
*	None
*
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <gl\GLAUX.H>
#include "general_defs.h"
#include "general_prot.h"
#pragma comment(linker, "/subsystem:\"windows\"")

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
GLuint			g_uBase						= 0;								// Base Display List For The Font
GLfloat			g_fCnt1						= 0.0f;								// Temp variable
GLfloat			g_fCnt2						= 0.0f;								// Temp variable

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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Window procedure
* Parameter:
*	[Inputs]
*		HWND	hWnd:			Handle For This Window
*		UINT	uMsg:			Message For This Window
*		WPARAM	wParam:			Additional Message Information
*		LPARAM	lParam:			Additional Message Information
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
LRESULT CALLBACK	WndProc(HWND	hWnd,			// Handle For This Window
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Create window
* Parameter:
*	[Inputs]
*		char* 	title:				Title To Appear At The Top Of The Window
*		int 	width:				Width Of The GL Window Or Full screen Mode
*		int 	height:				Height Of The GL Window Or Full screen Mode
*		int 	bits:				Number Of Bits To Use For Color (8/16/24/32)
*		bool 	fullScreenFlag:		Use Full screen Mode (TRUE) Or Windowed Mode (FALSE)
*  [Output]
*		None
* Return Value:
*	Return TRUE if create window success, FALSE otherwise
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Resize and initialize the GL Window
* Parameter:
*	[Inputs]
*		GLsizei 	width:				Width Of The GL Window to resize
*		GLsizei 	height:				Height Of The GL Window to resize
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	All setup for openGL goes here
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	Return TRUE if init window success, FALSE otherwise
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
int					InitGL(GLvoid)
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	BuildFont();										// Build The Font

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black background
	glClearDepth(1.0f);									// Depth buffer setup
	//glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Select The Type Of Blending
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calcutations
	
	//glLightfv(GL_LIGHT1, GL_AMBIENT, g_LightAmbient);	// Setup the ambient light
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, g_LightDiffuse);	// Setup the diffuse light
	//glLightfv(GL_LIGHT1, GL_POSITION, g_LightPosition);	// Position the light
	//glEnable(GL_LIGHT1);								// Enable light one


	//glFogi(GL_FOG_MODE, s_FogMode[g_uFogFilter]);		// Fog mode
	//glFogfv(GL_FOG_COLOR, s_fFogColor[g_uFogColor]);	// Set fog color
	//glFogf(GL_FOG_DENSITY, 0.35f);						// How dense will the fog be
	//glHint(GL_FOG_HINT, GL_DONT_CARE);					// Fog hint value
	//glFogf(GL_FOG_START, 1.0f);							// Fog start depth
	//glFogf(GL_FOG_END, 5.0f);							// Fog end depth
	//glEnable(GL_FOG);									// Enables GL_FOG

	/* Handle keyboard */
	ProcessKeyboard();
	return TRUE;										// Initialization went OK
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Here's where we do all the drawing
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	Return TRUE if draw window success, FALSE otherwise
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
int					DrawGLScene(GLvoid)
{
	GLfloat	pFirstVertext[2]	= {-1.0f, 1.0f };
	GLfloat	pSecondVertext[2]	= { 1.0f, 1.0f };
	GLfloat	pThirdVertext[2]	= { 1.0f,-1.0f };
	GLfloat	pFourthVertext[2]	= {-1.0f,-1.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
	glLoadIdentity();									// Reset The Modelview Matrix
	glBindTexture(GL_TEXTURE_2D, g_Texture[1]);
	glTranslatef(0.0f, 0.0f, -5.5f);					// Move Into The Screen 5 Units
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);					// Rotate The Triangle On The Z axis
	glRotatef(g_fCnt1 * 30.0f, 1.0f, 1.0f, 0.0f);		// Rotate On The X & Y Axis By cnt1 (Left To Right)
	glDisable(GL_BLEND);								// Disable Blending Before We Draw In 3D
	DrawQuads2fv(pFirstVertext, pSecondVertext,			// Draw Our First Texture Mapped Quad
		pThirdVertext, pFourthVertext, s_WhiteColor);
	glRotatef(90.0f, 1.0f, 1.0f, 0.0f);					// Rotate On The X & Y Axis By 90 Degrees (Left To Right)
	DrawQuads2fv(pFirstVertext, pSecondVertext,			// Draw Our Second Texture Mapped Quad
		pThirdVertext, pFourthVertext, s_WhiteColor);

	glEnable(GL_BLEND);									// Enable Blending
	glLoadIdentity();									// Reset The View

	glColor3f(1.0f * float(cos(g_fCnt1)),				// Pulsing Colors Based On Text Position
		1.0f * float(sin(g_fCnt2)),
		1.0f - 0.5f * float(cos(g_fCnt1 + g_fCnt2)));
	glPrint(int((280 + 250 * cos(g_fCnt1))),			// Print GL Text To The Screen
		int(235 + 200 * sin(g_fCnt2)), "glPrint1", 0);
	glColor3f(1.0f * float(sin(g_fCnt2)),				// Pulsing Colors Based On Text Position
		1.0f - 0.5f * float(cos(g_fCnt1 + g_fCnt2)),
		1.0f * float(cos(g_fCnt1)));
	glPrint(int((280 + 230*cos(g_fCnt2))),				// Print GL Text To The Screen
		int(235 + 200 * sin(g_fCnt1)), "glPrint2", 1);
	glColor3fv(s_BlueColor);							// Set Color To Blue
	glPrint(											// Draw Text To The Screen
		int(240 + 200 * cos((g_fCnt2 + g_fCnt1) / 5)),
		2,
		"glPrint3",
		0);
	glColor3fv(s_WhiteColor);							// Set color to white
	glPrint(											// Draw Offset Text To The Screen
		int(242 + 200 * cos((g_fCnt2 + g_fCnt1) / 5)),
		2,
		"glPrint4",
		0);
	
	g_fCnt1 += 0.005f;
	g_fCnt2 += 0.0040f;

	//g_RotateX += g_RDeltaX;
	//g_RotateY -= g_RDeltaY;
	//g_RotateZ += g_RDeltaZ;
	return TRUE;										// Everything went OK
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Properly kill the window
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				KillGLWindow(GLvoid)								// 
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Assign type of key and function handle when press key
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'P'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressP(GLvoid)
{
	g_bPause = !g_bPause;			/* Turn ON/OFF pause status */
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'L'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'F'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressF(GLvoid)
{
	g_uFilter++;						/* Change filter selection	*/
	if (g_uFilter >= NUMBER_FILTER)		/* Greater than max			*/
	{
		g_uFilter = 0;					/* Set to zero				*/
	}
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'F1'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'LEFT'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressLEFT(GLvoid)
{
	g_MoveX -= g_MDeltaX;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'RIGHT'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressRIGHT(GLvoid)
{
	g_MoveX += g_MDeltaX;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'UP'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressUP(GLvoid)
{
	g_MoveY += g_MDeltaY;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'DOWN'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressDOWN(GLvoid)
{
	g_MoveY -= g_MDeltaY;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'INSERT'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressINSERT(GLvoid)
{
	g_RotateX += g_RDeltaX;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'DELETE'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressDELETE(GLvoid)
{
	g_RotateX -= g_RDeltaX;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'HOME'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressHOME(GLvoid)
{
	g_RotateY += g_RDeltaY;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'END'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressEND(GLvoid)
{
	g_RotateY -= g_RDeltaY;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'PRIOR'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressPRIOR(GLvoid)
{
	g_RotateZ += g_RDeltaZ;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Handle when press 'NEXT'
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				OnPressNEXT(GLvoid)
{
	g_RotateZ -= g_RDeltaZ;
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Load a bitmap image
* Parameter:
*	[Inputs]
*		char*	pFileName:		Bitmap file name
*  [Output]
*		None
* Return Value:
*	Pointer to bitmap file
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Load all textures
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	Return TRUE if load textures success, FALSE otherwise
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
int					LoadGLTextures()
{
	int nStatus = TRUE;											// Status Indicator

	AUX_RGBImageRec *pTextureImage[NUMBER_TEXTURE];				// Create Storage Space For The Texture
	memset(pTextureImage, 0, sizeof(void*)* NUMBER_TEXTURE);	// Set The Pointer To NULL
	if ((pTextureImage[0] = LoadBMP("Data/Font.bmp"))			// Load The Font Bitmap
		&& (pTextureImage[1] = LoadBMP("data\\Bumps.bmp")))		// Load The Texture Bitmap
	{
		nStatus = TRUE;											// Set The Status To TRUE
		glGenTextures(NUMBER_TEXTURE, &g_Texture[0]);			// Create Textures
		for (GLuint i = 0; i < NUMBER_TEXTURE; i++)				// Loop Through All The Textures
		{
			// Build All The Textures
			glBindTexture(GL_TEXTURE_2D, g_Texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[i]->sizeX,
				pTextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
				pTextureImage[i]->data);
		}
	}
	for (GLuint i = 0; i < NUMBER_TEXTURE; i++)					// Loop Through All The Textures
	{
		if (pTextureImage[i])									// If Texture Exists
		{
			if (pTextureImage[i]->data)							// If Texture Image Exists
			{
				free(pTextureImage[i]->data);					// Free The Texture Image Memory
			}
			free(pTextureImage[i]);								// Free The Image Structure
		}
	}
	return nStatus;                                        // Return Success
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Build Our Font Display List
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				BuildFont(GLvoid)
{
	float	fX = 0.0f;										// Holds Our X Character Coord
	float	fY = 0.0f;										// Holds Our Y Character Coord
	g_uBase = glGenLists(NUMBER_CHARACTER);					// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, g_Texture[0]);				// Select Our Font Texture
	for (GLuint i = 0; i < NUMBER_CHARACTER; i++)			// Loop Through All 256 Lists
	{
		fX = float(i % 16) / 16.0f;							// X Position Of Current Character
		fY = float(i / 16) / 16.0f;							// Y Position Of Current Character
		glNewList(g_uBase + i, GL_COMPILE);					// Start buiding a list
		glBegin(GL_QUADS);									// Use A Quad For Each Character
		{
			glTexCoord2f(fX, 1 - fY - 0.0625f);				// Texture Coord (Bottom Left)
			glVertex2i(0, 0);								// Vertex Coord (Bottom Left)
			glTexCoord2f(fX + 0.0625f, 1 - fY - 0.0625f);	// Texture Coord (Bottom Right)
			glVertex2i(16, 0);								// Vertex Coord (Bottom Right)
			glTexCoord2f(fX + 0.0625f, 1 - fY);				// Texture Coord (Top Right)
			glVertex2i(16, 16);								// Vertex Coord (Top Right)
			glTexCoord2f(fX, 1 - fY);						// Texture Coord (Top Left)
			glVertex2i(16, 16);								// Vertex Coord (Top Right)
		}
		glEnd();											// Done Building Our Quad (Character)
		glTranslated(10, 0, 0);								// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Delete The Font From Memory
* Parameter:
*	[Inputs]
*		None
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				KillFont(GLvoid)
{
	glDeleteLists(g_uBase, NUMBER_CHARACTER);
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Where The Printing Happens
* Parameter:
*	[Inputs]
*		GLint		x:			X position
*		GLint		y:			Y position
*		char*		pString:	String to print
*		int			nSet:		[Set] value
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
GLvoid				glPrint(GLint x, GLint y, char* pString, int nSet)
{
	if (nSet > 1)											// Is set Greater Than One?
	{
		nSet = 1;											// If So, Make Set Equal One
	}
	glBindTexture(GL_TEXTURE_2D, g_Texture[0]);				// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);								// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);							// Select the projection matrix
	glPushMatrix();											// Store the projection matrix
	glLoadIdentity();										// Reset The Projection Matrix
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);		// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glPushMatrix();											// Store The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslated(x, y, 0);									// Position The Text (0,0 - Bottom Left)
	glListBase(g_uBase - 32 + (128 * nSet));				// Choose The Font Set (0 or 1)
	glCallLists(strlen(pString), GL_UNSIGNED_BYTE, pString);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glPopMatrix();											// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glPopMatrix();											// Restore The Old Modelview Matrix
	glEnable(GL_DEPTH_TEST);								// Enables Depth Testing
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Draw a triangle
* Parameter:
*	[Inputs]
*		GLfloat* 	d1:			Vertex 1
*		GLfloat* 	d2:			Vertex 2
*		GLfloat* 	d3:			Vertex 3
*		GLfloat* 	c1:			Color 1
*		GLfloat* 	c2:			Color 2
*		GLfloat* 	c3:			Color 3
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
void				DrawTriAngles(const GLfloat* d1, const GLfloat* d2, const GLfloat* d3,
	const GLfloat* c1, const GLfloat* c2, const GLfloat* c3)
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Draw a QUADS
* Parameter:
*	[Inputs]
*		GLfloat* 	d1:			Vertex 1
*		GLfloat* 	d2:			Vertex 2
*		GLfloat* 	d3:			Vertex 3
*		GLfloat* 	d4:			Vertex 4
*		GLfloat* 	color:		Color
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
void				DrawQuads3fv(const GLfloat* d1, const GLfloat* d2,
	const GLfloat* d3, const GLfloat* d4, const GLfloat* color)
{
	glColor3fv(color);
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

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Draw a QUADS
* Parameter:
*	[Inputs]
*		GLfloat* 	d1:			Vertex 1
*		GLfloat* 	d2:			Vertex 2
*		GLfloat* 	d3:			Vertex 3
*		GLfloat* 	d4:			Vertex 4
*		GLfloat* 	color:		Color
*  [Output]
*		None
* Return Value:
*	None
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
void				DrawQuads2fv(const GLfloat* d1, const GLfloat* d2,
	const GLfloat* d3, const GLfloat* d4, const GLfloat* color)
{
	glColor3fv(color);
	glBegin(GL_QUADS);									// Draw A Quad
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex2fv(d1);								// Top Left
		glTexCoord2f(1.0f, 0.0f);
		glVertex2fv(d2);								// Top Right
		glTexCoord2f(1.0f, 1.0f);
		glVertex2fv(d3);								// Bottom Right
		glTexCoord2f(0.0f, 1.0f);
		glVertex2fv(d4);								// Bottom Left
	}
	glEnd();											// Done Drawing The Quad
}

/*=======================================================================================
* Module Name:
*	Main module
* Function description:
*	Main entry
* Parameter:
*	[Inputs]
*		HINSTANCE	hInstance:		Instance
*		HINSTANCE	hPrevInstance:	Previous Instance
*		LPSTR		lpCmdLine:		Command Line Parameters
*		int			nCmdShow:		Window Show State
*  [Output]
*		None
* Return Value:
*	Should return 1
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
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