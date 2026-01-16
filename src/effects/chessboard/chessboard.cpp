module chess;

namespace MoleDemo
{
    using namespace mole_def;

    ChessBoard::ChessBoard(Timer* timer, Screen* screen) : Effect{ timer, screen } {}

    void ChessBoard::Load()
    {
        point1D period{ screen->w / repetitions };
        Color right;
        for (point1D y = 0; y < screen->h; ++y)
        {
            for (point1D x = 0; x < screen->w; ++x)
            {

                const bool first{ (x / period) % 2 != (y / period) % 2 };

                Color& color{ first ? A : B };
                PutPixel(Point2D{ x, y }, color.rgba());
            }
        }
    }

    void ChessBoard::Unload() {}

    void ChessBoard::Update(permille intensity, milliseconds delta) {}

    void ChessBoard::Cache(StencilBuffer& mask) {}

    void ChessBoard::Set(Color a, Color b, bunch repetitions)
    {
        this->A = a;
        this->B = b;
        this->repetitions = repetitions;
    }

    rgbaColor ChessBoard::GetMappedUV(CoordinateUV p)
    {
        Point2D mapped{ std::abs((int) (p.u * permilleFactor / screen->w)) % screen->w,
                        std::abs((int) (p.v * permilleFactor / screen->h)) % screen->h };
        return Effect::GetPixel(mapped);
    }
}
