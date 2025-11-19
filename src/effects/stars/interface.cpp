export module stars;

import std.compat;
import definitions;
import timer;
import effect;
using namespace mole_def;

namespace MoleDemo
{
    export class Stars;
    class Star;
}

class MoleDemo::Stars : public Effect
{
    const int maxStars = 100;
    const int newStarsPerFrame = 2;
    const speed maxSpeed = 100;
    std::vector<Star> stars;

public:
    Stars(Timer* timer, Screen* screen);
    ~Stars() override = default;

    void Load() override;
    void Unload() override;

    void Update(permille intensity, milliseconds delta) override;
    void Cache(StencilBuffer& mask) override;
};

class MoleDemo::Star
{
    const Screen& screen;
    const speed& maxSpeed;
    Color empty{ transparent };
    Color dessaturated{ white };
    Color color{ white };
    Point2D position;
    int progress;
    permille brightness;
    speed currentSpeed;
    speed baseSpeed;
    Color currentColor;

    void Reset();

public:
    Star(const Screen& screen, const speed& maxSpeed);
    ~Star();

    void Update(permille intensity, milliseconds delta);
    void Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel);
};
