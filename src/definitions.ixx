export module definitions;

import <cstdint>;

export constexpr double PI = 3.14159265358979323846264338327950288;

export enum class ProgramStatus {
	TERMINATE_OK,
	TERMINATE_ERROR,
	RUNNING,
};

export enum class BlendMode {
	Override,
	AlphaBlend,
	Additive,
	Subtractive,
	Multiply,
	Divide,
	Screen,
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
	Screen() :
		w{ 640 },
		h{ 480 } {} // TODO delete after injection tests
	Screen(uint16_t width, uint16_t heigth) :
		w{ width },
		h{ heigth } {}
};

export class Color {
	uint8_t m_r, m_g, m_b, m_a;
	const uint32_t to32(uint8_t a, uint8_t r, uint8_t g, uint8_t b) const {
		return b |
			(g << 8) |
			(r << 16) |
			(a << 24);
	}
public:
	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) {
		m_a = a;
		m_r = r;
		m_g = g;
		m_b = b;
	}
	uint8_t r() const { return m_r; }
	uint8_t g() const { return m_g; }
	uint8_t b() const { return m_b; }
	uint8_t a() const { return m_a; }
	uint32_t rgba() const { return to32(m_a, m_r, m_g, m_b); }
	uint32_t mLerp(const Color& base, const uint16_t milliUnits) {
		uint8_t bA = base.a();
		uint8_t bR = base.r();
		uint8_t bG = base.g();
		uint8_t bb = base.b();
		uint8_t cA = m_a;
		uint8_t cR = m_r;
		uint8_t cG = m_g;
		uint8_t cb = m_b;
		uint8_t vA = base.a() + (m_a - base.a()) * milliUnits / 1000;
		uint8_t vR = base.r() + (m_r - base.r()) * milliUnits / 1000;
		uint8_t vG = base.g() + (m_g - base.g()) * milliUnits / 1000;
		uint8_t vb = base.b() + (m_b - base.b()) * milliUnits / 1000;

		return to32(
			base.a() + (m_a - base.a()) * milliUnits / 1000,
			base.r() + (m_r - base.r()) * milliUnits / 1000,
			base.g() + (m_g - base.g()) * milliUnits / 1000,
			base.b() + (m_b - base.b()) * milliUnits / 1000
		);
	};
};