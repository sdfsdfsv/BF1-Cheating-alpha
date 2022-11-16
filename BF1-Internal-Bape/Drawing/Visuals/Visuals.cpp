/*
* Visuals.cpp : Contains the implementation for the visuals drawing function
*/

/* Includes for this file */
#include "Visuals.hpp"
#include "../../Global.hpp"
#include "../Functions/Draw.hpp"
#include "../../Vendors/ImGui/imgui.h"
#include "../../Vendors/ImGui/imgui_internal.h"
#include "../../SDK/sdk.hpp"
#include "../../SDK/FrostBite.hpp"
#include <ctime>

namespace Visual
{
	void Draw()
	{
		/* Push a transparent style */
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		/* set the border to 0 resulting in no 1px wide white border */
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		/* Create the window to be drawn on */
		ImGui::Begin("Visuals", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMouseInputs);

		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);

		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		{
			if (global->misc_crosshair)
				draw->XCrossHair(global->c_cross_hair);

			/* Attempt to get the local player instance */
			ClientPlayer* local_player = GetLocalPlayer();

			if (!IsValidPtr(local_player)) return;

			std::string name = local_player->name;

			if (!global->visuals) return;

			/* Check that local player is valid */
			if (!IsValidPtr(local_player)) return;

			/* Get localplayers soldier */
			ClientSoldierEntity* local_soldier = local_player->clientSoldierEntity;

			/* Check that Client soldier is valid */
			if (!IsValidPtr(local_soldier)||local_soldier->IsDead()) return;

			/* Walk the entirety of the player list */
			for (int i = 0; i <= 64; i++)
			{
				/* Get this iterations player */
				ClientPlayer* player = GetPlayerById(i);

				/* Check that the player is valid */
				if (!IsValidPtr(player)) continue;

				bool team = false; if (player->teamId == local_player->teamId) team = true;
				if (global->visuals_enemy_only && team) continue;
				
				/* Get this iterations soldier */
				ClientSoldierEntity* soldier = player->clientSoldierEntity;

				/* Check that Client soldier is valid */
				if (!IsValidPtr(soldier)) continue;

				/* Check that this player is valid */
				if (soldier->IsDead()) continue;

				/* World to screen the players position */
				Vec3 headpos = soldier->location;
				Vec2 base_screen, head_screen;

				/* World to screen the players head positon */
				if (soldier->poseType == 0) headpos.y += global->standoffset;
				else if (soldier->poseType == 1) headpos.y += global->crouchoffset;
				else if (soldier->poseType == 2) headpos.y += global->lyoffset;
				

				if (global->visuals_headcircle) {
					/* convert vec2 to imvec2 */
					if (!W2S(headpos, head_screen)) continue;
					/* draw a circle @ head position */
					draw->Circle(ImVec2(head_screen.x+global->drawoffx,head_screen.y+global->drawoffy), 4, 5, global->c_visuals_headcircle);
				}

				if (global->visuals_box) {
					
					Vec2 c1; Vec2 c2;
					auto aabb = soldier->GetAABB();
					W2S(headpos + Vec3(aabb.min.x, aabb.min.y, aabb.max.z), c1);
					W2S(headpos + Vec3(aabb.max.x, aabb.max.y, aabb.max.z), c2);

					ImColor boxColor;
					if (!team) 
						boxColor = global->c_e_visuals_box;
					else 
						boxColor = global->c_t_visuals_box;

					if (!soldier->occluded) boxColor = global->c_e_visuals_box_visible;
					draw->Rectangle(ImVec2(c1.x + 10+global->drawoffx, c1.y+ global->drawoffy), ImVec2(c2.x+ global->drawoffx - 10,c2.y+ global->drawoffy), boxColor, 2, 1.0f, NONE, NONE);
				}

				//if (global->visuals_healthbar) { /* broken */
				//	Vec2 pos2D;
				//	W2S(soldier->location, pos2D);
				//	draw->HealthBar(ToImVec2(pos2D), pos2D.y, soldier->healthcomponent->m_Health, soldier->healthcomponent->m_MaxHealth);
				//}

				if (global->visuals_info) {
					/* Form the information to display */
					char buffer[128];
					if (!W2S(headpos, head_screen)) continue;
					/* Create the upper text */
					sprintf(buffer, "[%dHP]", (int)soldier->healthcomponent->m_Health);

			
					draw->Text(ImVec2(head_screen.x + global->drawoffx, head_screen.y + global->drawoffy), global->c_visuals_info, buffer, CENTERED | OUTLINE);
				}

				if (global->visuals_skeleton) {
					/* draw skeleton */
					DrawSkeleton(soldier, global->c_visuals_skeleton);
				}
				if (global->budamage_enabled) {
					int *p=(int *)(ljx::bfhandle+0x1AE0151);
					*p = 8888;
					p = (int*)(ljx::bfhandle + 0x141AE0151);
					*p = 8888;
					DWORD tmp;
					WriteProcessMemory(ljx::bfhandle, (LPVOID)0x1AE0151, &global->budamage, 4, 0);
					global->budamage_enabled = false;
				}
			}
		}

		/* Span the draw to the entire screen */
		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();

		/* End the overlay window */
		ImGui::End();

		/* Pop the transparent colour we made earlier */
		ImGui::PopStyleColor();
	}
}