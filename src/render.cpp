export module render;

import std;
import definitions;
import effects;
import renderables;
import sdl;

namespace MoleDemo {

	using size_t = std::size_t;
	export class RenderManager;

	class RenderQueue;
	struct Blending;
	struct OverrideBlend;
	struct AlphaBlend;
}

struct  MoleDemo::Blending {
	const BlendMode mode;
	virtual ~Blending() {}
	virtual rgbaColor Blend(const rgbaColor base, const rgbaColor next) = 0;
	virtual rgbaColor Blend(Color& base, Color& next) = 0;
protected:
	Blending(BlendMode mode) :
		mode{ mode } {}
};

struct  MoleDemo::OverrideBlend : public Blending {
	OverrideBlend() :
		Blending{ BlendMode::Override } {}
	~OverrideBlend() {}
	rgbaColor Blend(const rgbaColor base, const rgbaColor next) override {
		return next;
	}
	rgbaColor Blend(Color& base, Color& next) override {
		return next.rgba();
	};

};

struct  MoleDemo::AlphaBlend : public  MoleDemo::Blending {
	AlphaBlend() :
		Blending{ BlendMode::AlphaBlend } {}
	~AlphaBlend() {}

	rgbaColor Blend(const rgbaColor base, const rgbaColor next) override {
		Color ref_base{ base };
		Color ref_next{ next };
		return Blend(ref_base, ref_next);
	};
	rgbaColor Blend(Color& base, Color& next)  override {

		tempChannel aB{ base.a() };
		tempChannel rB{ base.r() };
		tempChannel gB{ base.g() };
		tempChannel bB{ base.b() };

		tempChannel aN{ next.a() };
		tempChannel rN{ next.r() };
		tempChannel gN{ next.g() };
		tempChannel bN{ next.b() };

		channel a{ (channel)(aN + (0xFF - aN) * aB / 0xFF) };
		channel r{ (channel)(a == 0x0 ? 0x0 : (rN * aN + rB * (0xFF - aN)) / a) };
		channel g{ (channel)(a == 0x0 ? 0x0 : (gN * aN + gB * (0xFF - aN)) / a) };
		channel b{ (channel)(a == 0x0 ? 0x0 : (bN * aN + bB * (0xFF - aN)) / a) };

		return Color(r, g, b, a).rgba();
	};
};

class  MoleDemo::RenderQueue {
	std::map<BlendMode, std::unique_ptr<Blending>> blending;
public:
	RenderQueue() {
		blending[BlendMode::Override] = std::make_unique<OverrideBlend>();
		blending[BlendMode::AlphaBlend] = std::make_unique<AlphaBlend>();
	}

	void Cache(Renderables& renderables, StencilBuffer& mask) {
		for (Renderable* renderable : renderables) {
			renderable->Cache(mask);
		}
	}

	void Render(Renderables& renderables, PixelBuffer& buffer) {

		Renderable* renderable;
		Blending* blend;
		size_t size;
		for (int i{ (int)(renderables.size() - 1) }; i >= 0; --i) {

			renderable = renderables[i];
			blend = blending[renderable->GetBlend()].get();

			// TODO use buffer iteration (only relevant pixels)
			size = { buffer.size() };
			for (index p = 0; p < size; ++p) {
				if (renderable->CheckStencil(p)) {
					buffer[p] = blend->Blend(buffer[p], renderable->GetPixel(p));
				}
			}
		}
	}
};

class  MoleDemo::RenderManager : public Initializable {
	public:

	RenderManager() = default;
	RenderManager(const RenderManager&) = default;
	RenderManager(RenderManager&&) = default;
	~RenderManager() = default;

	private:
	const Screen m_screen;
	RenderQueue* queue;
	PixelBuffer buffer;
	StencilBuffer mask;
	SDL::SDLManager sdl {};

	void Lock() {
		sdl.LockSurface();
	}
	void Unlock() {
		sdl.UnlockSurface();
	}
	void Render() {
		sdl.UpdateSurface();
	}
public:
	RenderManager(Screen screen) :
		m_screen{ screen },
		queue{ new RenderQueue() } {

	}
	void Init() {
		sdl.Init({ defaultScreen.w, defaultScreen.h });
		buffer.assign(size_t{ defaultScreen.GetPixelCount() }, black);
	}

	void Finalize() {
		sdl.Finalize();
	}

	void Draw(Renderables& renderables) {

		if (!renderables.empty() && BlendMode::Override != renderables.front()->GetBlend()) {
			buffer.assign(size_t{ m_screen.GetPixelCount() }, black);
		}

		queue->Cache(renderables, mask);
		queue->Render(renderables, buffer);

		Lock();
		index i{ 0 };
		for (point1D y{ 0 }; y < m_screen.h; ++y) {
			for (point1D x{ 0 }; x < m_screen.w; ++x) {
				sdl.PutPixel(x, y, buffer[i]);
				i++;
			}
		}
		Render();
		Unlock();
	}

	StencilBuffer& GetMask() {
		return mask;
	}
};
