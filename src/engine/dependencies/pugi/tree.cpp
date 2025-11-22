module serialization;

import std;
import pugixml_experimental;

namespace mole::pugi_wrapper
{
    static generic_node::id_t counter{};
    static std::map<tree*, pugi::xml_document> hidden_parse_trees{};
    static std::map<generic_node::id_t, pugi::xml_node> hidden_node_mapping{};

    tree::~tree()
    {
        hidden_parse_trees.erase(this);
    }

    tree::tree(const std::filesystem::path path)
    {
        pugi::xml_document document{};
        pugi::xml_parse_result result{ document.load_file(path.c_str()) };

        if (!result)
        {
            throw std::runtime_error{ std::string{ "invalid xml file path: " } + path.string() };
        }

        hidden_parse_trees[this] = std::move(document);
    }

    generic_node tree::get_root_node(std::string_view name)
    {
        auto pugi_node{ hidden_parse_trees.at(this).child(name) };
        generic_node node{ ++counter, *this };
        hidden_node_mapping[node.get_id()] = pugi_node;

        return node;
    }

    int tree::get_number(const generic_node& node, std::string_view attribute_name) const
    {
        auto& pugi_node{ hidden_node_mapping.at(node.get_id()) };
        return pugi_node.attribute(attribute_name).as_int();
    }

    std::string tree::get_text(const generic_node& node, std::string_view attribute_name) const
    {
        auto& pugi_node{ hidden_node_mapping.at(node.get_id()) };
        return pugi_node.attribute(attribute_name).as_string();
    }

    generic_node tree::get_child(const generic_node& node, const std::string_view child_name) const
    {
        auto pugi_node{ hidden_node_mapping.at(node.get_id()).child(child_name) };
        generic_node child{ ++counter, *this };
        hidden_node_mapping[child.get_id()] = pugi_node;

        return child;
    }

    std::vector<generic_node> tree::get_children(const generic_node& node) const
    {
        std::vector<generic_node> children{};
        pugi::xml_node pugi_node{ hidden_node_mapping.at(node.get_id()) };

        pugi::xml_node node_it{ pugi_node.first_child() };
        pugi::xml_node node_end{ pugi_node.last_child() };
        for (; node_it != node_end; node_it = node_it.next_sibling())
        {
            generic_node child{ ++counter, *this };
            hidden_node_mapping[child.get_id()] = node_it;
            children.emplace_back(std::move(child));
        }

        return children;
    }
}
