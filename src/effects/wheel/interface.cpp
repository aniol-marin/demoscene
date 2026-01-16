export module wheel;

import std;
import effect;

namespace MoleDemo
{
    export class Wheel;
}

namespace MoleDemo
{
    using namespace mole_def;

    class Wheel : public Effect
    {
        Color color;
        Color base;
        Color top;
        rgbaColor rgbColor;
        double rotation;
        void SetColor();

    public:
        Wheel(Timer* timer, Screen* screen);
        ~Wheel() override = default;

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetPixel(Point2D p) override;
        rgbaColor GetPixel(index_t index) override;
    };
}
