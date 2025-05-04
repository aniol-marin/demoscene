#include "pugixml.hpp"

#include <string>
#include <string_view>


namespace mole::pugi_wrapper
{
	struct tree;
	struct generic_node;
	template<typename T>
		struct node;
}

namespace mole::pugi_wrapper
{
	struct tree
	{
		pugi::xml_document document {};
		bool tmp_success{};

		tree() = delete;
		tree(const std::string_view path);
		tree(const tree&) = delete;
		tree(tree&&) = default;
		~tree() = default;

		operator bool() const
		{
			return tmp_success;
		}

		int get_number(std::string_view name);
		std::string get_text(std::string_view name);
	};

	struct generic_node
	{
	};

	template<typename T>
	struct node
	{
	};
}
