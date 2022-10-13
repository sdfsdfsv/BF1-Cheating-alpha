
#include "Global.hpp"
#include"Drawing/Functions/ljx.h"
Global* global = new Global;
void Global::grect(void) {
	while (1) {
		RECT rect;
		GetWindowRect(ljx::bfhandle, &rect);
		global->display_size = ImVec2((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
		Sleep(5000);
	}
}