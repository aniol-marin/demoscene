#include "pugi.h"

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
	return node.attribute(std::string{name}.c_str()).as_int();
}

std::string mole::pugi_wrapper::generic_node::get_text(std::string_view name)
{
	std::string content
	{
		node.attribute(std::string{name}.c_str()).value()
	};

	return content;
}

mole::pugi_wrapper::generic_node mole::pugi_wrapper::tree::get_generic_node(std::string_view name)
{
	return generic_node{name, document.child(std::string{name}.c_str())};
}

/*
std::vector<mole::pugi_wrapper::generic_node> mole::pugi_wrapper::tree::generic_nodes()
{
	return {};
}
*/

mole::pugi_wrapper::generic_node::generic_node( std::string_view name , const pugi::xml_node& node) : name { name } , node { node }
{
}

