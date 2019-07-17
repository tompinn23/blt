#include "Console.h"
#include "OptionGroup2.h"
#include <charconv>
#include "utf8.h"

#define NONE 0x00
#define KEYBOARDMOUSE 0x01
#define KEYBOARD 0x02
#define MOUSE 0x03

std::unique_ptr<Console> g_instance;

using namespace BearLibTerminal;

Console::Console()
{
	main_thread_id = std::this_thread::get_id();
	SetOptions("window: size=80x25, icon=default; font: default; terminal.encoding=utf8; input.filter={keyboard}");
	//TODO: Implement Configuration File
}

#define THREAD_VIOLATIONS(ret) if (std::this_thread::get_id() != main_thread_id) { log_fatal("'%s' was not called from main thread.", __func__); return ret; }

int Console::Set(const std::string& options) {
	THREAD_VIOLATIONS(0);
	try {
		SetOptions(options);
	}
	catch(std::exception& e) {
		log_error("Failed to set options: %s", e.what());
	}
}

void Console::SetFgColour(color_t colour)
{
}

void Console::SetBgColour(color_t colour)
{
}

void Console::SetLayer(int layer)
{
}

void Console::ClearAll()
{
}

void Console::ClearArea(int x, int y, int w, int h)
{
}

void Console::Crop(int x, int y, int w, int h)
{
}

void Console::Refresh()
{
}

void Console::PutChar(int x, int y, int code)
{
}

void Console::PutCharExtended(int x, int y, int dx, int dy, int code, color_t* corners)
{
}

int Console::Pick(int x, int y, int index)
{
	return 0;
}

color_t Console::PickFgColour(int x, int y, int index)
{
	return color_t();
}

color_t Console::PickBgColour(int x, int y)
{
	return color_t();
}

void Console::PrintExt(int x, int y, int width, int height, int align, std::string str, int* out_w, int* out_h)
{
}

void Console::MeasureExt(int width, int height, std::string str, int* out_w, int* out_h)
{
}

int Console::State(int slot)
{
	return 0;
}

int Console::HasInput()
{
	return 0;
}

int Console::ReadInput()
{
	return 0;
}

int Console::PeekInput()
{
	return 0;
}

int Console::ReadStr(int x, int y, std::string* buffer, int max)
{
	return 0;
}

int Console::Delay(int period)
{
	return 0;
}

int Console::ColorFromName(const std::string& name)
{
	return 0;
}

int Console::SetOptions(std::string opts) {
	THREAD_VIOLATIONS(0);

	auto groups = ParseOptions(opts);

	for (auto& group : groups) {
		if (group.name == "window") {
			if (group.attributes.count("size")) {
				auto size = group.attributes["size"];
				auto delim = size.find('x');
				int width, height;
				auto result = std::from_chars(size.data(), size.data() + delim, width);
				if (result.ec == std::errc::invalid_argument) {
					throw std::invalid_argument("Failed to parse window width");
				}
				result = std::from_chars(size.data() + delim + 1, size.data() + size.size(), height);
				if (result.ec == std::errc::invalid_argument) {
					throw std::invalid_argument("Failed to parse window height");
				}
				window_size = { width, height };
			}
			if (group.attributes.count("title")) {
				title = group.attributes["title"];
			}
		}
		if (group.name == "input") {
			if (group.attributes.count("filter")) {
				auto filter = group.attributes["filter"];
				if (filter.find("keyboard+mouse") != std::string::npos) {
					input_filter = KEYBOARDMOUSE;
				}
				else if (filter.find("keyboard") != std::string::npos) {
					input_filter = KEYBOARD;
				}
				else if (filter.find("mouse") != std::string::npos) {
					input_filter = MOUSE;
				}
				else {
					input_filter = NONE;
				}
			}
		}
	}
}


