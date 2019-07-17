#include "BitmapTileset.h"
#include "lodepng.h"
#include "log.h"

#include "Config.h"
#include <charconv>

BitmapTileset::BitmapTileset(std::string bitmap, TileOrder ord, FontType typ) {
	unsigned w, h, error;
	bytevec buf;
	error = lodepng::decode(buf, w, h, bitmap);
	if (error) {
		log_error("PNG decode error: %s", lodepng_error_text(error));
		throw std::runtime_error(fmt::sprintf("PNG decode error: %s", lodepng_error_text(error)));
	}
	switch (ord) {
	case TileOrder::INCOL:
	case TileOrder::INROW:
		tileWidth = w / 16;
		tileHeight = h / 16;
		break;
	case TileOrder::LIBTCOD:
		tileWidth = w / 32;
		tileHeight = h / 8;
	}

	// Create Image with small initial PRIVATE_USE_AREA 
	tex = GPU_CreateImage(w, h + tileHeight * 3, GPU_FORMAT_RGBA);

	if (typ == FontType::STANDARD || typ == FontType::GREYSCALE) {
		uint32_t back_col;
		switch (ord) {
		case TileOrder::INCOL:
			int x = (w / 16) * 2;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		case TileOrder::INROW:
			int x = w * tileHeight * 2;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		case TileOrder::LIBTCOD:
			int x = 0;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		}
		uint32_t* pix_buf = (uint32_t*)& buf[0];
		for (int idx = 0; idx < w * h; idx++) {
			if (pix_buf[idx] == back_col) {
				pix_buf[idx] == 0x00000000;
			}
		}
	}
	// w * 4 as 4 bytes per pixel
	GPU_UpdateImageBytes(tex, &GPU_MakeRect( 0, 0, w, h ), buf.data(), w * 4);

	switch (ord) {
	case TileOrder::INCOL:
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {

			}
		}
	}

}

BitmapTileset::BitmapTileset(std::string memory_address, int buf_length, unsigned width, unsigned height, TileOrder ord, FontType typ) {
	unsigned char* buf = NULL;
	unsigned addr;
	auto result = std::from_chars(memory_address.data(), memory_address.data() + memory_address.size(), addr);
	if (result.ec == std::errc::invalid_argument) {
		throw std::invalid_argument("Failed to parse memory address");
	}
	buf = (unsigned char*)addr;
	switch (ord) {
	case TileOrder::INCOL:
	case TileOrder::INROW:
		tileWidth = width / 16;
		tileHeight = height / 16;
		break;
	case TileOrder::LIBTCOD:
		tileWidth = width / 32;
		tileHeight = height / 8;
	}

	// Create Image with small initial PRIVATE_USE_AREA 
	tex = GPU_CreateImage(width, height + tileHeight * 3, GPU_FORMAT_RGBA);

	if (typ == FontType::STANDARD || typ == FontType::GREYSCALE) {
		uint32_t back_col;
		switch (ord) {
		case TileOrder::INCOL:
			int x = tileWidth * 2;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		case TileOrder::INROW:
			int x = width * tileHeight * 2;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		case TileOrder::LIBTCOD:
			int x = 0;
			back_col = buf[x] << 24 | buf[x + 1] << 16 | buf[x + 2] << 8 | buf[x + 3];
			break;
		}
		uint32_t* pix_buf = (uint32_t*)& buf[0];
		for (int idx = 0; idx < width * height; idx++) {
			if (pix_buf[idx] == back_col) {
				pix_buf[idx] == 0x00000000;
			}
		}
	}
	// w * 4 as 4 bytes per pixel
	GPU_UpdateImageBytes(tex, &GPU_MakeRect(0, 0, width, height), buf, width * 4);

}

std::shared_ptr<TileInfo> BitmapTileset::Get(char32_t codepoint)
{
	return std::shared_ptr<TileInfo>();
}

bool BitmapTileset::Provides(char32_t codepoint)
{
	if(ord == TileOrder::INCOL || ord == TileOrder::INROW)
		return (codepoint >= 0 && codepoint <= 255);
	else {
		// NO STUPID TCOD LAYOUT 
		return (codepoint >= 32 && codepoint <= 126)
			|| (codepoint >= 176 && codepoint <= 179)
			|| (codepoint >= 185 && codepoint <= 188)
			|| (codepoint >= 192 && codepoint <= 197)
			|| (codepoint >= 200 && codepoint <= 206)
			|| (codepoint >= 217 && codepoint <= 223);
	}
}
