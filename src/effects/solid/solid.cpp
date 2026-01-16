module solid;

import std;
import effect;

namespace MoleDemo
{
    using namespace mole_def;
    Solid::Solid(Timer* timer, Screen* screen) : Texturable{}, Effect{ timer, screen } {}
    Solid::Solid(Solid&& o) noexcept : Effect{ o.timer, o.screen }, rgbColor{ o.rgbColor } {}

    void Solid::Load() {}

    void Solid::Unload() {}

    void Solid::Update(permille intensity, milliseconds delta) {}

    void Solid::Cache(StencilBuffer& mask) {}

    void Solid::SetColor(Color color)
    {
        rgbColor = color.rgba();
    }

    rgbaColor Solid::GetPixel(Point2D p)
    {
        return rgbColor;
    }

    rgbaColor Solid::GetPixel(index_t index)
    {
        return rgbColor;
    }

    rgbaColor Solid::GetMappedUV(CoordinateUV uv)
    {
        return rgbColor;
    }
}

/*
template<>
struct mole::pugi_wrapper::node<MoleDemo::Solid>
{
    MoleDemo::Solid data;

    node() = delete ("dependency injection is required for the invariant");
    node(const pugi::xml_node& node, MoleDemo::Timer* timer, Screen* screen);
    node(const node&) = delete ("a single instance is allowed, move it instead");
    node(node&&) = default;
    ~node() = default;

    MoleDemo::Solid&& deserialize() { return std::move(data); }
};

mole::pugi_wrapper::node<MoleDemo::Solid>::node(const pugi::xml_node& node, MoleDemo::Timer* timer, Screen* screen) :
  data{ timer, screen }
{
    // TO DO preconditions and info filling

    mole::pugi_wrapper::generic_node content{ "Solid", node };
    rgbaColor color{ static_cast<rgbaColor>(content.get_number("color")) };
    data.SetColor(color);
}
 */
