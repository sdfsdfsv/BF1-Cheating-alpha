#ifndef _DISCORD_HPP
#define _DISCORD_HPP

#include <Windows.h>
#include "Discord/discord_rpc.h"
#include "Discord/discord_register.h"

/* Declare the discord class wrapper声明不规则类包装器？ */
class DiscordRPC{
public: 
	void Init(const char* api_key);
	void Update(DiscordRichPresence* rpc);
};

#endif 
