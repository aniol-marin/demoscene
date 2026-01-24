#ifndef MOLE_GRADIENT_H
#define MOLE_GRADIENT_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    using namespace mole_def;

    class Gradient
      : public Texturable
      , public Effect
    {
        Color NE, NW, SW, SE;

    public:
        Gradient() = delete;
        Gradient(Timer* timer, Screen* screen);
        ~Gradient() = default;

        void SetColors(Color NE, Color NW, Color SW, Color SE);

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetMappedUV(CoordinateUV uv) override;
    };
}
#endif
