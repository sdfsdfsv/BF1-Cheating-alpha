/* 
* Global.hpp : Contains the global varible class 
*/

#ifndef _GLOBAL_HPP
#define _GLOBAL_HPP

#include <Windows.h>
#include "Vendors/ImGui/imgui.h"

class Global
{
public:
	/* General */
	bool is_menu_open = true;
	bool cursor_unlocked = true;
	
	/* Aim */
	bool aim_enabled = false;
	int aim_key = 0x70;

	/* Visuals */
	bool visuals = false;
	bool visuals_box = false;
	bool visuals_enemy_only = true;
	bool visuals_skeleton = false;
	bool visuals_headcircle = true;
	bool visuals_info = false;
	bool visuals_healthbar = false;

	/* Misc. */
	bool misc_crosshair = false;

	/* Colors-v */
	ImColor c_cross_hair = ImColor(1.0f, 0.0f, 1.0f);
	ImColor c_visuals_skeleton = ImColor(1.0f, 1.0f, 0.8627f);
	ImColor c_visuals_headcircle = ImColor(1.0f, 0.75686f, 0.75686f);
	ImColor c_visuals_info = ImColor(0.3882f, 0.7215f, 1.0f);
	/* team */
	ImColor c_t_visuals_box = ImColor(1.0f, 1.0f, 1.0f);
	/* enemy */
	ImColor c_e_visuals_box = ImColor(1.0f, 1.0f, 1.0f);
	ImColor c_e_visuals_box_visible = ImColor(1.0f, 1.0f, 1.0f);

	float standoffset=1.45f, crouchoffset=1.0f, lyoffset=0.35f;
	int aimoffx = 0, aimoffy = 15;
	float aimpredict = 0.35;
	int drawoffx = -8, drawoffy = -24;
	ImVec2 display_size=ImVec2(1000,1000);
	static void grect(void);
};

extern Global* global;

#endif 
