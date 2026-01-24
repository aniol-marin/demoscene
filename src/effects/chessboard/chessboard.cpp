#include "chessboard.h"

#include <cstdlib>

namespace MoleDemo
{
    using namespace mole_def;

    ChessBoard::ChessBoard(Timer* timer, Screen* screen) : Effect(timer, screen), repetitions(1) {}

    void ChessBoard::Load()
    {
        point1D period(get_screen()->w >= repetitions ? get_screen()->w / repetitions : 1);
        Color right;
        for (point1D y = 0; y < get_screen()->h; ++y)
        {
            for (point1D x = 0; x < get_screen()->w; ++x)
            {

                const bool first((x / period) % 2 != (y / period) % 2);

                Color& color{ first ? A : B };
                PutPixel(Point2D(x, y), color.rgba());
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
        Point2D mapped(std::abs((int) (p.u * permilleFactor() / get_screen()->w)) % get_screen()->w,
                       std::abs((int) (p.v * permilleFactor() / get_screen()->h)) % get_screen()->h);
        return Effect::GetPixel(mapped);
    }
}
