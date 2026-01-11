module;

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

export module tunnel;

import effect;
using namespace mole_def;

namespace MoleDemo
{
    export class Tunel;
}

namespace MoleDemo
{
    class Tunel
      : public Customizable
      , public Effect
    {
        long long accumulatedTime{};
        std::vector<channel> Tunel1;
        std::vector<Point2D> uv;
        int Windowx1, Windowy1, Windowx2, Windowy2;
        long src1, src2;
        Color palette[256];
        std::unique_ptr<Texturable> texture;

        permille du, dv, speedU, speedV;

        void buildPalette(std::uint16_t time);

    public:
        Tunel(Timer* timer, Screen* screen);
        ~Tunel() = default;

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        constexpr Id TextureLimit() const override { return 1; }
        void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
    };
}
