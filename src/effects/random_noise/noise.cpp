#include "noise.h"

#include <cmath>
#include <cstdlib>
#include <iostream> // temp

namespace MoleDemo
{
    using namespace mole_def;

    RandomNoise::RandomNoise(Timer* timer, Screen* screen) : Effect(timer, screen) {}

    void RandomNoise::Load()
    {
        Screen sampler(repetitions, repetitions);
        index_t samples((index_t) sampler.GetPixelCount());

        noise.clear();
        noise.assign(samples, 0x0);
        for (index_t i = 0; i < samples; ++i)
        {
            noise[i] = std::rand() % permilleFactor();
        }

        point1D period(std::max(static_cast<point1D>(get_screen()->w / repetitions), static_cast<point1D>(1)));
        for (point1D y = 0; y < get_screen()->h; ++y)
        {
            for (point1D x = 0; x < get_screen()->w; ++x)
            {

                index_t horizontal((x / period) % period);
                index_t right((horizontal + 1) % period);
                index_t vertical((y / period) % period);
                index_t down((vertical + 1) % period);

                permille offsetVertical((permille) (x % period));
                permille offsetHorizontal((permille) (y % period));

                std::cerr << "\ndeactivated logic at " << __FILE__ << "\n";
                exit(1);
                /*
                        Color base(A.lerp(B, noise[sampler.GetIndex((horizontal, vertical))]));
                        Color Right(A.lerp(B, noise[sampler.GetIndex((right, vertical))]));
                        Color Down(A.lerp(B, noise[sampler.GetIndex((horizontal, down))]));

                        Color sampled(base.lerp(Right, offsetVertical).lerp(Down, offsetVertical));

                        PutPixel(Point2D(x, y), sampled.rgba());
                */
            }
        }
    }

    void RandomNoise::Unload() {}

    void RandomNoise::Update(permille intensity, milliseconds delta) {}

    void RandomNoise::Cache(StencilBuffer& mask) {}

    void RandomNoise::Set(Color a, Color b, bunch repetitions)
    {
        this->A = a;
        this->B = b;
        this->repetitions = repetitions;
    }

    rgbaColor RandomNoise::GetMappedUV(CoordinateUV uv)
    {
        Point2D mapped(std::abs((int) (uv.u * permilleFactor() / get_screen()->w)) % get_screen()->w,
                       std::abs((int) (uv.v * permilleFactor() / get_screen()->h)) % get_screen()->h);
        return Effect::GetPixel(mapped);
    }
}
