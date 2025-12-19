export module noise;

import std;
import effect;
import definitions;
import timer;

namespace MoleDemo
{
    export class RandomNoise;
}

class MoleDemo::RandomNoise
  : public Texturable
  , public Effect
{
    ChannelBuffer noise;
    Color A, B;
    bunch repetitions;

public:
    RandomNoise();
    RandomNoise(Timer* timer, Screen* screen);
    ~RandomNoise();

    void Set(Color a, Color b, bunch repetitions);

    void Load() override;
    void Unload() override;
    void Update(permille intensity, milliseconds delta) override;
    void Cache(StencilBuffer& mask) override;
    rgbaColor GetMappedUV(CoordinateUV uv) override;
};
namespace MoleDemo
{

    RandomNoise::RandomNoise() : RandomNoise{ nullptr, &textureSize } {}

    RandomNoise::RandomNoise(Timer* timer, Screen* screen) : Effect{ timer, screen } {}

    RandomNoise::~RandomNoise() {}

    void RandomNoise::Load()
    {

        Screen sampler{ repetitions, repetitions };
        index_t samples{ (index) sampler.GetPixelCount() };

        noise.clear();
        noise.assign(samples, clear);
        for (index i{ 0 }; i < samples; ++i)
        {
            noise[i] = rand() % permilleFactor;
        }

        point1D period{ screen->w / repetitions };
        for (point1D y = 0; y < screen->h; ++y)
        {
            for (point1D x = 0; x < screen->w; ++x)
            {

                index_t horizontal{ (x / period) % period };
                index_t right{ (horizontal + 1) % period };
                index_t vertical{ (y / period) % period };
                index_t down{ (vertical + 1) % period };

                permille offsetVertical{ (permille) (x % period) };
                permille offsetHorizontal{ (permille) (y % period) };

                Color base{ A.lerp(B, noise[sampler.GetIndex({ horizontal, vertical })]) };
                Color Right{ A.lerp(B, noise[sampler.GetIndex({ right, vertical })]) };
                Color Down{ A.lerp(B, noise[sampler.GetIndex({ horizontal, down })]) };

                Color sampled{ base.lerp(Right, offsetVertical).lerp(Down, offsetVertical) };

                PutPixel(Point2D{ x, y }, sampled.rgba());
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
        Point2D mapped{ std::abs((int) (uv.u * permilleFactor / screen->w)) % screen->w,
                        std::abs((int) (uv.v * permilleFactor / screen->h)) % screen->h };
        return Effect::GetPixel(mapped);
    }
}
