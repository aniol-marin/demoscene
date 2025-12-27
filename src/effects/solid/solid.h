#ifndef MOLE_SOLID_H
#define MOLE_SOLID_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

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
#endif
