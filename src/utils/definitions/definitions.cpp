module definitions;

namespace mole_def
{
    channel lerp(channel m_r, channel next, permille permille)
    {
        return (channel) (m_r + (next - m_r) * permille / permilleFactor);
    }

    Timestamp::Timestamp(seconds start, milliseconds duration) : start{ start }, duration{ duration } {};

    Point2D::Point2D(point1D x, point1D y) : x{ x }, y{ y } {}

    const Point2D& Point2D::operator=(const Point2D& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Offset2D::Offset2D(offset1D x, offset1D y) : x{ x }, y{ y } {}

}
