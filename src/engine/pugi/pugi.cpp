#include "pugi.h"

#include<string>

mole::pugi_wrapper::tree::tree(const std::string_view path)
{
	pugi::xml_parse_result result
	{
		document.load_file(std::string{path}.c_str())
	};

	tmp_success = bool{result};
}

int mole::pugi_wrapper::generic_node::get_number(std::string_view name)
{
	return node.attribute(name).as_int();
}

std::string mole::pugi_wrapper::generic_node::get_text(std::string_view name)
{
	std::string content
	{
		node.attribute(name).value()
	};

	return content;
}

mole::pugi_wrapper::generic_node mole::pugi_wrapper::tree::get_generic_node(std::string_view name)
{
	return generic_node { name, document.child(name) };
}

mole::pugi_wrapper::generic_node mole::pugi_wrapper::generic_node::get_child(std::string_view name)
{
	return generic_node{name, node.child(name) };
}

std::vector<mole::pugi_wrapper::generic_node> mole::pugi_wrapper::generic_node::get_children(std::string_view name)
{
	std::vector<mole::pugi_wrapper::generic_node> container {};

	for (const auto it : node)
	{
		if (name.compare(it.name()) == 0)
		{
			container.emplace_back(name, it);
		}
	}

	return container;
}

mole::pugi_wrapper::generic_node::generic_node( std::string_view name , const pugi::xml_node& node) :
	name { name }
	, node { node }
{
}

