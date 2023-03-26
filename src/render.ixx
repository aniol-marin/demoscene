export module render;

import definitions;
import interfaces;
import effects;
import sdl;
import <vector>;
import <map>;
import <memory>;

namespace MoleDemo {

	struct Blending {
		const BlendMode mode;
		virtual ~Blending() {}
		virtual const uint32_t Blend(const uint32_t base, const uint32_t next) const = 0;
	protected:
		Blending(BlendMode mode) :
			mode{ mode } {}
	};

	struct OverrideBlend : public Blending {
		OverrideBlend() :
			Blending{ BlendMode::Override } {}
		~OverrideBlend() {}
		const uint32_t Blend(const uint32_t base, const uint32_t next) const override {
			return next;
		};

	};

	struct AlphaBlend : public Blending {
		AlphaBlend() :
			Blending{ BlendMode::AlphaBlend } {}
		~AlphaBlend() {}
		const uint32_t Blend(const uint32_t base, const uint32_t next) const override {

			uint_fast16_t aB{ (base & 0xFF000000) >> 24 };
			uint_fast16_t rB{ (base & 0x00FF0000) >> 16 };
			uint_fast16_t gB{ (base & 0x0000FF00) >> 8 };
			uint_fast16_t bB{ (base & 0x000000FF) };

			uint_fast16_t aN{ (next & 0xFF000000) >> 24 };
			uint_fast16_t rN{ (next & 0x00FF0000) >> 16 };
			uint_fast16_t gN{ (next & 0x0000FF00) >> 8 };
			uint_fast16_t bN{ (next & 0x000000FF) };

			uint8_t a{ (uint8_t)(aN + (0xFF - aN) * aB / 0xFF) };
			uint8_t r{ (uint8_t)(a == 0x0 ? 0x0 : (rN * aN + rB * (0xFF - aN)) / a) };
			uint8_t g{ (uint8_t)(a == 0x0 ? 0x0 : (gN * aN + gB * (0xFF - aN)) / a) };
			uint8_t b{ (uint8_t)(a == 0x0 ? 0x0 : (bN * aN + bB * (0xFF - aN)) / a) };

			uint32_t result{ (uint32_t)(
				(a << 24) |
				(r << 16) |
				(g << 8) |
				b) };

			return result;
		};

	};

	export struct Layer {
		const BlendMode blend;
		Effect* const effect;
		Layer(BlendMode mode, Effect* effect) :
			blend{ mode },
			effect{ effect } {}
		~Layer() {
			delete effect;
		}
	};

	class RenderQueue {
		std::map<BlendMode, std::unique_ptr<Blending>> blending;
	public:
		RenderQueue() {
			blending[BlendMode::Override] = std::make_unique<OverrideBlend>();
			blending[BlendMode::AlphaBlend] = std::make_unique<AlphaBlend>();
		}

		void Render(std::vector<Layer*>& layers, std::vector<uint32_t>& buffer) {

			// TODO limit render by stencil
			Layer* layer;
			for (int_fast8_t i{ (int_fast8_t)(layers.size() - 1) }; i >= 0; --i) {

				// TODO use buffer iteration (only relevant pixels)
				layer = layers[i];
				std::vector<uint32_t>& next = layer->effect->GetBuffer();
				Blending* blend = blending[layer->blend].get();

				uint_fast32_t size = (uint_fast32_t)buffer.size();
				for (uint_fast32_t p = 0; p < size; ++p) {
					buffer[p] = blend->Blend(buffer[p], next[p]);
				}
			}
		}
	};

	export class RenderManager : public Initializable {
		Screen* const screen;
		RenderQueue* queue;
		std::vector<uint_fast32_t> buffer;
		std::vector<bool> mask;
		void Lock() { SDL::LockSurface(); }
		void Unlock() { SDL::UnlockSurface(); }
		void Render() { SDL::UpdateSurface(); }
	public:
		RenderManager(Screen* screen) :
			screen{ screen },
			queue{ new RenderQueue() } {

		}
		void Init() {
			SDL::Init(*screen);
			buffer.assign(size_t{ (uint_fast16_t)screen->w * (uint_fast16_t)screen->h }, uint32_t{ 0xFF000000 });
		}

		void Finalize() {
			SDL::Finalize();
		}

		void Draw(std::vector<Layer*>& layers) {

			if (BlendMode::Override != layers.front()->blend) {
				buffer.assign(size_t{ (uint_fast16_t)screen->w * (uint_fast16_t)screen->h }, uint32_t{ 0xFF000000 });
			}
			
			queue->Render(layers, buffer);

			Lock();
			uint_fast32_t i{ 0 };
			for (uint_fast16_t y{ 0 }; y < screen->h; ++y) {
				for (uint_fast16_t x{ 0 }; x < screen->w; ++x) {
					SDL::PutPixel(x, y, buffer[i]);
					i++;
				}
			}
			Render();
			Unlock();
		}

		std::vector<bool>& GetMask() { return mask; }
	};
}