#include "definitions.h"

namespace mole_def
{
channel lerp(channel m_r, channel next, permille permille) {
	return (channel)(m_r + (next - m_r) * permille / permilleFactor);
}

Timestamp::Timestamp(seconds start, milliseconds duration) :
	start{ start },
	duration{ duration } {};

Point2D::Point2D(point1D x, point1D y): x{x}, y{y}
{
}

const Point2D& Point2D::operator=(const Point2D& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Offset2D::Offset2D(offset1D x, offset1D y) :
	x{ x },
	y{ y }
{
}

CoordinateUV::CoordinateUV(offset1D x, offset1D y) :
	u{ (permille)x },
	v{ (permille)y }
{
}

Color::Color(const rgbaColor& color) :
	m_r{ (channel)((color & mask_red) >> 16) },
	m_g{ (channel)((color & mask_green) >> 8) },
	m_b{ (channel)(color & mask_blue) },
	m_a{ (channel)((color & mask_opaque) >> 24) }
{
}

Color::Color(channel r, channel g, channel b, channel a) :
	m_r{ r },
	m_g{ g },
	m_b{ b },
	m_a{ a }
{
}

const channel Color::r() const
{
	return m_r;
}

const channel Color::g() const
{
	return m_g;
}

const channel Color::b() const
{
	return m_b;
}

const channel Color::a() const
{
	return m_a;
}

rgbaColor Color::rgba()
{
	return m_b |
		(m_g << 8) |
		(m_r << 16) |
		(m_a << 24);
}

Color Color::lerp(const Color& next, const permille permille)
{
	return Color{
		(channel)(m_r + (next.r() - m_r) * permille / permilleFactor),
			(channel)(m_g + (next.g() - m_g) * permille / permilleFactor),
			(channel)(m_b + (next.b() - m_b) * permille / permilleFactor),
			(channel)(m_a + (next.a() - m_a) * permille / permilleFactor)
	};
}

index Screen::GetIndex(Point2D point) const
{
	return (index)w * (index)point.y + (index)point.x;
}

const pixel_count Screen::GetPixelCount() const
{
	return pixel_count{ w * h };
}
}

