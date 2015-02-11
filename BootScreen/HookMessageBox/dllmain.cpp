// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>
#define	MSGBOX_STYLE		(WS_CAPTION		| \
							WS_POPUP		| \
							WS_CLIPSIBLINGS | \
							WS_SYSMENU		| \
							DS_ABSALIGN		| \
							DS_3DLOOK		| \
							DS_SETFONT		| \
							DS_NOIDLEMSG)
#define	BS_WND_NAME			_T("Boot Screen")

#pragma data_seg("SHARED_DATA")
HHOOK g_HookHandle = 0;
#pragma data_seg()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE HookMessageBoxDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("HookMessageBox.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(HookMessageBoxDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.
		//hInst = hInstance;

		new CDynLinkLibrary(HookMessageBoxDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("HookMessageBox.DLL Terminating!\n");
		//if (hWndHook)
		{
			// Clear hook
		}
		// Terminate the library before destructors are called
		AfxTermExtensionModule(HookMessageBoxDLL);
	}
	return 1;   // ok
}
__declspec(dllexport) LRESULT CALLBACK HookMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		CallNextHookEx(g_HookHandle, nCode, wParam, lParam);
		return 0;
	}
	switch (nCode)
	{
	case HCBT_ACTIVATE:
		{
			HWND hWnd = (HWND)wParam;
			LONG dwStyle = GetWindowLong(hWnd, GWL_STYLE);
			if ((dwStyle | MSGBOX_STYLE) == dwStyle)
			{	
				HWND hWndBS = FindWindow(NULL, BS_WND_NAME);
				if (hWndBS)
				{
					SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE);
				}
			}
		}
		break;
	default: break;
	}
	return CallNextHookEx(g_HookHandle, nCode, wParam, lParam);
}
/* Set hook handle */
__declspec(dllexport) void SetGlobalHookHandle(HHOOK hHook)
{
	g_HookHandle = hHook;
}