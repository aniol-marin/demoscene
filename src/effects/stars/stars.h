#ifndef MOLE_STARS_H
#define MOLE_STARS_H

#include "definitions.h"
#include "Effect.h"
using namespace mole_def;

namespace MoleDemo
{
	class Star;

    class Stars : public Effect
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

    class Star
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
}
#endif
