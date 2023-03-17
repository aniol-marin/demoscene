export module definitions;

import <cstdint>;

export constexpr double PI = 3.14159265358979323846264338327950288;

export enum class ProgramStatus {
	TERMINATE_OK,
	TERMINATE_ERROR,
	RUNNING,
};

export struct Point2D {
	uint16_t x, y;
	Point2D() :
		x{},
		y{} {}
	Point2D(uint16_t x, uint16_t y) :
		x{ x },
		y{ y } {}
	virtual ~Point2D() {}
};

export struct Screen {
	const uint16_t w, h;
	Screen(uint16_t width, uint16_t heigth) :
		w{ width },
		h{ heigth } {}
};

export struct Color {
	uint8_t r, g, b, a;
	uint32_t rgba() const { return to32(a, r, g, b); }
	uint32_t mLerp(uint16_t milliUnits) {
		return to32(
			a * milliUnits / 1000,
			r * milliUnits / 1000,
			g * milliUnits / 1000,
			b * milliUnits / 1000
		);
	};
private:
	const uint32_t to32(uint8_t a, uint8_t r, uint8_t g, uint8_t b) const {
		return b |
			(g << 8) |
			(r << 16) |
			(a << 24);
	}
};