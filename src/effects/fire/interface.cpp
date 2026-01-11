module;

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

export module fire;

import effect;
using namespace mole_def;

namespace MoleDemo
{
    export class Fire;
}

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
