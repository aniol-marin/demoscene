export module solid;

import std;
import definitions;
import timer;
import effect;
using namespace mole_def;

namespace MoleDemo
{
    export class Solid;
    /*
    export using SolidDeserializer = mole::pugi_wrapper::node<MoleDemo::Solid>;
     */
}

namespace MoleDemo
{
    class Solid final
      : public Texturable
      , public Effect
    {
        rgbaColor rgbColor;

    public:
        Solid() = default; // texturable-enforced constructor
        Solid(Timer* timer, Screen* screen);
        Solid(Solid&&) noexcept;
        ~Solid() override = default;

        void SetColor(Color color);

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetPixel(Point2D p) override;
        rgbaColor GetPixel(index_t index) override;
        rgbaColor GetMappedUV(CoordinateUV uv) override;
    };
}
