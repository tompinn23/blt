#include "blt.h"

int main(int argc, char** argv) {
	terminal_open();
	terminal_set("FLLML");
	wchar_t* s = L"OMOMP";
	terminal_wset(s);
	return 0;
}
