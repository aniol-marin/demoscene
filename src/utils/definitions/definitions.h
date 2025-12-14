#ifndef MOLE_DEFINITIONS_H
#define MOLE_DEFINITIONS_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string_view>
#include <vector>

namespace mole_def
{
    class Color;
    struct Point2D;
    struct Renderable;
    struct Texturable;

    constexpr double PI = 3.14159265358979323846264338327950288;

    using Id = uint_fast8_t;
    using bunch = uint_fast8_t;
    using seconds = uint_fast16_t;
    using milliseconds = uint_fast16_t;
    using permille = int_fast16_t;
    using speed = uint_fast16_t;
    using index_t = uint_fast32_t;
    using point1D = uint_fast16_t;
    using offset1D = int_fast64_t;
    using rgbaColor = uint32_t;
    using hslaColor = uint32_t;
    using tempChannel = uint_fast16_t;
    using channel = uint_fast8_t;
    using hue = uint_fast8_t;
    using saturation = uint_fast8_t;
    using lightness = uint_fast8_t;

    struct PixelBuffer : std::vector<rgbaColor>
    {
    };
    using pixel_count = PixelBuffer::size_type;
    struct StencilBuffer : std::vector<bool>
    {
    };
    struct ChannelBuffer : std::vector<channel>
    {
    };
    struct ColorBuffer : std::vector<Color>
    {
    };
    struct stencil : std::function<bool(Point2D)>
    {
    };
    struct Texture : std::unique_ptr<Texturable>
    {
    }; // TODO
    using Renderables = std::vector<Renderable*>;

    constexpr permille permilleFactor{ 1024 };
    constexpr double permilleRad{ 2 * PI / permilleFactor };

    constexpr rgbaColor mask_opaque{ 0xFF000000 };
    constexpr rgbaColor mask_red{ 0x00FF0000 };
    constexpr rgbaColor mask_green{ 0x0000FF00 };
    constexpr rgbaColor mask_blue{ 0x000000FF };

    constexpr channel clear{ 0x0 };
    constexpr channel saturated{ 0xFF };
    constexpr channel halfValue{ 0xFF / 2 };
    constexpr rgbaColor transparent{ clear };
    constexpr rgbaColor black{ mask_opaque };
    constexpr rgbaColor white{ mask_opaque | mask_red | mask_green | mask_blue };
    constexpr rgbaColor red{ mask_opaque | mask_red };
    constexpr rgbaColor green{ mask_opaque | mask_green };
    constexpr rgbaColor blue{ mask_opaque | mask_blue };
    constexpr rgbaColor yellow{ red | green };
    constexpr rgbaColor magenta{ red | blue };
    constexpr rgbaColor teal{ blue | green };
    constexpr rgbaColor orange{ 0xFFFF9933 };
    constexpr rgbaColor concrete{ 0xFF5D696B };

    enum class ProgramStatus
    {
        TERMINATE_OK,
        TERMINATE_ERROR,
        RUNNING,
    };

    enum class BlendMode
    {
        Override,
        AlphaBlend,
        Additive,
        Subtractive,
        Multiply,
        Divide,
        Screen,
    };

    enum class TransitionType
    {
        Cut,
        Fade,
        Wipe,
        Explode,
        Implode,
        Rotate,
    };

    channel lerp(channel m_r, channel next, permille permille);

    struct Timestamp
    {
        const seconds start;
        const milliseconds duration;

        Timestamp() = delete;
        Timestamp(seconds start, milliseconds duration);
        ~Timestamp() = default;
    };

    struct Point2D
    {
        point1D x{};
        point1D y{};

        Point2D() = default;
        Point2D(point1D x, point1D y);
        Point2D(const Point2D&) = default;
        Point2D(Point2D&&) = default;
        ~Point2D() = default;

        const Point2D& operator=(const Point2D& other);
    };

    struct Offset2D
    {
        const offset1D x{};
        const offset1D y{};

        Offset2D() = default;
        Offset2D(offset1D x, offset1D y);
        ~Offset2D() {}
    };

    struct CoordinateUV
    {
        const permille u, v;
        CoordinateUV() : u{}, v{} {}
        CoordinateUV(offset1D x, offset1D y) : u{ (permille) x }, v{ (permille) y } {}
        ~CoordinateUV() {}
    };

    class Color
    {
        channel m_r{};
        channel m_g{};
        channel m_b{};
        channel m_a{};

    public:
        Color() = default;
        Color(const rgbaColor& color);
        Color(channel r, channel g, channel b, channel a = saturated);
        ~Color() = default;
        Color(const Color&) = default;
        Color(Color&&) = default;
        Color& operator=(const Color&) = default;

        const channel r() const;
        const channel g() const;
        const channel b() const;
        const channel a() const;
        rgbaColor rgba();
        Color lerp(const Color& next, const permille permille);
    };

    struct Screen
    {
        point1D w;
        point1D h;

        Screen(point1D width, point1D heigth);
        ~Screen() = default;
        Screen(const Screen&) = default;
        Screen(Screen&&) = default;
        Screen& operator=(const Screen&) = default;
        Screen& operator=(Screen&&) = default;

        const pixel_count GetPixelCount() const;
        constexpr index_t GetIndex(Point2D point) const;
    };

    /*
    constexpr Screen defaultScreen{ 640, 480 };
    constexpr Screen textureSize{ 512, 512 };
    constexpr Screen superSampler{ 2048, 2048 };
     */

    struct Initializable
    {
        virtual void Init() = 0;
        virtual void Finalize() = 0;
    };

    struct Loadable
    {
        virtual void Load(std::string_view source) = 0;
        virtual void Unload() = 0;
    };

    struct Renderable
    {
        virtual void Update(permille intenisty, milliseconds deltaTime) = 0;
        virtual void Cache(StencilBuffer& mask) = 0;
        virtual rgbaColor GetPixel(Point2D point) = 0;
        virtual rgbaColor GetPixel(index_t index) = 0;
        virtual BlendMode GetBlend() = 0;
        virtual bool CheckStencil(index_t index) = 0;
    };

    struct Texturable
    {
        Texturable() = default; // enforced default non-copy, non-default-arguments constructor
        virtual ~Texturable() {}

        virtual void Load() = 0;
        virtual void Unload() = 0;

        virtual rgbaColor GetMappedUV(CoordinateUV uv) = 0;
    };

    struct Customizable
    {
        virtual constexpr Id TextureLimit() const = 0;
        virtual void AssignTexture(std::unique_ptr<Texturable> texture, Id id = 0) = 0;
    };
}

#endif // !MOLE_DEFINITIONS_H
