#include "stars.h"

#include <functional>
#include <cstdlib>
#include <cstdint>

namespace MoleDemo
{
    using namespace mole_def;

    Star::Star(const Screen& screen, const speed& maxSpeed) :
      screen(screen), maxSpeed(maxSpeed), empty(0x0), dessaturated(0xFFFFFFFF)
    {
        Reset();
    }

    Star::~Star() {}

    void Star::Reset()
    {
        progress = 0;
        position = Point2D(rand() % screen.w, 0);
        baseSpeed = 1 + rand() % maxSpeed;
        currentSpeed = baseSpeed;
        brightness = permilleFactor() * baseSpeed / maxSpeed;
        color = (static_cast<channel>(std::rand() % 0xFF),
                 static_cast<channel>(std::rand() % 0xFF),
                 static_cast<channel>(std::rand() % 0xFF));
    }

    void Star::Update(permille intensity, milliseconds deltaTime)
    {
        currentSpeed += deltaTime;
        progress += currentSpeed;
        position = Point2D(position.x, position.y + progress / permilleFactor());

        if (position.y >= screen.h)
        {
            Reset();
        }
        else
        {
            currentColor = dessaturated.lerp(color, intensity);
        }
    }

    void Star::Draw(drawer putPixel)
    {
        long int y(static_cast<long int>(position.y));
        short int trail(brightness);
        permille fade(permilleFactor() / (int) (1 + currentSpeed / maxSpeed));
        while (trail > 0 && y >= 0)
        {
            rgbaColor finalColor(empty.lerp(currentColor, (permille) trail).rgba());

            putPixel(Point2D(position.x, (point1D) y), finalColor);

            if (0 < position.x)
            {
                point1D left(position.x - 1);
                putPixel(Point2D(left, (point1D) y), finalColor);
            }
            if (screen.w > position.x)
            {
                point1D right(position.x + 1);
                putPixel(Point2D(right, (point1D) y), finalColor);
            }

            --y;
            trail -= fade;
        }
    }
}
