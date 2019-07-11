#include "blt.h"
#include "Console.h"
#include "utf8.h"
#include "log.h"
#include <vector>
/*
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE* __cdecl __iob_func(void)
{
	return _iob;
}
#endif
*/
#define STUB_API \
	printf("api call: %s needs IMPLEMENTING\n", __func__)

int terminal_open() {
	if (g_instance) {
		log_error("terminal_open: Already Initialized");
		return 0;
	}
	//Implement Config
	try {
		g_instance.reset(new Console());
		return 1;
	}
	catch (std::exception& e) {
		log_fatal("terminal_open: %s", e.what());
		return 0;
	}
}

void terminal_close() {
	if (g_instance) {
		g_instance.reset();
	}
}

int terminal_set8(const int8_t* s) {
	if (!s) {
		return -1;
	}
	g_instance->Set(std::string((char*)s));
	return 0;
}

int terminal_set16(const int16_t* s) {
	if (!s) {
		return -1;
	}
	const char16_t* s1 = (const char16_t*)s;
	std::string str;
	utf8::utf16to8(s1, s1 + std::char_traits<char16_t>::length(s1), std::back_inserter(str));
	g_instance->Set(str);
	return 0;
}

int terminal_set32(const int32_t* s) {
	if (!s) {
		return -1;
	}
	const char32_t* s1 = (const char32_t*)s;
	std::string str;
	utf8::utf32to8(s1, s1 + std::char_traits<char32_t>::length(s1), std::back_inserter(str));
	g_instance->Set(str);
	return 0;
}

void terminal_color(color_t color) {
	if (!g_instance) return;
	g_instance->SetFgColour(color);
}

void terminal_bkcolor(color_t color) {
	if (!g_instance) return;
	g_instance->SetBgColour(color);
}

void terminal_composition(int mode) {
	STUB_API;
}

void terminal_layer(int layer) {
	if (!g_instance) return;
	g_instance->SetLayer(layer);
}

void terminal_clear() {
	if (!g_instance) return;
	g_instance->ClearAll();
}

void terminal_clear_area(int x, int y, int w, int h) {
	if (!g_instance) return;
	g_instance->ClearArea(x, y, w, h);
}

void terminal_crop(int x, int y, int w, int h) {
	if (!g_instance) return;
	g_instance->Crop(x, y, w, h);
}

void terminal_refresh() {
	if (!g_instance) return;
	g_instance->Refresh();
}

void terminal_put(int x, int y, int code) {
	if (!g_instance) return;
	g_instance->PutChar(x, y, code);
}
void terminal_put_ext(int x, int y, int dx, int dy, int code, color_t* corners) {
	if (!g_instance) return;
	g_instance->PutCharExtended(x, y, dx, dy, code, corners);
}
int terminal_pick(int x, int y, int index) {
	if (!g_instance) return 0;
	return g_instance->Pick(x, y, index);
}
color_t terminal_pick_color(int x, int y, int index) {
	if (!g_instance) return 0;
	return g_instance->PickFgColour(x, y, index);
}
color_t terminal_pick_bkcolor(int x, int y) {
	if (!g_instance) return 0;
	return g_instance->PickBgColour(x, y);
}

void terminal_print_ext8(int x, int y, int width, int height, int align, const int8_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	return g_instance->PrintExt(x, y, width, height, align, std::string((const char*)s), out_w, out_h);
}
void terminal_print_ext16(int x, int y, int width, int height, int align, const int16_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	const char16_t* s1 = (const char16_t*)s;
	std::string utf8Str;
	utf8::utf16to8(s1, s1 + std::char_traits<char16_t>::length(s1), std::back_inserter(utf8Str));
	return g_instance->PrintExt(x, y, width, height, align, utf8Str, out_w, out_h);
}
void terminal_print_ext32(int x, int y, int width, int height, int align, const int32_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	const char32_t* s1 = (const char32_t*)s;
	std::string utf8Str;
	utf8::utf32to8(s1, s1 + std::char_traits<char32_t>::length(s1), std::back_inserter(utf8Str));
	return g_instance->PrintExt(x, y, width, height, align, utf8Str, out_w, out_h);
}
void terminal_measure_ext8(int width, int height, const int8_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	return g_instance->MeasureExt(width, height, std::string((const char*)s), out_w, out_h);
}
void terminal_measure_ext16(int width, int height, const int16_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	const char16_t* s1 = (const char16_t*)s;
	std::string utf8Str;
	utf8::utf16to8(s1, s1 + std::char_traits<char16_t>::length(s1), std::back_inserter(utf8Str));
	return g_instance->MeasureExt(width, height, utf8Str, out_w, out_h);
}
void terminal_measure_ext32(int width, int height, const int32_t* s, int* out_w, int* out_h) {
	if (!g_instance) return;
	const char32_t* s1 = (const char32_t*)s;
	std::string utf8Str;
	utf8::utf32to8(s1, s1 + std::char_traits<char32_t>::length(s1), std::back_inserter(utf8Str));
	return g_instance->MeasureExt(width, height, utf8Str, out_w, out_h);
}
int terminal_state(int slot) {
	if (!g_instance) return 0;
	return g_instance->State(slot);
}
int terminal_check(int slot) {
	return terminal_state(slot);
}
int terminal_has_input() {
	if (!g_instance) return 1;
	return g_instance->HasInput();
}
int terminal_read() {
	if (!g_instance) return TK_CLOSE;
	return g_instance->ReadInput();
}
int terminal_peek() {
	if (!g_instance) return TK_CLOSE;
	return g_instance->PeekInput();
}

int terminal_read_str8(int x, int y, int8_t* buffer, int max) {
	if (!g_instance) return TK_INPUT_CANCELLED;
	std::string buf;
	int ret = g_instance->ReadStr(x, y, &buf, max);
	if (ret >= 0) {
		memcpy(buffer, buf.data(), sizeof(char) * (buf.length() + 1));
	}
	return ret;	
}
int terminal_read_str16(int x, int y, int16_t* buffer, int max) {
	if (!g_instance) return TK_INPUT_CANCELLED;
	std::string buf;
	int ret = g_instance->ReadStr(x, y, &buf, max);
	if (ret >= 0) {
		std::vector<char16_t> utf16buf;
		utf8::utf8to16(buf.begin(), buf.end(), std::back_inserter(utf16buf));
		memcpy(buffer, utf16buf.data(), sizeof(char16_t) * (utf16buf.size() + 1));
	}
	return ret;
}
int terminal_read_str32(int x, int y, int32_t* buffer, int max) {
	if (!g_instance) return TK_INPUT_CANCELLED;
	std::string buf;
	int ret = g_instance->ReadStr(x, y, &buf, max);
	if (ret >= 0) {
		std::vector<char32_t> utf32buf;
		utf8::utf8to32(buf.begin(), buf.end(), std::back_inserter(utf32buf));
		memcpy(buffer, utf32buf.data(), sizeof(char32_t) * (utf32buf.size() + 1));
	}
	return ret;	
}
void terminal_delay(int period) {
	if (!g_instance) return;
	g_instance->Delay(period);
}
const int8_t* terminal_get8(const int8_t* key, const int8_t* default_) {
	STUB_API;
	return 0;
}
const int16_t* terminal_get16(const int16_t* key, const int16_t* default_) {
	STUB_API;
	return 0;
}
const int32_t* terminal_get32(const int32_t* key, const int32_t* default_) {
	STUB_API;
	return 0;
}
color_t color_from_name8(const int8_t* name) {
	if (!g_instance) return 0;
	return g_instance->ColorFromName(std::string((const char*)name));
}
color_t color_from_name16(const int16_t* name) {
	if (!g_instance) return 0;
	const char16_t* s1 = (const char16_t*)name;
	std::string utf8str;
	utf8::utf16to8(s1, s1 + std::char_traits<char16_t>::length(s1), std::back_inserter(utf8str));
	return g_instance->ColorFromName(utf8str);
}
color_t color_from_name32(const int32_t* name) {
	if (!g_instance) return 0;
	const char32_t* s1 = (const char32_t*)name;
	std::string utf8str;
	utf8::utf32to8(s1, s1 + std::char_traits<char32_t>::length(s1), std::back_inserter(utf8str));
	return g_instance->ColorFromName(utf8str);
}
color_t color_from_argb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue) {
	if (!g_instance) return 0;
	return red << 24 | green << 16 | blue << 8 | alpha;
}