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
	bool budamage_enabled = false;
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

	float standoffset=1.27f, crouchoffset=1.05, lyoffset=0.15f;
	int aimoffx = 0, aimoffy = 9;
	float aimpredict = 0.0;
	int drawoffx = 0, drawoffy = -0;
	int budamage = 8888;
	ImVec2 display_size=ImVec2(1000,1000);
	int aimdectsec = 4, aimshotsec = 4;
	int presssec = 3;
	long top, left;
	static void grect(void);
	void saveData(void);
	void loadData(void);
};

extern Global* global;

#endif 
