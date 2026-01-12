#include "fire.h"

#include <cmath>
#include <cstdlib>
#include <memory>
#include <vector>

namespace MoleDemo
{
    Fire::Fire(Timer* timer, Screen* screen) : Effect(timer, screen) {}

    Fire::~Fire() {}

    void Fire::Load()
    {
        std::srand(0);

        firstBuffer.assign(get_screen()->w * (get_screen()->h + 4), 0x0);
        secondBuffer.assign(get_screen()->w * (get_screen()->h + 4), 0x0);

        palette.assign(256, 0x0);
        GeneratePalette();
    }

    void Fire::Unload() {}

    void Fire::Update(permille intensity, milliseconds delta)
    {
        std::swap(firstBuffer, secondBuffer);
        GenerateHotspots(secondBuffer, intensity);
        FilterPrevious(secondBuffer, firstBuffer, delta, intensity);
    }

    void Fire::Cache(StencilBuffer& mask) {}

    void Shade_Pal(std::vector<Color>& palette, int s, int e, int r1, int g1, int b1, int r2, int g2, int b2)
    {
        int i;
        float k;
        for (i = 0; i <= e - s; i++)
        {
            k = (float) i / (float) (e - s);
            palette[s + i] = Color(
                    (channel) (r1 + (r2 - r1) * k), (channel) (g1 + (g2 - g1) * k), (channel) (b1 + (b2 - b1) * k));
        }
    }

    void Fire::GeneratePalette()
    {
        Shade_Pal(palette, 0, 23, 0, 0, 0, 32, 0, 64);
        Shade_Pal(palette, 24, 47, 32, 0, 64, 255, 0, 0);
        Shade_Pal(palette, 48, 63, 255, 0, 0, 255, 255, 0);
        Shade_Pal(palette, 64, 127, 255, 255, 0, 255, 255, 255);
        Shade_Pal(palette, 128, 255, 255, 255, 255, 255, 255, 255);
    }

    void Fire::GenerateHotspots(PixelBuffer& buffer, permille intensity)
    {

        unsigned char newFires = 1 + intensity / 32;

        for (int f = 0; f < newFires; ++f)
        {
            point1D start(std::rand() % get_screen()->w);
            point1D end(std::min(start + (point1D) (std::rand() % (1 + intensity / 32)), get_screen()->w - 3));
            rgbaColor random;
            index_t paletteStart(std::rand() % palette.size());
            for (int i = start; i < end; ++i)
            {

                index_t i1(get_screen()->GetIndex(Point2D((point1D) i, (point1D) (get_screen()->h + 1))));
                index_t i2(get_screen()->GetIndex(Point2D((point1D) i, (point1D) (get_screen()->h + 2))));
                index_t i3(get_screen()->GetIndex(Point2D((point1D) i, (point1D) (get_screen()->h + 3))));

                random = Color(0xFFFFFFFF).lerp(palette[std::rand() % palette.size()], std::rand() % 1000).rgba();
                buffer[i1] = random;
                buffer[i2] = random;
                buffer[i3] = random;
            }
        }
    }

    void Fire::FilterPrevious(PixelBuffer& src, PixelBuffer& dest, milliseconds delta, permille intensity)
    {
        Color NW;
        Color N;
        Color NE;
        Color E;
        Color SE;
        Color S;
        Color SW;
        Color W;
        rgbaColor blurred;
        for (point1D y = (point1D) (get_screen()->h / 2); y < get_screen()->h + 3; ++y)
        {
            for (point1D x = 1; x < get_screen()->w - 1; ++x)
            {

                NE = (GetColorAt(Point2D(x + 1, y - 1), src));
                N = (GetColorAt(Point2D(x, y - 1), src));
                NW = (GetColorAt(Point2D(x - 1, y - 1), src));
                W = (GetColorAt(Point2D(x - 1, y), src));
                SW = (GetColorAt(Point2D(x - 1, y + 1), src));
                S = (GetColorAt(Point2D(x, y + 1), src));
                SE = (GetColorAt(Point2D(x + 1, y + 1), src));
                E = (GetColorAt(Point2D(x + 1, y), src));

                permille part = permilleFactor() / static_cast<permille>(16);
                blurred = S.lerp(E, part)
                                  .lerp(W, part)
                                  .lerp(SE, part)
                                  .lerp(SW, part)
                                  /*
                                  .lerp(N, part)
                                  .lerp(NW, part)
                                  .lerp(NE, part)
                                  */
                                  .rgba();

                PutPixel(Point2D(x, y), blurred, dest);
            }
        }

        for (point1D y = get_screen()->h; y < get_screen()->h + 3; ++y)
        {
            for (point1D x = 1; x < get_screen()->w - 1; ++x)
            {
                Color original(GetColorAt(Point2D(x, y), dest));
                Color matte(0x000000FF);
                PutPixel(Point2D(x, y), original.lerp(matte, 300).rgba(), dest);
            }
        }
    }

    rgbaColor Fire::GetPixel(Point2D p)
    {
        return GetColorAt(p, firstBuffer);
    }

    rgbaColor Fire::GetPixel(index_t index)
    {
        return firstBuffer[index];
    }
}
