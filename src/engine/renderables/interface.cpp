export module renderables;

import std;
import definitions;
import effect;

using namespace mole_def;

namespace MoleDemo
{
    export struct Layer;

    export class Transition;
    export class Cut;
    export class Fade;
}

struct MoleDemo::Layer : public Renderable
{
    const BlendMode blend;
    Effect* const effect;

    Layer(BlendMode mode, Effect* effect);
    Layer(const Layer&) = delete;
    Layer(Layer&&) = default;
    ~Layer() = default;

    void Update(permille intensity, milliseconds deltaTime) override;
    void Cache(StencilBuffer& mask) override;
    rgbaColor GetPixel(Point2D point) override;
    rgbaColor GetPixel(index index) override;
    BlendMode GetBlend() override;
    bool CheckStencil(index offset) override;
};

class MoleDemo::Transition : public Renderable
{
    const TransitionType type;
    const Timestamp time;
    milliseconds m_elapsed{};

protected:
    Renderable* background{};
    Renderable* foreground{};

    Transition() = delete;
    explicit Transition(Timestamp time, TransitionType type);
    Transition(const Transition&) = delete;
    Transition(Transition&&) = default;

    permille elapsed() const;

public:
    virtual ~Transition() = default;

    void Bind(Renderable* background, Renderable* foreground);
    void Update(permille intensity, milliseconds deltaTime) final;
    bool IsDone();
    bool CheckStencil(index index) final;
};

class MoleDemo::Cut : public Transition
{
    Renderable* ActiveLayer();

public:
    Cut(Timestamp time);
    ~Cut() override = default;

    void Cache(StencilBuffer& mask) override;
    rgbaColor GetPixel(Point2D point) override;
    rgbaColor GetPixel(index index) override;
    BlendMode GetBlend() override;
};

class MoleDemo::Fade : public Transition
{
public:
    explicit Fade(Timestamp time);
    ~Fade() override = default;

    void Cache(StencilBuffer& mask) override;
    rgbaColor GetPixel(index index) override;
    rgbaColor GetPixel(Point2D point) override;
    BlendMode GetBlend() override;
};
