#ifndef MOLE_STARS_H
#define MOLE_STARS_H

#include <vector>
#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    class Star;
    typedef void (*drawer)(Point2D, rgbaColor);

    class Stars : public Effect
    {
        const int maxStars;
        const int newStarsPerFrame;
        const speed maxSpeed;
        std::vector<Star> stars;

    public:
        Stars(Timer* timer, Screen* screen);
        ~Stars();

        void Load();
        void Unload();

        void Update(permille intensity, milliseconds delta);
        void Cache(StencilBuffer& mask);
    };

    class Star
    {
        const Screen& screen;
        const speed& maxSpeed;
        Color empty;
        Color dessaturated;
        Color color;
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
        void Draw(drawer putPixel);
    };
}
#endif
