#ifndef MOLE_FIRE_H
#define MOLE_FIRE_H

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    class Fire : public Effect
    {
        PixelBuffer firstBuffer;
        PixelBuffer secondBuffer;
        std::vector<Color> palette;

        void GeneratePalette();
        void GenerateHotspots(PixelBuffer& buffer, permille intensity);
        void FilterPrevious(PixelBuffer& src, PixelBuffer& dest, milliseconds delta, permille intensity);

    public:
        Fire(Timer* timer, Screen* screen);
        ~Fire();

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetPixel(Point2D p) override;
        rgbaColor GetPixel(index_t index) override;
    };
}
#endif
