#pragma once

#include "Tileset.h"
#include <string>

enum class TileOrder {
	INROW,
	INCOL,
	LIBTCOD,
};

enum class FontType {
	STANDARD,
	ALPHA_32,
	GREYSCALE
};

class BitmapTileset : public Tileset {
public:
	BitmapTileset(std::string bitmap, TileOrder ord = TileOrder::INROW, FontType typ = FontType::STANDARD);
	BitmapTileset(std::string memory_address, int buffer_length, unsigned width, unsigned height, TileOrder ord = TileOrder::INROW, FontType typ = FontType::STANDARD);
	std::shared_ptr<TileInfo> Get(char32_t codepoint);
	bool Provides(char32_t codepoint);
private:
	GPU_Image* tex;
	int tileWidth;
	int tileHeight;
	FontType typ;
	TileOrder ord;
};