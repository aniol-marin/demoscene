#include "render.h"
#include "definitions.h"

using namespace mole_def;

namespace MoleDemo
{
    RenderQueue::RenderQueue()
    {
        blending[mole_def::BLEND_MODE_OVERRIDE] = new OverrideBlend();
        blending[mole_def::BLEND_MODE_ALPHABLEND] = new AlphaBlend();
    }

    RenderQueue::~RenderQueue()
    {
        for (std::map<BlendMode, Blending*>::iterator it = blending.begin(); it != blending.end(); ++it)
        {
            delete (it->second);
        }
        blending.clear();
    }

    void RenderQueue::Cache(Renderables& renderables, StencilBuffer& mask)
    {
        for (Renderables::iterator it = renderables.begin(); it != renderables.end(); ++it)
        {
            Renderable& renderable(**it);
            renderable.Cache(mask);
        }
    }

    void RenderQueue::Render(Renderables& renderables, PixelBuffer& buffer)
    {

        Renderable* renderable;
        Blending* blend;
        size_t size;
        for (int i = renderables.size() - 1; i >= 0; --i)
        {
            renderable = renderables[i];
            blend = blending[renderable->GetBlend()];

            // TODO use buffer iteration (only relevant pixels)
            size = size_t(buffer.size());
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
      m_screen(screen), sdl(sdl), queue(new RenderQueue())
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
        sdl.Init(mole_def::Screen(m_screen.w, m_screen.h));
        buffer.assign(size_t(m_screen.GetPixelCount()), 0x000000FF);
    }

    void MoleDemo::RenderManager::Finalize()
    {
        sdl.Finalize();
    }

    void MoleDemo::RenderManager::Draw(Renderables& renderables)
    {

        if (!renderables.empty() && mole_def::BLEND_MODE_OVERRIDE != renderables.front()->GetBlend())
        {
            buffer.assign(size_t(m_screen.GetPixelCount()), 0x000000FF);
        }

        queue->Cache(renderables, mask);
        queue->Render(renderables, buffer);

        Lock();
        index_t i(0);
        for (mole_def::point1D y(0); y < m_screen.h; ++y)
        {
            for (point1D x(0); x < m_screen.w; ++x)
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
