#include "stars.h"

#include <cstdlib>

namespace MoleDemo
{
    using namespace mole_def;


    Stars::Stars(Timer* timer, Screen* screen) : Effect(timer, screen), maxStars(100), newStarsPerFrame(2), maxSpeed(30)
    {
        ClearBuffer(0x0);
    }

    Stars::~Stars() {}

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
                stars.push_back(Star(*get_screen(), maxSpeed));
            }
        }

        for (Star* i = &*stars.begin(); i != &*stars.end(); ++i)
        {
            Star& star = *i;
            star.Update(intensity, delta);
        }
    }

    void Stars::Cache(StencilBuffer& mask)
    {
        ClearBuffer(0x0);
        for (Star* i = &*stars.begin(); i != &*stars.end(); ++i)
        {
            Star& star = *i;
            star.Draw(PutPixel);
            /*
        star.Draw([&](Point2D point, rgbaColor color) { PutPixel(point, color); });
        */
        }
    }
}
