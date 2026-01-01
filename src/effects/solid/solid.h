#ifndef MOLE_SOLID_H
#define MOLE_SOLID_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    class Solid
      : public Texturable
      , public Effect
    {
        rgbaColor rgbColor;

    public:
	/*
        Solid(); // texturable-enforced constructor
	 */
        Solid(Timer* timer, Screen* screen);
        Solid(const Solid&);
        ~Solid() {}

        void SetColor(Color color);

        void Load();
        void Unload();
        void Update(permille intensity, milliseconds delta);
        void Cache(StencilBuffer& mask);
        rgbaColor GetPixel(Point2D p);
        rgbaColor GetPixel(index_t index);
        rgbaColor GetMappedUV(CoordinateUV uv);
    };
}
#endif
