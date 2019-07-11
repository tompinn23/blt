#pragma once

#include "Options.h"
#include "blt.h"

#include "SDL.h"
#include <thread>
#include <string>
#include <memory>

class Console {
public:
	Console();
	int Set(std::string& options);
	void SetFgColour(color_t colour); 
	void SetBgColour(color_t colour);
	void SetLayer(int layer);
	void ClearAll();
	void ClearArea(int x, int y, int w, int h);
	void Crop(int x, int y, int w, int h);
	void Refresh();
	void PutChar(int x, int y, int code);
	void PutCharExtended(int x, int y, int dx, int dy, int code, color_t* corners);
	void Pick(int x, int y, int index);
	void PickFgColour(int x, int y, int index);
	void PickBgColour(int x, int y);
	void PrintExt(int x, int y, int width, int height, int align, std::string str, int* out_w, int* out_h);
	void MeasureExt(int width, int height, std::string str, int* out_w, int* out_h);
	int State(int slot);
	int HasInput();
	int ReadInput();
	int PeekInput();
	int ReadStr(int x, int y, std::string* buffer, int max);
	int Delay(int period);
	int ColorFromName(std::string& name);
private:
	int SetOptions(std::string opts);
	std::thread::id main_thread_id;

	BearLibTerminal::Options opt;

};

extern std::unique_ptr<Console> g_instance;