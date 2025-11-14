module definitions;

namespace mole_def
{
    Screen::Screen(point1D width, point1D heigth) : w{ width }, h{ heigth } {}

    constexpr index Screen::GetIndex(Point2D point) const
    {
        return (index) w * (index) point.y + (index) point.x;
    }

    constexpr const pixel_count Screen::GetPixelCount() const
    {
        return pixel_count{ w * h };
    }
}
