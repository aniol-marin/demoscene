export module serialization;

import std;
export import pugixml_experimental;

namespace mole::pugi_wrapper
{
	export struct generic_node;
	export struct tree;
	export template<typename T>
	struct node;
}

namespace mole::pugi_wrapper
{
	template<typename T>
	struct node
	{
		node()
		{
			// only specializations are allowed
			throw std::exception{};
		}
		node(const pugi::xml_node& node)
		{
			// only specializations are allowed
			throw std::exception{};
		}
		node(const generic_node& other)
		{
			// only specializations are allowed
			throw std::exception{};
		}
		node(const node&) = delete;
		node(const node&&) = delete;
		~node() = default;
	};
}

