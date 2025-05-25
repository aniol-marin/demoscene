export module pugi;

import std;
export import pugixml;

namespace mole::pugi_wrapper
{
	export struct generic_node;
	export struct tree;
	export template<typename T>
	struct node;
}

namespace mole::pugi_wrapper
{
	struct generic_node
	{
		const std::string_view name{};
			/*

		const pugi::xml_node node{};
		*/

		generic_node() = default; // temp
		generic_node(std::string_view name, const pugi::xml_node& node);
		generic_node(const generic_node&) = default;
		generic_node(generic_node&&) = default;
		virtual ~generic_node() = default;

		std::string get_text(std::string_view name);
		int get_number(std::string_view name);

		generic_node get_child(std::string_view name);
		std::vector<generic_node> get_children(std::string_view name);


		/*
	protected:
		generic_node() = default;
		*/
	};

	struct tree
	{
		/*
		pugi::xml_document document {};
		*/
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

mole::pugi_wrapper::tree::tree(const std::string_view path)
{
	pugixml::mole_test{};
	pugi::another_mole_test{};

	/*
	pugi::xml_parse_result result
	{
		document.load_file(std::string{path}.c_str())
	};

	tmp_success = bool{result};
	*/
}

int mole::pugi_wrapper::generic_node::get_number(std::string_view name)
{
	return 0;
	/*
	return node.attribute(name).as_int();
	*/
}

std::string mole::pugi_wrapper::generic_node::get_text(std::string_view name)
{
	std::string content
	{
		"temp"
				/*
		node.attribute(name).value()
		*/
	};

	return content;
}

mole::pugi_wrapper::generic_node mole::pugi_wrapper::tree::get_generic_node(std::string_view name)
{
	return mole::pugi_wrapper::generic_node{};

	/*
	return generic_node { name, document.child(name) };
	*/
}

mole::pugi_wrapper::generic_node mole::pugi_wrapper::generic_node::get_child(std::string_view name)
{
	return {};
		/*

	return generic_node{name, node.child(name) };
	*/
}

std::vector<mole::pugi_wrapper::generic_node> mole::pugi_wrapper::generic_node::get_children(std::string_view name)
{
	std::vector<mole::pugi_wrapper::generic_node> container {};

		/*

	for (const auto it : node)
	{
		if (name.compare(it.name()) == 0)
		{
			container.emplace_back(name, it);
		}
	}
	*/

	return container;
}

mole::pugi_wrapper::generic_node::generic_node( std::string_view name , const pugi::xml_node& node) :
	name { name }
		/*
	, node { node }
	*/
{
}

