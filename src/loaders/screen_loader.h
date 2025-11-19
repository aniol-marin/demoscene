#include "definitions.h"
#include "pugi.h"

namespace MoleDemo
{
	template<>
	struct mole::pugi_wrapper::node<Screen> : mole::pugi_wrapper::generic_node
	{
		Screen data{};

		node() : generic_node{}
		{
		}
		node() : generic_node{std::string_view path}
		{
			mole::pugi_wrapper::tree tree {path};
			mole::pugi_wrapper::generic_node content { tree.get_generic_node("screen") };
			data.w = { content.get_number( "width" ) };
			data.h = { content.get_number( "height" ) };
		
		}
		node(const pugi::xml_node& node)
			: generic_node{}
		{
			mole::pugi_wrapper::generic_node content { "screen", node };
			data.w = { content.get_number( "width" ) };
			data.h = { content.get_number( "height" ) };
		}
		node(const generic_node&)
			: generic_node{}
		{
		}
		node(const node&) = delete;
		node(const node&&) = delete;
		~node() override = default;

		const Screen& deserialize() const
		{
			return data;
		}
	};
}

