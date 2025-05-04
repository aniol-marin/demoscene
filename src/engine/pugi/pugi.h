#include "pugixml.hpp"

#include <exception>
#include <string>
#include <vector>
#include <string_view>


namespace mole::pugi_wrapper
{
	struct generic_node;
	struct tree;
	/*
	template<typename T>
	struct node;
	*/
}

namespace mole::pugi_wrapper
{
	struct generic_node
	{
		const std::string_view name{};
		const pugi::xml_node node;

		generic_node() = delete;
		generic_node( std::string_view name , const pugi::xml_node& node);
		generic_node(const generic_node&) = delete;
		generic_node(generic_node&&) = default;
		virtual ~generic_node() = default;

		std::string get_text(std::string_view name);
		int get_number(std::string_view name);
	};

	/*
	template<typename T>
	struct node: generic_node
	{
		node() = delete;
		node(const node&) = delete;
		node(const generic_node&)
		{
			// only specializations are allowed
			throw std::exception{};
		}
		node(const node&&)
		{
			// only specializations are allowed
			throw std::exception{};
		}
		~node() override = default;
	};

*/
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

		generic_node get_generic_node(std::string_view name);
		/*
		std::vector<generic_node> generic_nodes();
		*/
	};
}

