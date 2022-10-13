/*
* Draw.hpp : Defines the external linkage for the Wrapped ImGui Drawing functions 
*/



/* Includes for this header */
#include <Windows.h>
#include <string>
#include<tchar.h>
#include <TlHelp32.h>
#include "../../Hooks/DirectX 11 Hook/DXHook.hpp"
#include "../../Vendors/ImGui/imgui.h"
#include "../../Math/Vec3.hpp"
#include "../../SDK/sdk.hpp"
#ifndef _DRAW_HPP
#define _DRAW_HPP

#define M_PI 3.141592//65358979323846264338327950288

/* flags包含不同的绘画格式*/
enum DrawFlags
{
	SOLID = 1 << 0,
	OUTLINE = 1 << 1,
	CENTERED = 1 << 2,
	BOUNDS = 1 << 3,
	NONE = 1 << 4,
	FILLED = 1 << 5
};
DEFINE_ENUM_FLAG_OPERATORS(DrawFlags);


class Draw
{
public:
	void Rectangle(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, float rounding, ImDrawCornerFlags corner_flags, DrawFlags flags);
	void CornerRectangle(ImVec2 pt, ImVec2 pb, ImColor col, float length, int thickness, ImDrawCornerFlags corner_flags, DrawFlags flags);
	void CircleFilled(ImVec2 pos, ImColor col, int radius, int thickness, int segments, DrawFlags flags);
	void Circle(ImVec2 pos, float points, float radius, ImColor color);
	void Line(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, DrawFlags flags);
	void Text(ImVec2 pos, ImColor col, std::string str, DrawFlags flags);
	void XCrossHair(ImColor col);
	void Rectangle3D(Vec3 location, ImColor col);
	void HealthBar(ImVec2 pos, int h, float health, float mHealth);
	

};

extern Draw* draw;

#endif // _DRAW_HPP
