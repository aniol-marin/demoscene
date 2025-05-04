#include "pugi.h"

mole::pugi_wrapper::tree::tree(const std::string_view path)
{
	pugi::xml_parse_result result
	{
		document.load_file(std::string{path}.c_str())
	};

	tmp_success = bool{result};
}

int mole::pugi_wrapper::tree::get_number(std::string_view name)
{
	return document.child("test").attribute(std::string{name}.c_str()).as_int();
}

std::string mole::pugi_wrapper::tree::get_text(std::string_view name)
{
	std::string content
	{
		document.child("test").attribute(std::string{name}.c_str()).value()
	};

	return content;
}
