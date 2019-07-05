#ifndef _BLT_H_
#define _BLT_H_

#include <stdint.h>

typedef uint32_t color_t

typedef struct dimensions_t_ {
	int width;
	int height;
} dimensions_t;


#if defined(BLT_BUILD_STATIC)
#	define BLT_API
#elif defined(_WIN32)
#	if defined(BLT_BUILDING_LIB)
#		define BLT_API __declspec(dllexport)
#   else
#      defined BLT_API __declspec(dllimport)
#   endif
#else
#   if defined(BLT_BUILDING_LIB) && __GNUC__ >= 4
#		define BLT_API __attribute__ ((visibility ("default")))  
#   else
#       defined BLT_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

BLT_API int terminal_open();
BLT_API void terminal_close();

BLT_API int terminal_set(const char* s);
BLT_API int terminal_setf(const char* s, ...);
BLT_API int terminal_wset(const wchar_t* s);
BLT_API int terminal_wsetf(const wchar_t* s, ...);

void terminal_color(color_t color);
void terminal_bkcolor(color_t color);

void terminal_composition(int mode);

void terminal_layer(int layer);

void terminal_clear();
void terminal_clear_area(int x, int y, int w, int h);

void terminal_crop(int x, int y, int w, int h);
void terminal_refresh();

void terminal_put(int x, int y, int code);
int terminal_pick(int x, int y, int index);

color_t terminal_pick_color(int x, int y, int index);
color_t terminal_pick_bkcolor(int x, int y);

void terminal_put_ext(int x, int y, int dx, int dy, int code, color_t* corners);


#ifdef __cplusplus
}
#endif

#endif //_BLT_H_
