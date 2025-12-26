#include "definitions.h"

namespace mole_def
{
	Screen::Screen()
		: w()
		, h()
	{
		throw std::exception();
	}

	Screen::Screen(point1D width, point1D heigth)
		: w( width )
		, h( heigth )
	{
	}

	Screen::Screen(const Screen& other)
		: w( other.w )
		, h( other.h )
	{
	}

	Screen::~Screen()
	{
	}

	index_t Screen::GetIndex(Point2D point) const
	{
		return static_cast<index_t>(w * point.y + point.x);
	}

	const pixel_count Screen::GetPixelCount() const
	{
		return static_cast<pixel_count>( w * h );
	}
}
