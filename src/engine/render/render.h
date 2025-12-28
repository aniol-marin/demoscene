#ifndef MOLE_RENDER_H
#define MOLE_RENDER_H

#include <map>
#include "Effect.h"
#include "definitions.h"
#include "renderables.h"
#include "sdl_wrapper.h"

using namespace mole_def;

namespace MoleDemo
{
    struct Blending
    {
        const BlendMode mode;
        virtual ~Blending() {}
        virtual rgbaColor Blend(const rgbaColor base, const rgbaColor next) = 0;
        virtual rgbaColor Blend(Color& base, Color& next) = 0;

    protected:
        Blending(BlendMode mode) : mode(mode) {}
    };

    struct OverrideBlend : public Blending
    {
        OverrideBlend() : Blending(mole_def::BLEND_MODE_OVERRIDE) {}
        ~OverrideBlend() {}
        rgbaColor Blend(const rgbaColor base, const rgbaColor next) { return next; }
        rgbaColor Blend(Color& base, Color& next) { return next.rgba(); };
    };

    struct AlphaBlend : public Blending
    {
        AlphaBlend() : Blending(mole_def::BLEND_MODE_ALPHABLEND) {}
        ~AlphaBlend() {}

        rgbaColor Blend(const rgbaColor base, const rgbaColor next)
        {
            Color ref_base(base);
            Color ref_next(next);
            return Blend(ref_base, ref_next);
        };
        rgbaColor Blend(Color& base, Color& next)
        {

            tempChannel aB(base.a());
            tempChannel rB(base.r());
            tempChannel gB(base.g());
            tempChannel bB(base.b());

            tempChannel aN(next.a());
            tempChannel rN(next.r());
            tempChannel gN(next.g());
            tempChannel bN(next.b());

            channel a((channel) (aN + (0xFF - aN) * aB / 0xFF));
            channel r((channel) (a == 0x0 ? 0x0 : (rN * aN + rB * (0xFF - aN)) / a));
            channel g((channel) (a == 0x0 ? 0x0 : (gN * aN + gB * (0xFF - aN)) / a));
            channel b((channel) (a == 0x0 ? 0x0 : (bN * aN + bB * (0xFF - aN)) / a));

            return Color(r, g, b, a).rgba();
        };
    };

    class RenderQueue
    {
        std::map<BlendMode, Blending*> blending;

    public:
        RenderQueue();
        ~RenderQueue();

        void Cache(Renderables& renderables, StencilBuffer& mask);
        void Render(Renderables& renderables, PixelBuffer& buffer);
    };

    class RenderManager : public Initializable
    {
    public:
        RenderManager(Screen& screen, SDL::SDLManager& sdl);
        RenderManager(const RenderManager& other) :
          m_screen(other.m_screen), queue(other.queue), buffer(other.buffer), mask(other.mask), sdl(other.sdl)
        {
        }
        ~RenderManager() {}

    private:
        const Screen m_screen;
        RenderQueue* queue;
        PixelBuffer buffer;
        StencilBuffer mask;
        SDL::SDLManager& sdl;

        void Lock();
        void Unlock();
        void Render();

    public:
        void Init();
        void Finalize();
        void Draw(Renderables& renderables);
        StencilBuffer& GetMask();
    };
}

#endif
