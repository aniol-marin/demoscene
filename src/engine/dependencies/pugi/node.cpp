#include "pugi.h"

namespace mole::pugi_wrapper
{
	generic_node::generic_node(id_t a_id, const tree& a_tree) : id{ a_id }, m_tree{ a_tree } {}

	generic_node::id_t generic_node::get_id() const
	{
		return id;
	}

	int generic_node::get_number(std::string_view attribute_name) const
	{
		return m_tree.get_number(*this, attribute_name);
	}

	std::string generic_node::get_text(std::string_view attribute_name) const
	{
		return m_tree.get_text(*this, attribute_name);
	}

	generic_node generic_node::get_child(const std::string_view child_name) const
	{
		return m_tree.get_child(*this, child_name);
	}

	std::vector<generic_node> generic_node::get_children(std::string_view name) const
	{
		return m_tree.get_children(*this);
	}
}

