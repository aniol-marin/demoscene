#include "pugi.h"

mole::pugi_wrapper::node::node(const std::string_view path)
{
	pugi::xml_parse_result result
	{
		document.load_file(std::string{path}.c_str())
	};

	tmp_success = bool{result};
}

bool mole::pugi_wrapper::Load(const std::string_view path)
{
	mole::pugi_wrapper::node wrapper {path};

	return wrapper;
}
