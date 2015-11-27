/*=======================================================================================
*	Copyright (c) Nixforest Corporation. 2015 All rights reserved.
*
* File Discription:
*	General defines
*
* Note:
*	None
*
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
#ifndef _GENERAL_DEFS_H_
#define	_GENERAL_DEFS_H_
#include <windows.h>
#include <gl\GL.h>
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
#define		NUMBER_TEXTURE						2							// Number of textures
#define		NUMBER_FILTER						3							// Number of filters
#define		NUMBER_CHARACTER					256							// Number of character

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
#endif // !_GENERAL_DEFS_H_
