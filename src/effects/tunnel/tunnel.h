#ifndef MOLE_SOLID_H
#define MOLE_SOLID_H

#include <vector>
#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    class Tunel
      : public Customizable
      , public Effect
    {
        long long accumulatedTime;
        std::vector<channel> Tunel1;
        std::vector<Point2D> uv;
        int Windowx1, Windowy1, Windowx2, Windowy2;
        long src1, src2;
        Color palette[256];
        Texturable* texture;

        permille du, dv, speedU, speedV;

        void buildPalette(short int time);

    public:
        Tunel(Timer* timer, Screen* screen);
        ~Tunel() {}

        void Load();
        void Unload();
        void Update(permille intensity, milliseconds delta);
        void Cache(StencilBuffer& mask);
        Id TextureLimit() const { return 1; }
        void AssignTexture(Texturable* texture, Id id);
	rgbaColor GetMappedUV(CoordinateUV uv);
    };
}
#endif
