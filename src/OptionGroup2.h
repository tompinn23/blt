#pragma once

#include <string>
#include <list>
#include <map>

struct OptionGroup {
	std::string name;
	std::map<std::string, std::string> attributes;
}

std::list<OptionGroup> ParseOptions(const std::string& s, bool semicolon_comments = false);
