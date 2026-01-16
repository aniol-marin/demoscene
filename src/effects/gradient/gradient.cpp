module gradient;

namespace MoleDemo
{
    using namespace mole_def;

    Gradient::Gradient(Timer* timer, Screen* screen) : Effect{ timer, screen } {}

    void Gradient::Load()
    {
        Color left;
        Color right;
        for (point1D y = 0; y < screen->h; ++y)
        {

            permille vertical{ (permille) (y * permilleFactor / screen->w) };
            right = NE.lerp(SE, vertical);
            left = NW.lerp(SW, vertical);

            for (point1D x = 0; x < screen->w; ++x)
            {
                permille horizontal{ (permille) (x * permilleFactor / screen->w) };
                PutPixel(Point2D{ x, y }, left.lerp(right, horizontal).rgba());
            }
        }
    }

    void Gradient::Unload() {}

    void Gradient::Update(permille intensity, milliseconds delta) {}

    void Gradient::Cache(StencilBuffer& mask) {}

    void Gradient::SetColors(Color NE, Color NW, Color SW, Color SE)
    {
        this->NE = NE;
        this->NW = NW;
        this->SE = SE;
        this->SW = SW;
    }

    rgbaColor Gradient::GetMappedUV(CoordinateUV p)
    {
        Point2D mapped{ std::abs((int) (p.u * permilleFactor / screen->w)) % screen->w,
                        std::abs((int) (p.v * permilleFactor / screen->h)) % screen->h };
        return Effect::GetPixel(mapped);
    }
}
