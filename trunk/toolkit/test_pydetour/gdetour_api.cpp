
#include "stdafx.h"

#include "gdetour_api.h"


gdetour::gdetour() {
	this->imp_add_detour = NULL;
	this->imp_run_python_file = NULL;

#ifdef _DEBUG
	HMODULE gd = LoadLibrary("pydetour_d.pyd");
	if (gd == NULL) {
		MessageBox(0,"Could not load pydetour_d.pyd", "Error", 0);
		return;
	}
#else
	HMODULE gd = LoadLibrary("pydetour.pyd");
	if (gd == NULL) {
		MessageBox(0,"Could not load pydetour.pyd", "Error", 0);
		return;
	}
#endif
	this->imp_add_detour = (add_detour_func) GetProcAddress(gd, "add_detour");
	if (this->imp_add_detour == NULL) {
		MessageBox(0,"Could not find add_detour in gdetour.pyd", "Error", 0);
	}
	this->imp_run_python_file = (run_python_file_func) GetProcAddress(gd, "run_python_file");
	if (this->imp_run_python_file == NULL) {
		MessageBox(0,"Could not find run_python_file in gdetour.pyd", "Error", 0);
	}
}
bool gdetour::add_detour(BYTE* address, int overwrite_length, int bytes_to_pop, int type) {
	if (this->imp_add_detour == NULL) {
		MessageBox(0,"Could not find add_detour in gdetour.pyd", "Error", 0);
		return false;
	}
	return imp_add_detour(address, overwrite_length, bytes_to_pop, type);
}
int gdetour::run_python_file(char* filename) {
	if (this->imp_run_python_file == NULL) {
		MessageBox(0,"Could not find imp_run_python_file in gdetour.pyd", "Error", 0);
		return false;
	}
	return imp_run_python_file(filename);
}
