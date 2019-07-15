#include "Console.h"
#include "OptionGroup.h"

#include "utf8.h"

std::unique_ptr<Console> g_instance;

using namespace BearLibTerminal;

Console::Console()
{
	main_thread_id = std::this_thread::get_id();
	SetOptions("window: size=80x25, icon=default; font: default; terminal.encoding=utf8; input.filter={keyboard}");
	//TODO: Implement Configuration File
}

#define THREAD_VIOLATIONS(ret) if (std::this_thread::get_id() != main_thread_id) { log_fatal("'%s' was not called from main thread.", __func__); return ret; }

int Console::Set(std::string& options) {
	THREAD_VIOLATIONS(0);
	try {
		SetOptions(options);
	}
	catch(std::exception& e) {
		log_error("Failed to set options: %s", e.what());
	}
}

int Console::SetOptions(std::string opts) {
	THREAD_VIOLATIONS(0);
	std::string::iterator it = opts.begin();
	int cp = utf8::next(it, opts.end());
	std::wstring wstr;
	while (it != opts.end()) {
		wstr.append(cp);
	}
	auto groups = ParseOptions2(opts);
}
