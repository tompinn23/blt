#pragma once

#include "SDL_gpu.h"

struct Rect {
	int x; 
	int y;
	int width;
	int height;
	operator GPU_Rect() {
		return GPU_MakeRect((float)x, (float)y, (float)width, (float)height);
	}

	operator SDL_Rect() {
		SDL_Rect ret = { x, y, width, height };
		return ret;
	}
};