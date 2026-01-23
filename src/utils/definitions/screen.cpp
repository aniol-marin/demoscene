module definitions;

namespace mole_def
{
    Screen::Screen(point1D width, point1D heigth) : w{ width }, h{ heigth } {}

    index_t Screen::GetIndex(Point2D point) const
    {
        return static_cast<index_t>(w * point.y + point.x);
    }

    const pixel_count Screen::GetPixelCount() const
    {
        return pixel_count{ w * h };
    }
}
