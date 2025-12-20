#include "render.h"
#include <memory>
#include "definitions.h"

using namespace mole_def;

namespace MoleDemo
{
    RenderQueue::RenderQueue()
    {
        blending[BlendMode::Override] = std::unique_ptr<OverrideBlend>(new OverrideBlend{});
        blending[BlendMode::AlphaBlend] = std::unique_ptr<AlphaBlend>(new AlphaBlend{});
    }

    void RenderQueue::Cache(Renderables& renderables, StencilBuffer& mask)
    {
        for (Renderable* renderable: renderables)
        {
            renderable->Cache(mask);
        }
    }

    void RenderQueue::Render(Renderables& renderables, PixelBuffer& buffer)
    {

        Renderable* renderable;
        Blending* blend;
        size_t size;
        for (int i{ (int) (renderables.size() - 1) }; i >= 0; --i)
        {

            renderable = renderables[i];
            blend = blending[renderable->GetBlend()].get();

            // TODO use buffer iteration (only relevant pixels)
            size = { buffer.size() };
            for (index_t p = 0; p < size; ++p)
            {
                if (renderable->CheckStencil(p))
                {
                    buffer[p] = blend->Blend(buffer[p], renderable->GetPixel(p));
                }
            }
        }
    }

    MoleDemo::RenderManager::RenderManager(Screen& screen, SDL::SDLManager& sdl) :
      m_screen{ screen }, sdl{ sdl }, queue{ new RenderQueue() }
    {
    }
    void MoleDemo::RenderManager::Lock()
    {
        sdl.LockSurface();
    }
    void MoleDemo::RenderManager::Unlock()
    {
        sdl.UnlockSurface();
    }
    void MoleDemo::RenderManager::Render()
    {
        sdl.UpdateSurface();
    }

    void MoleDemo::RenderManager::Init()
    {
        sdl.Init({ m_screen.w, m_screen.h });
        buffer.assign(size_t{ m_screen.GetPixelCount() }, black);
    }

    void MoleDemo::RenderManager::Finalize()
    {
        sdl.Finalize();
    }

    void MoleDemo::RenderManager::Draw(Renderables& renderables)
    {

        if (!renderables.empty() && BlendMode::Override != renderables.front()->GetBlend())
        {
            buffer.assign(size_t{ m_screen.GetPixelCount() }, black);
        }

        queue->Cache(renderables, mask);
        queue->Render(renderables, buffer);

        Lock();
        index_t i{ 0 };
        for (point1D y{ 0 }; y < m_screen.h; ++y)
        {
            for (point1D x{ 0 }; x < m_screen.w; ++x)
            {
                sdl.PutPixel(x, y, buffer[i]);
                i++;
            }
        }
        Render();
        Unlock();
    }

    StencilBuffer& MoleDemo::RenderManager::GetMask()
    {
        return mask;
    }
}
