#pragma once
#ifndef _LJX 
#define _LJX
#include <Windows.h>
#include <string>
#include<tchar.h>
#include <TlHelp32.h>

namespace ljx
{
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	


	HWND GetMainWindow();
	
	extern HWND bfhandle;
}

#endif // !_LJX 
