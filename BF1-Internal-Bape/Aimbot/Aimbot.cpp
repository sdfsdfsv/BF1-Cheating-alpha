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
	void AimDetect() {
		while (1)
		{
			Sleep(20);
			while (global->aim_enabled && (GetAsyncKeyState(0x05) & 0x8000)) {
				Sleep(global->aimdectsec);

				/* Retrieve the screen size */

				local_player = GetLocalPlayer();
				if (!IsValidPtr(local_player)) continue;

				local_soldier = local_player->clientSoldierEntity;
				if (!IsValidPtr(local_soldier) || local_soldier->IsDead()) continue;

				target_num = 0;
				/*遍历所有玩家 */
				for (int i = 0; i < 64; i++)
				{
					player = GetPlayerById(i);
					if (!IsValidPtr(player) || player == local_player || player->teamId == local_player->teamId) continue;

					soldier = player->clientSoldierEntity;
					if (!IsValidPtr(soldier) || !soldier->IsValid() || soldier->occluded) continue;
					targets[target_num++] = soldier;
				}

				/* 屏幕坐标 */
				if (target_num == 0)continue;
				float closestdist = INFINITY;
				closest = NULL;
				
				
				for (int i = 0; i < target_num; i++)
				{
					ClientSoldierEntity* soldier = targets[i];
					Vec3 loc = soldier->location;
					
					float distancefromcenter = CalculateDistance(local_soldier->location, loc);
					if (distancefromcenter < closestdist&&distancefromcenter>0.5f)
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
				
			}
		}
	}
	void Aim()
	{
		/*int cnt = 256;
		ClientSoldierEntity* lst = NULL;
		Vec2 lstscn = Vec2(0., 0.);*/
		while (1) {
			Sleep(20); // Hot thread no no!

			while (global->aim_enabled && (GetAsyncKeyState(0x05) & 0x8000))
			{
				static ClientSoldierEntity* Lastperson=NULL;
				static Vec3 LastpersonheadLoc;
				Sleep(global->aimshotsec);
				if (IsValidPtr(closest)) {
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
					if (IsValidPtr(Lastperson)&&Lastperson==closest&&global->aimpredict>0)
					{
						Vec3 tmp = loc;
						loc += (loc - LastpersonheadLoc) * global->aimpredict;
						LastpersonheadLoc = tmp;
					}
						
					Vec2 closestHead;
					if (!W2S(loc, closestHead))continue;
					//if (lst != closest) {
					SetCursorPos(global->left + closestHead.x + global->aimoffx, global->top + closestHead.y + global->aimoffy);


					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(global->presssec);//要留给某些应用的反应时间 
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					//SetCursorPos(point.x, point.y);
					//lst = closest;
					//lstscn = closestHead;
					
				}
				Lastperson = closest;
				

			}

		}

	}
}