export module wheel;

import std;
import effect;
import definitions;
import timer;

namespace MoleDemo
{
    export class Wheel;
}

class MoleDemo::Wheel : public Effect
{
    Color color;
    Color base;
    Color top;
    rgbaColor rgbColor;
    double rotation;
    void SetColor();

public:
    Wheel(Timer* timer, Screen* screen);
    ~Wheel();

    void Load() override;
    void Unload() override;
    void Update(permille intensity, milliseconds delta) override;
    void Cache(StencilBuffer& mask) override;
    rgbaColor GetPixel(Point2D p) override;
    rgbaColor GetPixel(index_t index) override;
};

namespace MoleDemo
{
    Wheel::Wheel(Timer* timer, Screen* screen) :
      color{ black }, base{ halfValue, halfValue, halfValue }, top{ white }, Effect{ timer, screen }
    {
    }

    Wheel::~Wheel() {}

    void Wheel::Load()
    {
        rgbColor = transparent;
    }

    void Wheel::Unload() {}

    void Wheel::Update(permille intensity, milliseconds delta)
    {
        rotation = (permille) (rotation + delta * permilleFactor / 8192) % permilleFactor;
        SetColor();
        rgbColor = base.lerp(top, intensity).lerp(color, intensity).rgba();
    }

    void Wheel::Cache(StencilBuffer& mask) {}

    void Wheel::SetColor()
    {

        double rad = rotation * permilleRad;
        color = Color{ (channel) (halfValue * std::sin(rad) / 2 + halfValue),
                       (channel) (halfValue * std::cos(rad) / 2 + halfValue),
                       (channel) (halfValue * std::sin(PI + rad) / 2 + halfValue) };
    }

    rgbaColor Wheel::GetPixel(Point2D p)
    {
        return rgbColor;
    }

    rgbaColor Wheel::GetPixel(index_t index)
    {
        return rgbColor;
    }
}
