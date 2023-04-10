export module definitions;

import <vector>;
import <cstdint>;
import <exception>;

export constexpr double PI = 3.14159265358979323846264338327950288;

export using seconds = uint_fast8_t;
export using milliseconds = uint_fast16_t;
export using permille = uint_fast16_t;
export using speed = uint_fast8_t;
export using index = uint_fast32_t;
export using point1D = uint_fast16_t;
export using rgbaColor = uint32_t;
export using hslaColor = uint32_t;
export using tempChannel = uint_fast16_t;
export using channel = uint_fast8_t;
export using hue = uint_fast8_t;
export using saturation = uint_fast8_t;
export using lightness = uint_fast8_t;

export struct PixelBuffer : std::vector<rgbaColor> {};
export struct StencilBuffer : std::vector<bool> {};

export constexpr permille permilleFactor{ 1024 };

export constexpr rgbaColor mask_opaque{ 0xFF000000 };
export constexpr rgbaColor mask_red{ 0x00FF0000 };
export constexpr rgbaColor mask_green{ 0x0000FF00 };
export constexpr rgbaColor mask_blue{ 0x000000FF };

export constexpr rgbaColor transparent{ ~mask_opaque };
export constexpr rgbaColor black{ mask_opaque };
export constexpr rgbaColor white{ mask_opaque | mask_red | mask_green | mask_blue };
export constexpr rgbaColor red{ mask_opaque | mask_red };
export constexpr rgbaColor green{ mask_opaque | mask_green };
export constexpr rgbaColor blue{ mask_opaque | mask_blue };
export constexpr rgbaColor orange{ red | green };
export constexpr rgbaColor magenta{ red | blue };
export constexpr rgbaColor tile{ blue | green };

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

export enum class TransitionType {
	Cut,
	Fade,
	Wipe,
	Explode,
	Implode,
	Rotate,
};

export channel lerp(channel m_r, channel next, permille permille) {
	return (channel)(m_r + (next - m_r) * permille / permilleFactor);
}

export struct Timestamp {
	const seconds start;
	const milliseconds duration;
	Timestamp(seconds start, milliseconds duration) :
		start{ start },
		duration{ duration } {};
	~Timestamp() {}
};

export struct Point2D {
	point1D x, y;
	Point2D() :
		x{},
		y{} {}
	Point2D(point1D x, point1D y) :
		x{ x },
		y{ y } {}
	virtual ~Point2D() {}
};

export struct Screen {
	const point1D w, h;
	Screen() :
		w{ 640 },
		h{ 480 } {} // TODO delete after injection tests
	Screen(point1D width, point1D heigth) :
		w{ width },
		h{ heigth } {}
	index GetPixelIndex(Point2D& point) {
		return (size_t)w * (size_t)point.y + (size_t)point.x;
	}
};

export class Color {
	channel m_r, m_g, m_b, m_a;
	hue m_h;
	saturation m_s;
	lightness m_l;
	bool rgbCached;
	bool hslCached;
	const rgbaColor to32(channel a, channel r, channel g, channel b) const {
		return b |
			(g << 8) |
			(r << 16) |
			(a << 24);
	}
	const hslaColor tohsla(channel a, hue h, saturation s, lightness l) const {
		return l |
			(s << 8) |
			(h << 16) |
			(a << 24);
	}
	void cacheRGB() {
		throw std::exception("tried to use an uncached RGB, but RGB caching is still not implemented");
	}
	void cacheHSL() {
		throw std::exception("tried to use an uncached HSL, but HSL caching is still not implemented");
	}
public:
	Color() :
		m_a{},
		m_r{},
		m_g{},
		m_b{},
		m_h{},
		m_s{},
		m_l{},
		rgbCached{ false },
		hslCached{ false } {}
	Color(const Color& color) :
		m_a{ color.m_a },
		m_r{ color.m_r },
		m_g{ color.m_g },
		m_b{ color.m_b },
		m_h{},
		m_s{},
		m_l{},
		rgbCached{ true },
		hslCached{ false } {}
	Color(const rgbaColor color) :
		m_a{ (channel)((color & mask_opaque) >> 24) },
		m_r{ (channel)((color & mask_red) >> 16) },
		m_g{ (channel)((color & mask_green) >> 8) },
		m_b{ (channel)(color & mask_blue) },
		m_h{},
		m_s{},
		m_l{},
		rgbCached{ true },
		hslCached{ false } {}
	Color(channel r, channel g, channel b, channel a) :
		m_a{ a },
		m_r{ r },
		m_g{ g },
		m_b{ b },
		m_h{},
		m_s{},
		m_l{},
		rgbCached{ true },
		hslCached{ false } {}
	~Color() {}

	void SetRGBA(channel r, channel g, channel b, channel a = 0xFF) {
		m_a = a;
		m_r = r;
		m_g = g;
		m_b = b;
		rgbCached = true;
		hslCached = false;
	}
	void SetHSLA(hue h, saturation s, lightness l, channel a = 0xFF) {
		m_a = a;
		m_h = h;
		m_s = s;
		m_l = l;
		rgbCached = false;
		hslCached = true;
	}
	const channel r() const { return m_r; }
	const channel g() const { return m_g; }
	const channel b() const { return m_b; }
	const channel a() const { return m_a; }
	const hue hue() const { return m_h; }
	const lightness lightness() const { return m_l; }
	const saturation saturation() const { return m_s; }
	rgbaColor rgba() {

		if (!rgbCached) {
			cacheRGB();
		}

		return to32(m_a, m_r, m_g, m_b);
	}
	hslaColor hsla() {
		if (!hslCached) {
			cacheHSL();
		}

		return tohsla(m_a, m_h, m_s, m_l);
	}
	Color lerp(const Color& next, const permille permille) {

		// TODO allow lerping with cached HSL

		if (!rgbCached) {
			cacheRGB();
		}

		return Color{
			(channel)(m_r + (next.r() - m_r) * permille / permilleFactor),
			(channel)(m_g + (next.g() - m_g) * permille / permilleFactor),
			(channel)(m_b + (next.b() - m_b) * permille / permilleFactor),
			(channel)(m_a + (next.a() - m_a) * permille / permilleFactor)
		};
	};
};