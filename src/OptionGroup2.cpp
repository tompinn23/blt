#include "OptionGroup2.h"
#include "utf8.h"
#include "utf82.h"
#include <vector>

static bool isquote(char c)
{
	return c == '\'' || c == '"' || c == '[' || c == '{';
}

static char get_closing_quote(char c)
{
	switch (c)
	{
	case '[':  return ']';
	case '{':  return '}';
	default:    return c;
	}
}

std::list<OptionGroup> ParseOptions(const std::string& s, bool semicolon_comments) {
	std::list<OptionGroup> result;
	std::map<std::string, decltype(result.begin())> lookup;
	const char* p = s.c_str();

	auto keep_property2 = [&](std::string name, std::string value)
	{
		// a       --> [a] ''       font.''
		// a.b     --> [a] b        window.title
		// a.b.c   --> [a.b] c      ini.custom.property
		// a.b.c.d --> [a.b] c.d    ini.bearlibterminal.window.title

		std::string section_name = "_";

		size_t first_period_pos = name.find('.');
		if (first_period_pos == std::wstring::npos)
		{
			// Nameless property.
			section_name.swap(name);
		}
		else
		{
			size_t second_period_pos = name.find('.', first_period_pos + 1);
			size_t section_end = (second_period_pos == std::string::npos) ? first_period_pos : second_period_pos;

			if (section_end == 0 || section_end == name.length() - 1)
			{
				// Surely invalid.
				return;
			}

			section_name = name.substr(0, section_end);
			name = name.substr(section_end + 1);
		}

		auto i = lookup.find(section_name);
		if (i == lookup.end())
		{
			result.emplace_back();
			i = lookup.insert({ section_name, (--result.end()) }).first;
			i->second->name = section_name;
		}
		i->second->attributes[name] = value;
	};

	while (*p != '\0') {
		auto name = read_until(p, ":=;");

		if (*p == '=') {
			p++;
			keep_property2(name, read_until(p, ";"));
		}
		else if (*p == ':') {
			// Grouped property.
			while (*p != '\0' && *p != ';') {
				p++;
				auto subname = read_until(p,"=,;");
				if (*p == '=') {
					// Regular subproperty.
					p++;
					keep_property2(name + "." + subname, read_until(p, ",;"));
				}
				else if (*p == ',' || *p == ';' || *p == '\0') {
					// Nameless subproperty (both continued or finale).
					keep_property2(name, subname);
				}
			}
		}
		else if (*p == ';') {
			if (semicolon_comments)
				break;
			// Discard.
			p++;
		}
		else {
			// Whatever.
			break;
		}
	}
	return result;
}


std::string read_until(const char*& p, const std::string& until) {
	std::string space;
	std::string value;
	char closing_qoute = 0;

	while (*p != '\0' && (closing_qoute || until.find(*p) == std::string::npos)) {
		//consume \n and \r
		if (*p == '\n' || *p == '\r') {

		}
		else if (std::isspace(*p) && !closing_qoute)
		{
			space += *p;
		}
		else if (*p == closing_qoute)
		{
			if (*(p + 1) == closing_qoute) {
				// Escaped quote
				value += *p++; 
			}
			else {
				// End of quoted string.
				closing_qoute = 0;
			}
		}
		else if (isquote(*p) && !closing_qoute && value.empty()) {
			closing_qoute = get_closing_quote(*p);
			space.clear();
		}
		else {
			if (!value.empty()) {
				value += space;
			}
			space.clear();
			value += *p;
		}
		p++;
	}
	return value;
}