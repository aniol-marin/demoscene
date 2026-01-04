#include "stars.h"
#include <cstdlib>

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

    Stars::Stars(Timer* timer, Screen* screen)
	: Effect(timer, screen)
	, maxStars(100)
	, newStarsPerFrame(2)
	, maxSpeed(30)
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
                stars.push_back(Star(*screen, maxSpeed));
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
            /*
	    star.Draw(&PutPixel);
	    star.Draw([&](Point2D point, rgbaColor color) { PutPixel(point, color); });
	    */
        }
    }
}
