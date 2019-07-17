#pragma once

#include "Rect.h"
#include "SDL_gpu.h"

#include <vector>
#include <memory>

typedef std::vector<unsigned char> bytevec;

struct TileInfo {
	int texIndex;
	Rect clip;
	GPU_Image* tex;
};

class Tileset {
	virtual std::shared_ptr<TileInfo> Get(char32_t codepoint);
	virtual bool Provides(char32_t codepoint);
};