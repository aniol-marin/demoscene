module;

#include <cstdint>

export module plasma;

import std;
import effect;
import definitions;
import timer;

namespace MoleDemo
{
    export class Plasma;
}

class MoleDemo::Plasma
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
    void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
};

namespace MoleDemo
{
    Plasma::Plasma(Timer* timer, Screen* screen) : Effect{ timer, screen } {}

    Plasma::~Plasma() {}

    void Plasma::Load()
    {
        buildPalette(0);
        for (unsigned int j = 0; j < screen->h * 2; ++j)
        {
            for (unsigned int i = 0; i < screen->w * 2; ++i)
            {
                plasma1.push_back(
                        (channel) (64 + 63 * (std::sin((double) std::hypot(screen->h - j, screen->w - i) / 16))));
                plasma2.push_back(
                        (unsigned char) (64 + 63 * std::sin((float) i / (37 + 15 * std::cos((float) j / 74))) *
                                                      std::cos((float) j / (31 + 11 * std::sin((float) i / 57)))));
            }
        }
    }

    void Plasma::Unload() {}

    void Plasma::Update(permille intensity, milliseconds delta)
    {

        accumulatedTime += delta;
        // setup some nice colours, different every frame
        // this is a palette that wraps around itself, with different period sine
        // functions to prevent monotonous colours
        buildPalette(accumulatedTime / 10 + intensity);

        // move plasma with more sine functions :)
        Windowx1 = (screen->w / 2) + (int) (((int) (screen->w / 2) - 1) * std::cos((double) accumulatedTime / 970));
        Windowx2 = (screen->w / 2) + (int) (((int) (screen->w / 2) - 1) * std::sin((double) -accumulatedTime / 1140));
        Windowy1 = (screen->h / 2) + (int) (((int) (screen->h / 2) - 1) * std::sin((double) accumulatedTime / 1230));
        Windowy2 = (screen->h / 2) + (int) (((int) (screen->h / 2) - 1) * std::cos((double) -accumulatedTime / 750));
        // we only select the part of the precalculated buffer that we need
        src1 = Windowy1 * (int) (screen->w * 2) + Windowx1;
        src2 = Windowy2 * (int) (screen->w * 2) + Windowx2;
    }

    void Plasma::Cache(StencilBuffer& mask)
    {
        int indexColor;
        for (std::uint16_t y = 0; y < screen->h; y++)
        {
            for (std::uint16_t x = 0; x < screen->w; x++)
            {

                indexColor = (plasma1[src1 % plasma1.size()] + plasma2[src2 % plasma2.size()]) % 256;
                PutPixel(Point2D{ x, y }, palette[indexColor].rgba());

                src1++;
                src2++;
            }
            // get the next line in the precalculated buffers
            src1 += screen->w;
            src2 += screen->w;
        }
    }

    void Plasma::buildPalette(std::uint16_t time)
    {
        for (int i = 0; i < 256; i++)
        {
            palette[i] = { (unsigned char) (128 + 127 * std::cos(i * PI / 128 + (double) time / 740)),
                           (unsigned char) (128 + 127 * std::sin(i * PI / 128 + (double) time / 630)),
                           (unsigned char) (128 - 127 * std::cos(i * PI / 128 + (double) time / 810)) };
        }
    }

    void Plasma::AssignTexture(std::unique_ptr<Texturable> texture, Id id = 0)
    {
        switch (id)
        {
            case 0:
                break;
            case 1:
                break;
            default:
                throw;
                break;
        }
    }
}
