#include "pugixml.hpp"

#include <string_view>


namespace mole::pugi_wrapper
{
	bool Load(std::string_view path);
	/*
	 struct node;

	 }

	 struct mole::pugi_wrapper::node
	 */
	struct node
	{
		pugi::xml_document document {};
		bool tmp_success{};

		node() = delete;
		node(const std::string_view path);
		node(const node&) = delete;
		node(node&&) = default;
		~node() = default;

		operator bool() const
		{
			return tmp_success;
		}
	};
}
