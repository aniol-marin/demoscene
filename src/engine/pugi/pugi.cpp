module;

#include "pugixml.hpp"

export module pugi_wrapper;

import std;

namespace mole::pugi_wrapper
{
	export struct node;
	using maybe_node = std::optional<node>;

	export bool Load(std::string_view path);
}

struct mole::pugi_wrapper::node
{
	bool tmp_success{};

	node() = delete;
	node(const std::string_view path)
	{
		pugi::xml_document document {};
		pugi::xml_parse_result result
		{
			document.load_file(std::string{path}.c_str())
		};

		tmp_success = bool{result};
	}
	node(const node&) = delete;
	node(node&&) = default;
	~node() = default;

	operator bool() const
	{
		return tmp_success;
	}
};

bool mole::pugi_wrapper::Load(const std::string_view path)
{
	node wrapper {path};

	return wrapper;
}
