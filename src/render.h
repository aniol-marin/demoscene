#ifndef MOLE_RENDER_H
#define MOLE_RENDER_H

#include <cstdint>

namespace MoleDemo
{
    using size_t = std::size_t;

    struct MoleDemo::Blending
    {
        const BlendMode mode;
        virtual ~Blending() = default;
        virtual rgbaColor Blend(const rgbaColor base, const rgbaColor next) = 0;
        virtual rgbaColor Blend(Color& base, Color& next) = 0;

    protected:
        Blending(BlendMode mode);
    };

    struct MoleDemo::OverrideBlend : public Blending
    {
        OverrideBlend();
        ~OverrideBlend();
        rgbaColor Blend(const rgbaColor base, const rgbaColor next) override;
        rgbaColor Blend(Color& base, Color& next) override;
    };

    struct MoleDemo::AlphaBlend : public MoleDemo::Blending
    {
        AlphaBlend();
        ~AlphaBlend() = default;
        rgbaColor Blend(const rgbaColor base, const rgbaColor next) override;
        rgbaColor Blend(Color& base, Color& next) override;
    };

    class MoleDemo::RenderQueue
    {
        std::map<BlendMode, std::unique_ptr<Blending>> blending;

    public:
        RenderQueue();
        void Cache(Renderables& renderables, StencilBuffer& mask);
        void Render(Renderables& renderables, PixelBuffer& buffer);
    };

    class MoleDemo::RenderManager : public Initializable
    {
    public:
        RenderManager() = delete;
        RenderManager(Screen& screen, SDL::SDLManager& sdl);
        RenderManager(const RenderManager&) = default;
        RenderManager(RenderManager&&) = default;
        ~RenderManager() = default;

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
    }
};
#endif //! MOLE_RENDER_H
