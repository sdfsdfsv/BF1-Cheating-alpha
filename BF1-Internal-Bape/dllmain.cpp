/*
* dllmain.cpp : Defines the entry point for this binary and the main thread
*/

#include <windows.h>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include "Utility/Console/Console.hpp"
#include "Utility/Logging/Logging.hpp"
#include "Hooks/DirectX 11 Hook/DXHook.hpp"
#include "Drawing/Menu/Menu.hpp"
#include "Drawing/Visuals/Visuals.hpp"
#include "Global.hpp"
#include "Utility/Discord RPC/Discord.hpp"
#include "Aimbot/Aimbot.hpp"
#include "Drawing/Functions/ljx.h"
bool pressed = false;

/*
* 主程序
* Main thread for this binary, bootstrapped off the API entry point
*/
inline void Main(HMODULE hModule){
	
	//Console::Allocate("Debug Console");/* Allocate a console window to the target process */
	//
	//Log::Success("Console Allocated");/* Log the creation of the console window */

	///* Log the change in discord Status */
	//Log::Initialize("Discord RPC");

	/* Initialize discord RPC inside a scope because thats hot */
	{
		/* Create an instance of the discordRPC class */
		DiscordRPC discord_rpc;

		/* Initialize the discord RPC with an api key */
		discord_rpc.Init("749153609035415583");

		/* Declear the RPC information */
		DiscordRichPresence rpc;
		rpc.state = "BF1 Internal";
		rpc.startTimestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		rpc.endTimestamp = NULL;	
		rpc.largeImageKey = "bf1guy";
		rpc.largeImageText = "Bape Internal";
		discord_rpc.Update(&rpc);
	}

	
	{/* 初始化钩子 */
		std::vector<std::function<void()>> task_list = { Visual::Draw, Menu::Draw };/* Populate this with drawing tasks */
		dx_hook->Init(task_list);/* 初始化钩子 */
	}


	ljx::bfhandle=ljx::GetMainWindow();
	{/* 创建自瞄进程 */
		std::thread t_getrect(&Global::grect);
		t_getrect.detach();
		std::thread t_aimbot(&Aimbot::Aim);
		t_aimbot.detach();
		
	}

	
	while (true){
		/* Exit thread if insert is press */
		if (GetAsyncKeyState(VK_END)) break;

		/*切换主菜单状态 */
		pressed = false;
		while (GetAsyncKeyState(VK_INSERT))
		{
			if (!pressed) {
				global->is_menu_open = !global->is_menu_open;
				global->cursor_unlocked = !global->cursor_unlocked;
				pressed = true;
			}
		}

		/* 防止hot looping*/
		SleepEx(1, true);
	}

	/* 提示主进程已退出 */
	Log::Warn("Main thread has been exited. [Deallocating console][Freeing library]");

	/* Remove the present hook */
	dx_hook->Remove();

	/* Deallocate the console window from the target process */
	//Console::DeAllocate();

	/* Exit thread and close handle */
	FreeLibraryAndExitThread(hModule, 0);
}

/*
* 启动主进程
* Entrypoint for the Dynamic link library.
* Will boot strap the main thread
*/
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr));
	}
	else
	{
		/* DLL_PROCESS_DETACH handler here */
	}

	return TRUE;
}
