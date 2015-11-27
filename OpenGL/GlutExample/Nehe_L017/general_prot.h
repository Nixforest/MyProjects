/*=======================================================================================
*	Copyright (c) Nixforest Corporation. 2015 All rights reserved.
*
* File Discription:
*	General prototypes
*
* Note:
*	None
*
* History:
*	Date		Version		Code		PIC				Description
*	2006/09/26	v0000.00	XXXXXXXX	NguyenPT		First create
*=======================================================================================*/
#ifndef _GENERAL_PROT_H_
#define	_GENERAL_PROT_H_
#include <windows.h>
#include <gl\GL.h>
#include <gl\GLAUX.H>
/* ----- Define prototypes ----- */
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);										/* Declare for WndProc 										*/
BOOL				CreateGLWindow(char* title,													/* This Code Creates Our OpenGL Window						*/
						int width, int height, int bits, bool fullScreenFlag);
GLvoid				ReSizeGLScene(GLsizei width, GLsizei height);								/* Resize and initialize the GL Window 						*/
int					InitGL(GLvoid);																/* All setup for openGL goes here 							*/
int					DrawGLScene(GLvoid);														/* Here's where we do all the drawing 						*/
GLvoid				KillGLWindow(GLvoid);														/* Properly kill the window 								*/
GLvoid				ProcessKeyboard();															/* Assign type of key and function handle when press key 	*/
GLvoid				OnPressP(GLvoid);															/* Handle when press 'P'									*/
GLvoid				OnPressL(GLvoid);															/* Handle when press 'L'									*/
GLvoid				OnPressF(GLvoid);															/* Handle when press 'F'									*/
GLvoid				OnPressF1(GLvoid);															/* Handle when press 'F1'									*/
GLvoid				OnPressLEFT(GLvoid);														/* Handle when press 'LEFT'									*/
GLvoid				OnPressRIGHT(GLvoid);														/* Handle when press 'RIGHT'								*/
GLvoid				OnPressUP(GLvoid);															/* Handle when press 'UP'									*/
GLvoid				OnPressDOWN(GLvoid);														/* Handle when press 'DOWN'									*/
GLvoid				OnPressINSERT(GLvoid);														/* Handle when press 'INSERT'								*/
GLvoid				OnPressDELETE(GLvoid);														/* Handle when press 'DELETE'								*/
GLvoid				OnPressHOME(GLvoid);														/* Handle when press 'HOME'									*/
GLvoid				OnPressEND(GLvoid);															/* Handle when press 'END'									*/
GLvoid				OnPressPRIOR(GLvoid);														/* Handle when press 'PRIOR'								*/
GLvoid				OnPressNEXT(GLvoid);														/* Handle when press 'NEXT'									*/
AUX_RGBImageRec*	LoadBMP(char* pFileName);													/* Load a bitmap image 										*/
int					LoadGLTextures();															/* Load all textures 										*/
GLvoid				BuildFont(GLvoid);															/* Build Our Font Display List 								*/
GLvoid				KillFont(GLvoid);															/* Delete The Font From Memory								*/
GLvoid				glPrint(GLint x, GLint y, char* pString, int nSet);							/* Where The Printing Happens								*/
void				DrawTriAngles(const GLfloat* d1,											/* Draw a triangle											*/
						const GLfloat* d2, const GLfloat* d3,
						const GLfloat* c1, const GLfloat* c2, const GLfloat* c3);
void				DrawQuads(const GLfloat* d1,												/* Draw a QUADS												*/
						const GLfloat* d2, const GLfloat* d3,
						const GLfloat* d4, const GLfloat* color);
#endif // !_GENERAL_PROT_H_