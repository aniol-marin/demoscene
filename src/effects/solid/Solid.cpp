#include "solid.h"

#include <cstdlib>
#include <functional>

/*
import serialization;

struct mole::pugi_wrapper::node<MoleDemo::Solid>;
 */

namespace MoleDemo
{
    /*
    Solid::Solid()
        : Texturable	(		)
        , Effect		( NULL, NULL )
    {
    }
     */

    Solid::Solid(Timer* timer, Screen* screen) : Texturable(), Effect(timer, screen) {}

    Solid::Solid(const Solid& o) : Effect(o.timer, o.screen), rgbColor(o.rgbColor) {}

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

    node() = delete;
    node(const pugi::xml_node& node, MoleDemo::Timer* timer, Screen* screen);
    node(const node&) = delete;
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
