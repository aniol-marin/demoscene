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
		node(const pugi::xml_node& node)
			: generic_node{}
		{
			mole::pugi_wrapper::generic_node content { "child", node };
			data.number = { content.get_number( "number" ) };
			data.word = { content.get_text( "word" ) };
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

