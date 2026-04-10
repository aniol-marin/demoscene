module;

#include <functional>
#include <cstdlib>
#include <cstdint>

module stars:star;

import definitions;
import timer;
import effect;

namespace MoleDemo
{
    using namespace mole_def;

    // TO DO remove duplication of definition in private implementation
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

    Star::Star(const Screen& screen, const speed& maxSpeed) : maxSpeed{ maxSpeed }, screen{ screen }
    {
        Reset();
    }

    Star::~Star() {}

    void Star::Reset()
    {
        progress = 0;
        position = { std::rand() % screen.w, 0 };
        baseSpeed = 1 + std::rand() % maxSpeed;
        currentSpeed = baseSpeed;
        brightness = permilleFactor * baseSpeed / maxSpeed;
        color = { static_cast<channel>(std::rand() % saturated),
                  static_cast<channel>(std::rand() % saturated),
                  static_cast<channel>(std::rand() % saturated) };
    }

    void Star::Update(permille intensity, milliseconds deltaTime)
    {
        currentSpeed += deltaTime;
        progress += currentSpeed;
        position = { position.x, position.y + progress / permilleFactor };

        if (position.y >= screen.h)
        {
            Reset();
        }
        else
        {
            currentColor = dessaturated.lerp(color, intensity);
        }
    }

    void Star::Draw(std::function<void(Point2D, rgbaColor)> putPixel)
    {
        std::int_fast64_t y{ static_cast<std::int_fast64_t>(position.y) };
        std::int_fast16_t trail{ (std::int_fast16_t) brightness };
        permille fade{ permilleFactor / (int) (1 + currentSpeed / maxSpeed) };
        while (trail > 0 && y >= 0)
        {
            rgbaColor finalColor{ empty.lerp(currentColor, (permille) trail).rgba() };

            putPixel(Point2D{ position.x, (point1D) y }, finalColor);

            if (0 < position.x)
            {
                point1D left{ position.x - 1 };
                putPixel(Point2D{ left, (point1D) y }, finalColor);
            }
            if (screen.w > position.x)
            {
                point1D right{ position.x + 1 };
                putPixel(Point2D{ right, (point1D) y }, finalColor);
            }

            --y;
            trail -= fade;
        }
    }
}
