#pragma once
#include "ljx.h"

	BOOL CALLBACK ljx::EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		DWORD dwCurProcessId = *((DWORD*)lParam);
		DWORD dwProcessId = 0;

		GetWindowThreadProcessId(hwnd, &dwProcessId);
		if (dwProcessId == dwCurProcessId && GetParent(hwnd) == NULL)
		{
			*((HWND*)lParam) = hwnd;
			return FALSE;
		}
		return TRUE;
	}


	HWND ljx::GetMainWindow()
	{
		DWORD dwCurrentProcessId = GetCurrentProcessId();
		if (!EnumWindows(ljx::EnumWindowsProc, (LPARAM)&dwCurrentProcessId))
		{
			return (HWND)dwCurrentProcessId;
		}
		return NULL;
	}
	
	HWND ljx::bfhandle = 0;