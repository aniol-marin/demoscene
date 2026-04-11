#include "stars.h"

#include <cstdlib>
#include <typeinfo>

namespace MoleDemo
{
    using namespace mole_def;

    Stars::Stars(Timer* timer, Screen* screen) : Effect{ timer, screen }
    {
        ClearBuffer(transparent);
    }

    void Stars::Load()
    {
        std::srand(0);
    }

    void Stars::Unload() {}

    void Stars::Update(permille intensity, milliseconds delta)
    {
        if (stars.size() < maxStars)
        {
            for (int i = 0; i < newStarsPerFrame; i++)
            {
                stars.push_back(Star{ *screen, maxSpeed });
            }
        }

        for (Star& star: stars)
        {
            star.Update(intensity, delta);
        }
    }

    void Stars::Cache(StencilBuffer& mask)
    {
        ClearBuffer(transparent);
        for (Star& star: stars)
        {
            star.Draw([&](Point2D point, rgbaColor color) { PutPixel(point, color); });
        }
    }
}
