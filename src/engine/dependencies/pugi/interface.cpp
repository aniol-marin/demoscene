export module serialization;

import std;

namespace mole::pugi_wrapper
{
    export struct tree;
    export struct generic_node;
}

namespace mole::pugi_wrapper
{
    struct generic_node
    {
        using id_t = int;

    private:
        const id_t id{};
        const tree& m_tree;

    public:
        generic_node() = delete;
        generic_node(id_t a_id, const tree& a_tree);
        generic_node(const generic_node&) = delete;
        generic_node(generic_node&&) = default;
        virtual ~generic_node() = default;

        id_t get_id() const;
        std::string get_text(std::string_view attribute_name) const;
        int get_number(std::string_view attribute_name) const;

        generic_node get_child(const std::string_view name) const;
        std::vector<generic_node> get_children(std::string_view name) const;
    };

    struct tree
    {
        tree() = delete;
        explicit tree(std::filesystem::path path);
        tree(const tree&) = delete;
        tree(tree&&) = default;
        ~tree();

        [[nodiscard]] generic_node get_root_node(std::string_view name);
        [[nodiscard]] int get_number(const generic_node& node, std::string_view attribute_name) const;
        [[nodiscard]] std::string get_text(const generic_node& node, std::string_view attribute_name) const;
        [[nodiscard]] generic_node get_child(const generic_node& node, const std::string_view child_name) const;
        [[nodiscard]] std::vector<generic_node> get_children(const generic_node& node) const;
    };
}
