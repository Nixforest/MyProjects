// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#pragma data_seg("SHAREDDATA")
HWND	hWndHook = NULL;
HHOOK g_HookHandle = 0;
#pragma data_seg()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HINSTANCE	hInst;
HHOOK		hook;
static LRESULT CALLBACK HookMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam);

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
		hInst = hInstance;

		new CDynLinkLibrary(HookMessageBoxDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("HookMessageBox.DLL Terminating!\n");
		if (hWndHook)
		{
			// Clear hook
		}
		// Terminate the library before destructors are called
		AfxTermExtensionModule(HookMessageBoxDLL);
	}
	return 1;   // ok
}
BOOL WINAPI InstallHook(HWND hWnd)
{
	if (hWndHook)
	{
		return FALSE;
	}
	hook = SetWindowsHookEx(WH_CBT, (HOOKPROC)HookMessageBoxProc,
		hInst, 0);
	if (hook)
	{
		hWndHook = hWnd;
		return TRUE;
	}
	return FALSE;
}
BOOL UnInstallHook(HWND hWnd)
{
	if (hWnd != hWndHook)
	{
		return FALSE;
	}
	BOOL bRet = UnhookWindowsHookEx(hook);
	if (bRet)
	{
		hWndHook = NULL;
	}
	return bRet;
}
static LRESULT CALLBACK HookMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		CallNextHookEx(hook, nCode, wParam, lParam);
		return 0;
	}
	switch (nCode)
	{
	case HCBT_CREATEWND:
		{
			OutputDebugString(_T("HCBT_CREATEWND\n"));
			HWND hWnd = (HWND)wParam;
			_TCHAR name[MAX_PATH];
			::GetWindowText(hWnd, name, MAX_PATH);
			OutputDebugString(name);
			OutputDebugString(_T("\n"));
		}
		break;

	case HCBT_ACTIVATE:
		{
			OutputDebugString(_T("HCBT_ACTIVATE\n"));
			HWND hWnd = (HWND)wParam;
			_TCHAR name[MAX_PATH];
			::GetWindowText(hWnd, name, MAX_PATH);
			OutputDebugString(name);
			OutputDebugString(_T("\n"));
		}
		break;
	default: break;
	}
	return 0;
}