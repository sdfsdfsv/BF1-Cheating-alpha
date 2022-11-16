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
	void Aim()
	{
		int cnt=256;
		ClientSoldierEntity* lst = NULL;
		Vec2 lstscn=Vec2(0.,0.);
		for (;;) {
			Sleep(20); // Hot thread no no!

			while (global->aim_enabled && (GetAsyncKeyState(0x05) & 0x8000))
			{

				Sleep(global->aimdectsec);
				RECT rect;
			

				/* Retrieve the screen size */
				
				ClientPlayer* local_player = GetLocalPlayer();

				if (!IsValidPtr(local_player)) continue;

				ClientSoldierEntity* local_soldier = local_player->clientSoldierEntity;
			
				if (!IsValidPtr(local_soldier)||local_soldier->IsDead()) continue;

				/* 猎物vector */
				std::vector<ClientSoldierEntity*> targets={};

				/*遍历所有玩家 */
				for (int i = 0; i < 64; i++)
				{
					ClientPlayer* player = GetPlayerById(i);
					
					if (!IsValidPtr(player)|| player->teamId == local_player->teamId) continue;
					
					ClientSoldierEntity* soldier = player->clientSoldierEntity;
				
					if (!IsValidPtr(soldier)|| soldier->IsDead()|| local_player->getId() == player->getId()||soldier->occluded) continue;

					targets.push_back(soldier);
				}

				/* 屏幕坐标 */
				if (targets.size() == 0)continue;
				float closestdist = 9999999.f;
				ClientSoldierEntity* closest = NULL;
				auto closestHead=Vec2(0,0);

				for (int i = 0; i < targets.size(); i++) {
					ClientSoldierEntity* soldier = targets[i];
					Vec3 loc=soldier->location;
					switch (soldier->poseType) {
					case 0:loc.y += global->standoffset;break;
					case 1:loc.y += global->crouchoffset;break;
					case 2:loc.y += global->lyoffset; break;
					default:break;
					};
					
					Vec2 head_screen; 
					if (!W2S(loc, head_screen)) continue;
					float distancefromcenter = CalculateDistance(local_soldier->location,soldier->location);
					if (distancefromcenter < closestdist) {
						closest = targets[i];
						closestdist = distancefromcenter;
						closestHead = head_screen;
					}
				}
				
				if (closest) {
					float dx, dy;
					if (!IsValidPtr(closest)) continue;
					if (lst != closest) {
						SetCursorPos(global->left+closestHead.x + global->aimoffx, global->top+closestHead.y + global->aimoffy);
					}
					else {
						dx = closestHead.x - lstscn.x;
						SetCursorPos(global->left+closestHead.x+global->aimpredict*dx + global->aimoffx , global->top+closestHead.y  + global->aimoffy);
					}
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(global->presssec);//要留给某些应用的反应时间 
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					lst = closest;
					lstscn = closestHead;
					
				}
				
			}

		}
		
	}
}