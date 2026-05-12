#include "plasma.h"

#include <cmath>

namespace MoleDemo
{
    using namespace mole_def;

    Plasma::Plasma(Timer* timer, Screen* screen) : Effect(timer, screen) {}

    Plasma::~Plasma() {}

    void Plasma::Load()
    {
        buildPalette(0);
        for (unsigned int j = 0; j < get_screen()->h * 2; ++j)
        {
            for (unsigned int i = 0; i < get_screen()->w * 2; ++i)
            {
                plasma1.push_back((
                        channel) (64 +
                                  63 * (std::sin((double) std::hypot(get_screen()->h - j, get_screen()->w - i) / 16))));
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
        Windowx1 = (get_screen()->w / 2) +
                   (int) (((int) (get_screen()->w / 2) - 1) * std::cos((double) accumulatedTime / 970));
        Windowx2 = (get_screen()->w / 2) +
                   (int) (((int) (get_screen()->w / 2) - 1) * std::sin((double) -accumulatedTime / 1140));
        Windowy1 = (get_screen()->h / 2) +
                   (int) (((int) (get_screen()->h / 2) - 1) * std::sin((double) accumulatedTime / 1230));
        Windowy2 = (get_screen()->h / 2) +
                   (int) (((int) (get_screen()->h / 2) - 1) * std::cos((double) -accumulatedTime / 750));
        // we only select the part of the precalculated buffer that we need
        src1 = Windowy1 * (int) (get_screen()->w * 2) + Windowx1;
        src2 = Windowy2 * (int) (get_screen()->w * 2) + Windowx2;
    }

    void Plasma::Cache(StencilBuffer& mask)
    {
        int indexColor;
        for (unsigned short y = 0; y < get_screen()->h; y++)
        {
            for (unsigned short x = 0; x < get_screen()->w; x++)
            {

                indexColor = (plasma1[src1 % plasma1.size()] + plasma2[src2 % plasma2.size()]) % 256;
                PutPixel(Point2D{ x, y }, palette[indexColor].rgba());

                src1++;
                src2++;
            }
            // get the next line in the precalculated buffers
            src1 += get_screen()->w;
            src2 += get_screen()->w;
        }
    }

    void Plasma::buildPalette(unsigned short time)
    {
        for (int i = 0; i < 256; i++)
        {
            palette[i] = { (unsigned char) (128 + 127 * std::cos(i * PI / 128 + (double) time / 740)),
                           (unsigned char) (128 + 127 * std::sin(i * PI / 128 + (double) time / 630)),
                           (unsigned char) (128 - 127 * std::cos(i * PI / 128 + (double) time / 810)) };
        }
    }

    void Plasma::AssignTexture(Texturable* texture, Id id = 0)
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
