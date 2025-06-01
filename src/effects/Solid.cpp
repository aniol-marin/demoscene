export module solid;

import std.compat;
import definitions;
import timer;
import effect;
import pugi;

namespace MoleDemo
{
    export class Solid;
    export using SolidDeserializer = mole::pugi_wrapper::node<MoleDemo::Solid>;

}

struct mole::pugi_wrapper::node<MoleDemo::Solid>;

class MoleDemo::Solid final
  : public Texturable
  , public Effect
{
    rgbaColor rgbColor;

public:
    Solid(); // texturable-enforced constructor
    Solid(Timer* timer, Screen* screen);
    ~Solid() override;

    void SetColor(Color color);

    void Load() override;
    void Unload() override;
    void Update(permille intensity, milliseconds delta) override;
    void Cache(StencilBuffer& mask) override;
    rgbaColor GetPixel(Point2D p) override;
    rgbaColor GetPixel(index index) override;
    rgbaColor GetMappedUV(CoordinateUV uv) override;
};

namespace MoleDemo
{

    Solid::Solid() : Solid{ nullptr, &textureSize } {}

    Solid::Solid(Timer* timer, Screen* screen) : Texturable{}, Effect{ timer, screen } {}

    Solid::~Solid() {}

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

    rgbaColor Solid::GetPixel(index index)
    {
        return rgbColor;
    }

    rgbaColor Solid::GetMappedUV(CoordinateUV uv)
    {
        return rgbColor;
    }
}

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
