/*
* Aimbot.cpp : Contains the implementation for the aimbot function
*/

/* Includes for this file */
#include "Aimbot.hpp"
#include "../Global.hpp"
#include "../Vendors/ImGui/imgui.h"
#include "../Vendors/ImGui/imgui_internal.h"
#include "../SDK/sdk.hpp"
#include "../SDK/FrostBite.hpp"
#include "../Utility/Logging/Logging.hpp"
#include <vector>

namespace Aimbot
{
	ClientPlayer* local_player;
	ClientSoldierEntity* local_soldier;
	ClientPlayer* player;
	ClientSoldierEntity* soldier;
	ClientSoldierEntity* closest;
	/* 猎物vector */
	ClientSoldierEntity* targets[64];
	int target_num;
	void refreshpPlayerMgr(void)
	{
		global->encryptlocalplayermgr = getEncryptedPlayerMgr(false);
		global->encryptplayermgr = getEncryptedPlayerMgr(true);
	}
	void AimDetect(void) 
	{
		while (1)
		{
			Sleep(20);
			while (global->aim_enabled && ((GetAsyncKeyState(0x05) & 0x8000)|| (GetAsyncKeyState(0x06) & 0x8000))) {
				
				/* Retrieve the screen size */
				if (global->visuals) {
					local_player = global->local_player;
					global->local_player = NULL;
				}
				else
					local_player = GetLocalPlayer();
				if (!IsValidPtr(local_player)) {Sleep(global->aimdectsec); continue;}

				local_soldier = local_player->clientSoldierEntity;
				if (!IsValidPtr(local_soldier) || local_soldier->IsDead()) { Sleep(global->aimdectsec);  continue; }

				target_num = 0;
				/*遍历所有玩家 */
				for (int i = 0; i < 64; i++)
				{
					if (global->visuals) {
						player = global->players[i];
						global->players[i] = NULL;
					}
					else
						player = GetPlayerById(i);

					if (global->testteammatesforaimbot) 
					{
						if (!player || player == local_player || player->teamId != local_player->teamId)  continue;
						
					}
					else
					{
						if (!player || player == local_player || player->teamId == local_player->teamId) continue; 
					}
					soldier = player->clientSoldierEntity;
					if (!soldier || !soldier->IsValid() || soldier->occluded)continue; 
					targets[target_num++] = soldier;
				}

				/* 屏幕坐标 */
				if (target_num == 0) { Sleep(global->aimdectsec); continue; }
				float closestdist = INFINITY;
				closest = NULL;
				
				
				for (int i = 0; i < target_num; i++)
				{
					ClientSoldierEntity* soldier = targets[i];
					Vec3 loc = soldier->location;
					
					float distancefromcenter = CalculateDistance(local_soldier->location, loc);
					if (distancefromcenter < closestdist)
					{
						closest = targets[i];
						closestdist = distancefromcenter;
					}
				}
				/*static int ii= 0;
				ii = min((ii + 1) % target_num, target_num - 1);
				ClientSoldierEntity* soldier = targets[ii];
				Vec3 loc = soldier->location;
				switch (soldier->poseType)
				{
					case 0:loc.y += global->standoffset; break;
					case 1:loc.y += global->crouchoffset; break;
					case 2:loc.y += global->lyoffset; break;
					default:break;
				};
				
				if (!W2S(loc, closestHead)) break;
				closest = targets[ii];*/
				Sleep(global->aimdectsec);
			}
		}
	}
	void Aim(void)
	{
		/*int cnt = 256;
		ClientSoldierEntity* lst = NULL;
		Vec2 lstscn = Vec2(0., 0.);*/
		while (1) {
			Sleep(20); // Hot thread no no!

			while (global->aim_enabled)
			{
				
				static ClientSoldierEntity* Lastperson = NULL;
				static Vec3 LastpersonheadLoc;
				static bool disablescopeafteraim = false;
				if (closest) {
					
					if ((GetAsyncKeyState(0x05) & 0x8000))
						disablescopeafteraim = true;
					else if ((GetAsyncKeyState(0x06) & 0x8000))
						disablescopeafteraim = false;
					else {
						Sleep(global->aimshotsec); continue;
					}
					
					//POINT point;
					//GetCursorPos(&point);
					Vec3 loc = closest->location;
					switch (closest->poseType)
					{
					case 0:loc.y += global->standoffset; break;
					case 1:loc.y += global->crouchoffset; break;
					case 2:loc.y += global->lyoffset; break;
					default:break;
					};
					Vec3 tmp = loc;
					if (Lastperson&&Lastperson==closest&&global->aimpredict>0)
					{
						loc += (loc - LastpersonheadLoc) * global->aimpredict;
					}
					LastpersonheadLoc = tmp;
					Vec2 closestHead;
					if (!W2S(loc, closestHead)) {
						Sleep(global->aimshotsec); continue;
					}
					//if (lst != closest) {
					SetCursorPos(global->left + closestHead.x + global->aimoffx, global->top + closestHead.y + global->aimoffy);
					mouse_event(MOUSEEVENTF_LEFTDOWN| MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					Sleep(global->presssec);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					if (disablescopeafteraim) {  mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0); }
					//SetCursorPos(point.x, point.y);
					//lst = closest;
					//lstscn = closestHead;
					
				}
				Lastperson = closest;
				
				Sleep(global->aimshotsec);
			}

		}

	}
}