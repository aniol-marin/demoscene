#ifndef MOLE_RENDERABLES_H
#define MOLE_RENDERABLES_H

#include "definitions.h"
#include "Effect.h"
using namespace mole_def;

namespace MoleDemo
{
	struct Layer : public Renderable
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
		rgbaColor GetPixel(mole_def::index index) override;
		BlendMode GetBlend() override;
		bool CheckStencil(mole_def::index offset) override;
	};

	class Transition : public Renderable
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
		bool CheckStencil(mole_def::index index) final;
	};

	class Cut : public Transition
	{
		Renderable* ActiveLayer();

		public:
		Cut(Timestamp time);
		~Cut() override = default;

		void Cache(StencilBuffer& mask) override;
		rgbaColor GetPixel(Point2D point) override;
		rgbaColor GetPixel(mole_def::index index) override;
		BlendMode GetBlend() override;
	};

	class Fade : public Transition
	{
		public:
			explicit Fade(Timestamp time);
			~Fade() override = default;

			void Cache(StencilBuffer& mask) override;
			rgbaColor GetPixel(mole_def::index index) override;
			rgbaColor GetPixel(Point2D point) override;
			BlendMode GetBlend() override;
	};
}
#endif
