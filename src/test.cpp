#include "blt.h"

int main() {
	terminal_open();
	terminal_set("FLLML");
	wchar_t* s = L"OMOMP";
	terminal_wset(s);
}
