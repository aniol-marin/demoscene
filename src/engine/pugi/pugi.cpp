module;

#include "pugixml.hpp"

export module pugi_wrapper;

import std;

export void Mock()
{
}

export bool Load(std::string_view path)
{
	pugi::xml_document document {};
	pugi::xml_parse_result result
	{
		document.load_file(std::string{path}.c_str())
	};

	return result;
}
