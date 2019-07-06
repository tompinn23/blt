#include "blt.h"

#define STUB_API \
	printf("API call: %s needs IMPLEMENTING\n", __func__);

int terminal_open() {
	STUB_API
	return 0;
}

void terminal_close() {
	STUB_API
}

int terminal_set8(const int8_t* s) {
	STUB_API
	return 0;
}

int terminal_set16(const int16_t* s) {
	STUB_API
	return 0;
}

int terminal_set32(const int32_t* s) {
	STUB_API
	return 0;
}

void terminal_color(color_t color) {
	STUB_API
}

void terminal_bkcolor(color_t color) {
	STUB_API
}

void terminal_composition(int mode) {
	STUB_API
}

void terminal_layer(int layer) {
	STUB_API
}
