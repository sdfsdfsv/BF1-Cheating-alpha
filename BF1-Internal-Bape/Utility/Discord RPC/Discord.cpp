#include "Discord.hpp"

/* Implementation for discordRPC initialize */
void DiscordRPC::Init(const char* api_key){
	DiscordEventHandlers handle;/*  创建进程句柄*/
	
	memset(&handle, 0, sizeof(handle));/* 清理*/

	Discord_Initialize(api_key, &handle, 1, NULL);/* 初始化*/
}

/* Implementation for discordRPC update
不知道是什么玩意*/
void DiscordRPC::Update(DiscordRichPresence* rpc)
{
	/* Update the discord presence*/
	Discord_UpdatePresence(rpc);
}