#include "renderables.h"

namespace MoleDemo
{
    using namespace mole_def;
    Layer::Layer(BlendMode mode, Effect* effect) : blend{ mode }, effect{ effect } {}

    void Layer::Update(permille intensity, milliseconds deltaTime)
    {
        effect->Update(intensity, deltaTime);
    }

    void Layer::Cache(StencilBuffer& mask)
    {
        effect->Cache(mask);
    }

    rgbaColor Layer::GetPixel(Point2D point)
    {
        return effect->GetPixel(point);
    }

    rgbaColor Layer::GetPixel(index_t index)
    {
        return effect->GetPixel(index);
    }

    BlendMode Layer::GetBlend()
    {
        return blend;
    }

    bool Layer::CheckStencil(index_t offset)
    {
        // TODO buffer relevant content
        return true;
    }

    Transition::Transition(Timestamp time, TransitionType type) : type{ type }, time{ time } {}

    permille Transition::elapsed() const
    {
        return m_elapsed * permilleFactor / time.duration;
    }

    void Transition::Bind(Renderable* background, Renderable* foreground)
    {
        this->background = background;
        this->foreground = foreground;
    }

    void Transition::Update(permille intensity, milliseconds deltaTime)
    {
        m_elapsed += deltaTime;
    }

    bool Transition::IsDone()
    {
        return m_elapsed > time.duration;
    }

    bool Transition::CheckStencil(index_t index)
    {
        return true; // transitions by now are always be full screen
    }

    Renderable* Cut::ActiveLayer()
    {
        return IsDone() ? foreground : background;
    }

    Cut::Cut(Timestamp time) : Transition{ time, TransitionType::Cut } {}

    void Cut::Cache(StencilBuffer& mask)
    {
        background->Cache(mask);
        foreground->Cache(mask);
    }

    rgbaColor Cut::GetPixel(Point2D point)
    {
        return ActiveLayer()->GetPixel(point);
    }

    rgbaColor Cut::GetPixel(index_t index)
    {
        return ActiveLayer()->GetPixel(index);
    }

    BlendMode Cut::GetBlend()
    {
        return ActiveLayer()->GetBlend();
    }

    Fade::Fade(Timestamp time) : Transition{ time, TransitionType::Fade } {}

    void Fade::Cache(StencilBuffer& mask)
    {
        background->Cache(mask);
        foreground->Cache(mask);
    }

    rgbaColor Fade::GetPixel(index_t index)
    {
        Color next{ foreground->GetPixel(index) };
        rgbaColor result;

        if (!IsDone())
        {
            Color base{ background->GetPixel(index) };
            result = base.lerp(next, elapsed()).rgba();
        }
        else
        {
            result = next.rgba();
        }

        return result;
    }

    rgbaColor Fade::GetPixel(Point2D point)
    {
        rgbaColor result;
        Color next{ foreground->GetPixel(point) };

        if (!IsDone())
        {
            Color base{ background->GetPixel(point) };
            result = base.lerp(next, elapsed()).rgba();
        }
        else
        {
            result = next.rgba();
        }

        return result;
    }

    BlendMode Fade::GetBlend()
    {
        return background->GetBlend();
    }
}
