#ifndef MOLE_RENDERABLES_H
#define MOLE_RENDERABLES_H

#include "Effect.h"
#include "definitions.h"
using namespace mole_def;

namespace MoleDemo
{
    struct Layer : public Renderable
    {
        const BlendMode blend;
        Effect* const effect;

        Layer(BlendMode mode, Effect* effect);
        ~Layer() {}

        void Update(permille intensity, milliseconds deltaTime);
        void Cache(StencilBuffer& mask);
        rgbaColor GetPixel(Point2D point);
        rgbaColor GetPixel(index_t index);
        BlendMode GetBlend();
        bool CheckStencil(index_t offset);
    };

    class Transition : public Renderable
    {
        const TransitionType type;
        const Timestamp time;
        milliseconds m_elapsed;

    protected:
        Renderable* background;
        Renderable* foreground;

        Transition() : type(), time(), m_elapsed(), background(), foreground() {}
        explicit Transition(Timestamp time, TransitionType type);
        Transition(const Transition& other) :
          type(other.type),
          time(other.time),
          m_elapsed(other.m_elapsed),
          background(other.background),
          foreground(other.foreground)
        {
        }

        permille elapsed() const;

    public:
        virtual ~Transition() {}

        void Bind(Renderable* background, Renderable* foreground);
        void Update(permille intensity, milliseconds deltaTime);
        bool IsDone();
        bool CheckStencil(index_t index);
    };

    class Cut : public Transition
    {
        Renderable* ActiveLayer();

    public:
        Cut(Timestamp time);
        ~Cut() {}

        void Cache(StencilBuffer& mask);
        rgbaColor GetPixel(Point2D point);
        rgbaColor GetPixel(index_t index);
        BlendMode GetBlend();
    };

    class Fade : public Transition
    {
    public:
        explicit Fade(Timestamp time);
        ~Fade() {}

        void Cache(StencilBuffer& mask);
        rgbaColor GetPixel(index_t index);
        rgbaColor GetPixel(Point2D point);
        BlendMode GetBlend();
    };
}
#endif
