
#include "Global.hpp"
#include"Drawing/Functions/ljx.h"
#include <fstream>
Global* global = new Global;
void Global::grect(void) {
	while (1) {
		RECT rect;
		GetWindowRect(ljx::bfhandle, &rect);
		global->display_size = ImVec2((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
		global->top = rect.top;
		global->left = rect.left;
		Sleep(10000);
	}
}
void Global::saveData(void) {
	std::ofstream outFile("data.txt", std::ios::out);

	outFile << standoffset <<std::endl;
	outFile << crouchoffset <<std::endl;
	outFile << lyoffset << std::endl;
	outFile << aimoffx << std::endl;
	outFile << aimoffy << std::endl;
	outFile << aimpredict << std::endl;
	outFile << drawoffx << std::endl;
	outFile << drawoffy << std::endl;
	outFile << budamage << std::endl;
	outFile << aimdectsec << std::endl;
	outFile << aimshotsec << std::endl;
	outFile << presssec << std::endl;

	outFile.close();
}
void Global::loadData(void) {
	std::ifstream outFile("data.txt");
	if (!outFile.is_open()) { outFile.close(); return; }
	outFile >> standoffset;
	outFile >> crouchoffset;
	outFile >> lyoffset;
	outFile >> aimoffx;
	outFile >> aimoffy;
	outFile >> aimpredict;
	outFile >> drawoffx;
	outFile >> drawoffy;
	outFile >> budamage;
	outFile >> aimdectsec;
	outFile >> aimshotsec;
	outFile >> presssec;

	outFile.close();
}