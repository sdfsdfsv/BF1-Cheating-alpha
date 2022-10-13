/*
* Draw.cpp : Contains the implementation for the wrapped ImGui Drawing functions 
*/

/* Includes for this file */
#include "Draw.hpp"
#include "../../Vendors/ImGui/imgui_internal.h"
#include "../../Global.hpp"
#include "ljx.h"
/* Implementation for drawing text */
void Draw::Text(ImVec2 pos, ImColor col, std::string str, DrawFlags flags)
{
	
	/* Check if the rect is within bounds of the render frame */
	/*if ((pos.x >= rect.right || pos.y >= rect.top) || (pos.x <= rect.left || pos.y <= rect.bottom))
	{
		if (flags & BOUNDS) return;
	}*/

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Check if the centered text flag was applied */
	if (flags & CENTERED)
	{
		/* Update the text position to the center */
		pos.x -= (ImGui::CalcTextSize(str.c_str()).x) / 2.0f;
	}

	/* Check if the outline text flag was applied */
	if (flags & OUTLINE)
	{
		window->DrawList->AddText(pos, ImColor(0.0f, 0.0f, 0.0f, 1.0f), str.c_str());
	}

	/* Add text to draw list */
	window->DrawList->AddText(pos, col, str.c_str());

}

/* Implementation for drawing a line */
void Draw::Line(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, DrawFlags flags)
{
	
	/* Check if the rect is within bounds of the render frame */
	/*if ((pt.x >= rect.right || pt.y >= rect.top) || (pb.x <= rect.left || pb.y <= rect.bottom))
	{
		if (flags & BOUNDS) return;
	}*/

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the line */
		window->DrawList->AddLine(pt, pb, ImColor(0.0f, 0.0f, 0.0f, 1.0f), thickness + 3);
	}

	/* Draw the outline of the line */
	window->DrawList->AddLine(pt, pb, col, thickness);
}

/* Implementation for drawing a circle */
void Draw::CircleFilled(ImVec2 pos, ImColor col, int radius, int thickness, int segments, DrawFlags flags)
{
	
	/* Check if the rect is within bounds of the render frame */
	/*if ((pos.x >= rect.right || pos.y >= rect.top) || (pos.x <= rect.left || pos.y <= rect.bottom))
	{
		if (flags & BOUNDS) return;
	}*/

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the circle */
		window->DrawList->AddCircle(pos, radius, ImColor(0.0f, 0.0f, 0.0f, 1.0f), segments, thickness + 3);
	}

	/* Distinguish whether the flag specified wanted a solid object */
	if (flags & SOLID)
	{
		/* Draw a solid circle */
		window->DrawList->AddCircleFilled(pos, radius, col, segments);
	}
	else
	{
		/* Draw a Cricle if solid wasnt specified */
		window->DrawList->AddCircle(pos, radius, col, segments, thickness);
	}
}

/* Implementation for drawing a rectangle */
void Draw::Rectangle(ImVec2 pt, ImVec2 pb, ImColor col, int thickness, float rounding, ImDrawCornerFlags corner_flags, DrawFlags flags)
{
	

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	/* Distinguish whether flag specified wanted an outline */
	if (flags & OUTLINE)
	{
		/* Draw the outline of the rectangle */
		window->DrawList->AddRect(pt, pb, ImColor(0.0f, 0.0f, 0.0f, 1.0f), rounding, corner_flags, thickness + 3);
	}

	/* Distinguish whether the flag specified wanted a solid or filled object */
	if (flags & SOLID)
	{
		/* Draw the solid rectangle */
		window->DrawList->AddRectFilled(pt, pb, col, rounding, corner_flags);
	}
	else if (flags & FILLED)
	{
		/* Draw the solid rectangle */
		window->DrawList->AddRectFilled(pt, pb, ImColor(0.0f, 0.0f, 0.0f, 0.5f), rounding, corner_flags);
	}
	else
	{
		/* Draw a rectangle if solid wasnt specified */
		window->DrawList->AddRect(pt, pb, col, rounding, corner_flags, thickness);
	}
}

void Draw::Circle(ImVec2 pos, float points, float radius, ImColor color) {
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		ImVec2 start(radius * cosf(a) + pos.x, radius * sinf(a) + pos.y);
		ImVec2 end(radius * cosf(a + step) + pos.x, radius * sinf(a + step) + pos.y);
		Draw::Line(start, end, color, 1, NONE);
	}
}

/* Implementation for the X cross hair */
void Draw::XCrossHair(ImColor col)
{
	/* Create a pos vector (( Center of the screen )) */
	
	ImVec2 center = global->display_size;
	/* Draw crosshair */
	this->Line(ImVec2(center.x - 5+ global->drawoffx, center.y+ global->drawoffy), ImVec2(center.x + 4+ global->drawoffx, center.y+ global->drawoffy), col, 2, NONE); // horizontal
	this->Line(ImVec2(center.x - 1+ global->drawoffx, center.y - 4+ global->drawoffy), ImVec2(center.x - 1+ global->drawoffx, center.y + 5+ global->drawoffy), col, 2, NONE); // vertical
}

void Draw::Rectangle3D(Vec3 location, ImColor col) {
	/* We need 3 vectors */
}

void Draw::HealthBar(ImVec2 pos, int h, float health, float mHealth) {
	float flBoxes = std::ceil(health / 10.f);
	float flX = pos.x;
	//-7 - h / 4.f;
	float flY = pos.y - 1;
	float flHeight = h / 10.f;
	float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
	ImColor ColHealth(0.0f, 1.0f, 0.0f);

	draw->Rectangle(ImVec2(flX, flY), ImVec2(flX, flY + 2), ImColor(0.8f, 0.8f, 0.8f, 0.5), 1.0f, 0, NONE, SOLID); /* background */
	draw->Rectangle(ImVec2(flX, flY), ImVec2(flX, flY + 2), ImColor(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0, OUTLINE, SOLID); /* outline */
	draw->Rectangle(ImVec2(flX + 1, flY), ImVec2(flX, flHeight * flBoxes + 1), ColHealth, 1.0f, 0.0f, NONE, SOLID); /* green health bar*/

	for (int i = 0; i < 10; i++)
		draw->Line(ImVec2(flX, flY + i * flHeight), ImVec2(flX + 4, flHeight), flY + i * flHeight, ImColor(0.0f, 0.0f, 0.0f, 1.0f), NONE);
}

void Draw::CornerRectangle(ImVec2 pt, ImVec2 pb, ImColor col, float length,int thickness,ImDrawCornerFlags corner_flags, DrawFlags flags) {
	
	/* Check if the rect is within bounds of the render frame */
	/*if ((pt.x >= rect.right || pt.y >= rect.top) || (pb.x <= rect.left || pb.y <= rect.bottom))
	{
		if (flags & BOUNDS) return;
	}*/

	/* Get the ImGui window class */
	ImGuiWindow* window = ImGui::GetCurrentWindow();

}

Draw* draw = new Draw;