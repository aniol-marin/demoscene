#ifndef MOLE_PLASMA_H
#define MOLE_PLASMA_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    using namespace mole_def;

    class Plasma
      : public Customizable
      , public Effect
    {
        long long accumulatedTime{};
        std::vector<channel> plasma1;
        std::vector<channel> plasma2;
        int Windowx1, Windowy1, Windowx2, Windowy2;
        long src1, src2;
        Color palette[256];

        void buildPalette(std::uint16_t time);

    public:
        Plasma(Timer* timer, Screen* screen);
        ~Plasma();

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        constexpr Id TextureLimit() const override { return 2; }
        void AssignTexture(Texturable* texture, Id id) override;
    };
}
#endif
