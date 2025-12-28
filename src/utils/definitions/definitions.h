#ifndef MOLE_DEFINITIONS_H
#define MOLE_DEFINITIONS_H

#include <string>
#include <vector>

#define PI 3.14159265358979323846264338327950288

namespace mole_def
{
    class Color;
    struct Point2D;
    struct Renderable;
    struct Texturable;
    struct Screen;

    typedef char Id;
    typedef char bunch;
    typedef unsigned short seconds;
    typedef unsigned short milliseconds;
    typedef short int permille;
    typedef short permille;
    typedef unsigned short speed;
    typedef unsigned int index_t;
    typedef unsigned short point1D;
    typedef unsigned long offset1D;
    typedef unsigned int rgbaColor;
    typedef unsigned int hslaColor;
    typedef unsigned short tempChannel;
    typedef unsigned char channel;
    typedef unsigned char hue;
    typedef unsigned char saturation;
    typedef unsigned char lightness;

    struct PixelBuffer : std::vector<rgbaColor>
    {
    };
    typedef PixelBuffer::size_type pixel_count;
    struct StencilBuffer : std::vector<bool>
    {
    };
    struct ChannelBuffer : std::vector<channel>
    {
    };
    struct ColorBuffer : std::vector<Color>
    {
    };
    /*
    typedef bool (*stencil)(Point2D);
    struct Texture : std::unique_ptr<Texturable>
    {
        private:
            Texturable* t {};

        ~Texture() { delete t; }
    }; // TODO
    using Renderables = std::vector<Renderable*>;
    */

    permille permilleFactor();
    typedef std::vector<Renderable*> Renderables;

    /*
        double permilleRad{ 2 * PI / permilleFactor };

        channel clear{ 0x0 };
        channel saturated{ 0xFF };
        channel halfValue{ 0xFF / 2 };
        rgbaColor transparent{ clear };
        rgbaColor black{ mask_opaque };
        rgbaColor white{ mask_opaque | mask_red | mask_green | mask_blue };
        rgbaColor red{ mask_opaque | mask_red };
        rgbaColor green{ mask_opaque | mask_green };
        rgbaColor blue{ mask_opaque | mask_blue };
        rgbaColor yellow{ red | green };
        rgbaColor magenta{ red | blue };
        rgbaColor teal{ blue | green };
        rgbaColor orange{ 0xFFFF9933 };
        rgbaColor concrete{ 0xFF5D696B };
        */

    enum ProgramStatus
    {
        PROGRAM_TERMINATE_OK,
        PROGRAM_TERMINATE_ERROR,
        PROGRAM_RUNNING,
    };

    enum BlendMode // TO DO prefix
    {
        BLEND_MODE_OVERRIDE,
        AlphaBlend,
        Additive,
        Subtractive,
        Multiply,
        Divide,
        BLEND_MODE_SCREEN,
    };

    enum TransitionType // TO DO prefix
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

        Timestamp();
        Timestamp(seconds start, milliseconds duration);
        ~Timestamp();
    };

    struct Point2D
    {
        point1D x;
        point1D y;

        Point2D();
        Point2D(point1D x, point1D y);
        Point2D(const Point2D&);
        ~Point2D();

        const Point2D& operator=(const Point2D& other);
    };

    struct Offset2D
    {
        const offset1D x;
        const offset1D y;

        Offset2D();
        Offset2D(offset1D x, offset1D y);
        ~Offset2D();
    };

    struct CoordinateUV
    {
        const permille u;
        const permille v;

        CoordinateUV();
        CoordinateUV(offset1D x, offset1D y);
        ~CoordinateUV();
    };

    class Color
    {
        channel m_r;
        channel m_g;
        channel m_b;
        channel m_a;

    public:
        Color();
        Color(const rgbaColor& color);
        Color(channel r, channel g, channel b, channel a = 0xFF);
        ~Color();
        Color(const Color&);
        Color& operator=(const Color&);

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

        Screen();
        Screen(point1D width, point1D heigth);
        ~Screen();
        Screen(const Screen&);
        Screen& operator=(const Screen&);

        const pixel_count GetPixelCount() const;
        index_t GetIndex(Point2D point) const;
    };

    /*
    Screen defaultScreen{ 640, 480 };
    Screen textureSize{ 512, 512 };
    Screen superSampler{ 2048, 2048 };
     */

    struct Initializable
    {
        virtual void Init() = 0;
        virtual void Finalize() = 0;
    };

    struct Loadable
    {
        virtual void Load(const std::string& source) = 0;
        virtual void Unload() = 0;
    };

    struct Renderable
    {
        virtual void Update(permille intensity, milliseconds deltaTime) = 0;
        virtual void Cache(StencilBuffer& mask) = 0;
        virtual rgbaColor GetPixel(Point2D point) = 0;
        virtual rgbaColor GetPixel(index_t index) = 0;
        virtual BlendMode GetBlend() = 0;
        virtual bool CheckStencil(index_t index) = 0;
    };

    struct Texturable
    {
        Texturable() {} // enforced default non-copy, non-default-arguments constructor
        virtual ~Texturable() {}

        virtual void Load() = 0;
        virtual void Unload() = 0;

        virtual rgbaColor GetMappedUV(CoordinateUV uv) = 0;
    };

    struct Customizable
    {
        virtual Id TextureLimit() const = 0;
        virtual void AssignTexture(Texturable* texture_ownership, Id id = 0) = 0;
    };
}

#endif // !MOLE_DEFINITIONS_H
