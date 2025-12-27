#include "definitions.h"

namespace mole_def
{
    permille permilleFactor()
    {
        return 1024;
    }

    channel lerp(channel m_r, channel next, permille permille)
    {
        return (channel) (m_r + (next - m_r) * permille / permilleFactor());
    }

    Timestamp::Timestamp() : start(), duration()
    {
        throw std::exception();
    }
    Timestamp::Timestamp(seconds start, milliseconds duration) : start(start), duration(duration) {}

    Timestamp::~Timestamp() {}

    Point2D::Point2D() : x(), y() {}

    Point2D::Point2D(point1D x, point1D y) : x(x), y(y) {}

    Point2D::Point2D(const Point2D& other) : x(other.x), y(other.y) {}

    Point2D::~Point2D() {}

    const Point2D& Point2D::operator=(const Point2D& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Offset2D::Offset2D() : x(), y() {}

    Offset2D::Offset2D(offset1D x, offset1D y) : x(x), y(y) {}

    Offset2D::~Offset2D() {}

    CoordinateUV::CoordinateUV() : u(), v() {}

    CoordinateUV::CoordinateUV(offset1D u, offset1D v) : u(u), v(v) {}

    CoordinateUV::~CoordinateUV() {}
}
