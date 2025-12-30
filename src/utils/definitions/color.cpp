#include "definitions.h"

namespace mole_def
{
    const rgbaColor mask_opaque(0xFF000000);
    const rgbaColor mask_red(0x00FF0000);
    const rgbaColor mask_green(0x0000FF00);
    const rgbaColor mask_blue(0x000000FF);

    Color::Color() : m_r(), m_g(), m_b(), m_a() {}

    Color::Color(const rgbaColor& color) :
      m_r((channel) ((color & mask_red) >> 16)),
      m_g((channel) ((color & mask_green) >> 8)),
      m_b((channel) (color & mask_blue)),
      m_a((channel) ((color & mask_opaque) >> 24))
    {
    }

    Color::Color(channel r, channel g, channel b, channel a) : m_r(r), m_g(g), m_b(b), m_a(a) {}

    Color::Color(const Color& other) : m_r(other.m_r), m_g(other.m_g), m_b(other.m_b), m_a(other.m_a) {}

    Color::~Color() {}

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
        return m_b | (m_g << 8) | (m_r << 16) | (m_a << 24);
    }

    Color Color::lerp(const Color& next, const permille permille)
    {
        return Color((channel) (m_r + (next.r() - m_r) * permille / permilleFactor()),
                     (channel) (m_g + (next.g() - m_g) * permille / permilleFactor()),
                     (channel) (m_b + (next.b() - m_b) * permille / permilleFactor()),
                     (channel) (m_a + (next.a() - m_a) * permille / permilleFactor()));
    }

    Color& Color::operator=(const Color& other)
    {
        m_r = other.m_r;
        m_g = other.m_g;
        m_b = other.m_b;
        m_a = other.m_a;

        return *this;
    }
}
