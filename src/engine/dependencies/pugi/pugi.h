#ifndef MOLE_PUGI_WRAPPER_H
#define MOLE_PUGI_WRAPPER_H

#include "pugixml.hpp"
#include <vector>

namespace mole::pugi_wrapper
{
    struct generic_node
    {
        const std::string_view name{};
        const pugi::xml_node node{};

        generic_node(std::string_view name, const pugi::xml_node& node);
        generic_node(const generic_node&) = default;
        generic_node(generic_node&&) = default;
        virtual ~generic_node() = default;

        std::string get_text(std::string_view name);
        int get_number(std::string_view name);

        generic_node get_child(std::string_view name);
        std::vector<generic_node> get_children(std::string_view name);

    protected:
        generic_node() = default;
    };

    struct tree
    {
        pugi::xml_document document{};
        bool tmp_success{};

        tree() = delete;
        explicit tree(std::string_view path);
        tree(const tree&) = delete;
        tree(tree&&) = default;
        ~tree() = default;

        operator bool() const { return tmp_success; }

        generic_node get_generic_node(std::string_view name);
    };

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

#endif
