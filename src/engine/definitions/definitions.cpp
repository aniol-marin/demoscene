module;

#include <cstdint>

export module definitions;

import std;

export class Color;
export struct Point2D;
export struct Renderable;
export struct Texturable;

export constexpr double PI = 3.14159265358979323846264338327950288;

export using Id = uint_fast8_t;
export using bunch = uint_fast8_t;
export using seconds = uint_fast16_t;
export using milliseconds = uint_fast16_t;
export using permille = int_fast16_t;
export using speed = uint_fast16_t;
export using index = uint_fast32_t;
export using point1D = uint_fast16_t;
export using offset1D = int_fast64_t;
export using rgbaColor = uint32_t;
export using hslaColor = uint32_t;
export using tempChannel = uint_fast16_t;
export using channel = uint_fast8_t;
export using hue = uint_fast8_t;
export using saturation = uint_fast8_t;
export using lightness = uint_fast8_t;

export struct PixelBuffer : std::vector<rgbaColor> {};
export using pixel_count = PixelBuffer::size_type;
export struct StencilBuffer : std::vector<bool> {};
export struct ChannelBuffer : std::vector<channel> {};
export struct ColorBuffer : std::vector<Color> {};
export struct stencil : std::function<bool(Point2D)> {};
struct Texture : std::unique_ptr<Texturable> {}; // TODO
export using Renderables = std::vector<Renderable*>;

export constexpr permille permilleFactor{ 1024 };
export constexpr double permilleRad{ 2 * PI / permilleFactor };

export constexpr rgbaColor mask_opaque{ 0xFF000000 };
export constexpr rgbaColor mask_red{ 0x00FF0000 };
export constexpr rgbaColor mask_green{ 0x0000FF00 };
export constexpr rgbaColor mask_blue{ 0x000000FF };

export constexpr channel clear{ 0x0 };
export constexpr channel saturated{ 0xFF };
export constexpr channel halfValue{ 0xFF / 2 };
export constexpr rgbaColor transparent{ clear };
export constexpr rgbaColor black{ mask_opaque };
export constexpr rgbaColor white{ mask_opaque | mask_red | mask_green | mask_blue };
export constexpr rgbaColor red{ mask_opaque | mask_red };
export constexpr rgbaColor green{ mask_opaque | mask_green };
export constexpr rgbaColor blue{ mask_opaque | mask_blue };
export constexpr rgbaColor yellow{ red | green };
export constexpr rgbaColor magenta{ red | blue };
export constexpr rgbaColor teal{ blue | green };
export constexpr rgbaColor orange{ 0xFFFF9933 };
export constexpr rgbaColor concrete{ 0xFF5D696B };

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

struct Point2D {
	point1D x{};
	point1D y{};

	Point2D() = default;
	~Point2D() = default;
	Point2D(const Point2D&) = default;
	Point2D(Point2D&&) = default;
	Point2D(point1D x, point1D y): x{x}, y{y} {}
	
	const Point2D& operator=(const Point2D& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
};

export struct Offset2D {
	const offset1D x, y;
	Offset2D() :
		x{},
		y{} {}
	Offset2D(offset1D x, offset1D y) :
		x{ x },
		y{ y } {}
	~Offset2D() {}
};

export struct CoordinateUV {
	const permille u, v;
	CoordinateUV() :
		u{},
		v{} {}
	CoordinateUV(offset1D x, offset1D y) :
		u{ (permille)x },
		v{ (permille)y } {}
	~CoordinateUV() {}
};

class Color {
	channel m_r{};
	channel m_g{};
	channel m_b{};
	channel m_a{};

public:

	Color() = default;
	~Color() = default;
	Color(const Color&) = default;
	Color(Color&&) = default;
	constexpr Color& operator=(const Color&) = default;

	Color(const rgbaColor color) :
		m_r{ (channel)((color & mask_red) >> 16) },
		m_g{ (channel)((color & mask_green) >> 8) },
		m_b{ (channel)(color & mask_blue) },
		m_a{ (channel)((color & mask_opaque) >> 24) }
	{
	}


	Color(channel r, channel g, channel b, channel a = saturated) :
		m_r{ r },
		m_g{ g },
		m_b{ b },
		m_a{ a }
	{
	}


	const channel r() const {
		return m_r;
	}
	const channel g() const {
		return m_g;
	}
	const channel b() const {
		return m_b;
	}
	const channel a() const {
		return m_a;
	}
	rgbaColor rgba() {
		return m_b |
			(m_g << 8) |
			(m_r << 16) |
			(m_a << 24);
	}
	Color lerp(const Color& next, const permille permille) {
		return Color{
			(channel)(m_r + (next.r() - m_r) * permille / permilleFactor),
			(channel)(m_g + (next.g() - m_g) * permille / permilleFactor),
			(channel)(m_b + (next.b() - m_b) * permille / permilleFactor),
			(channel)(m_a + (next.a() - m_a) * permille / permilleFactor)
		};
	};
};
export struct Screen
{
	point1D w, h;

	Screen(point1D width, point1D heigth) :
		w{ width },
		h{ heigth } {}
	Screen(const Screen&) = default;
	Screen(Screen&&) = default;
	~Screen() = default;
	Screen& operator=(const Screen&) = default;
	Screen& operator=(Screen&&) = default;

	index GetIndex(Point2D point) const {
		return (index)w * (index)point.y + (index)point.x;
	}
	const pixel_count GetPixelCount() const {
		return pixel_count{ w * h };
	}
};

export const Screen defaultScreen{ 640, 480 };
export Screen textureSize{ 512, 512 };
export Screen superSampler{ 2048, 2048 };


export struct Initializable {
	virtual void Init() = 0;
	virtual void Finalize() = 0;
};

export struct Loadable {
	virtual void Load(std::string source) = 0;
	virtual void Unload() = 0;
};

struct Renderable {
	virtual void Update(permille intenisty, milliseconds deltaTime) = 0;
	virtual void Cache(StencilBuffer& mask) = 0;
	virtual rgbaColor GetPixel(Point2D point) = 0;
	virtual rgbaColor GetPixel(index index) = 0;
	virtual BlendMode GetBlend() = 0;
	virtual bool CheckStencil(index index) = 0;
};

struct Texturable {
	Texturable() = default; // enforced default non-copy, non-default-arguments constructor
	virtual ~Texturable() {}

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual rgbaColor GetMappedUV(CoordinateUV uv) = 0;
};

export struct Customizable {
	virtual constexpr Id TextureLimit() const = 0;
	virtual void AssignTexture(std::unique_ptr<Texturable> texture, Id id = 0) = 0;
};

