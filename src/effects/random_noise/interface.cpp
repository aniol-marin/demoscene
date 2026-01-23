export module noise;

import std;
import effect;

namespace MoleDemo
{
    export class RandomNoise;
}

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
