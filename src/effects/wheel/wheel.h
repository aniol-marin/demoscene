#ifndef MOLE_WHEEL_H
#define MOLE_WHEEL_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

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
#endif
