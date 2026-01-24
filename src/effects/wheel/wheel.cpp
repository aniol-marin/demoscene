#include "wheel.h"

#include <cmath>
#include <iostream> //temp

namespace MoleDemo
{
    using namespace mole_def;

    Wheel::Wheel(Timer* timer, Screen* screen) :
      color(0x000000FF), base(0x88, 0x88, 0x88), top(0xFFFFFFFF), Effect(timer, screen)
    {
    }

    void Wheel::Load()
    {
        rgbColor = 0x0;
    }

    void Wheel::Unload() {}

    void Wheel::Update(permille intensity, milliseconds delta)
    {
        rotation = (permille) (rotation + delta * permilleFactor() / 8192) % permilleFactor();
        SetColor();
        rgbColor = base.lerp(top, intensity).lerp(color, intensity).rgba();
    }

    void Wheel::Cache(StencilBuffer& mask) {}

    void Wheel::SetColor()
    {
        std::cerr << "\ndeactivated logic at " << __FILE__ << "\n";
        exit(1);
        /*
        double rad = rotation * permilleRad();
        color = Color((channel) (0x88 * std::sin(rad) / 2 + 0x88),
                      (channel) (0x88 * std::cos(rad) / 2 + 0x88),
                      (channel) (0x88 * std::sin(PI + rad) / 2 + 0x88));
         */
    }

    rgbaColor Wheel::GetPixel(Point2D p)
    {
        return rgbColor;
    }

    rgbaColor Wheel::GetPixel(index_t index)
    {
        return rgbColor;
    }
}
