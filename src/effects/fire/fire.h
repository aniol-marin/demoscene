#ifndef MOLE_SOLID_H
#define MOLE_SOLID_H

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

        void Load();
        void Unload();
        void Update(permille intensity, milliseconds delta);
        void Cache(StencilBuffer& mask);
        rgbaColor GetPixel(Point2D p);
        rgbaColor GetPixel(index_t index);
    };
}
#endif
