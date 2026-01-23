#ifndef MOLE_NOISE_H
#define MOLE_NOISE_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    using namespace mole_def;

    class RandomNoise
      : public Texturable
      , public Effect
    {
        ChannelBuffer noise;
        Color A, B;
        bunch repetitions;

    public:
        RandomNoise() = delete;
        RandomNoise(Timer* timer, Screen* screen);
        ~RandomNoise() override = default;

        void Set(Color a, Color b, bunch repetitions);

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetMappedUV(CoordinateUV uv) override;
    };
}
#endif
