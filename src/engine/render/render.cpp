module render;

import std;
import definitions;
import effect;
import renderables;
import sdl_wrapper;

using namespace mole_def;

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

	RenderManager() = delete;
	RenderManager(Screen& screen, SDL::SDLManager& sdl) :
		m_screen{ screen },
		sdl{ sdl },
		queue{ new RenderQueue() }
	{
	}
	RenderManager(const RenderManager&) = default;
	RenderManager(RenderManager&&) = default;
	~RenderManager() = default;

	private:
	const Screen m_screen;
	RenderQueue* queue;
	PixelBuffer buffer;
	StencilBuffer mask;
	SDL::SDLManager& sdl;

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
	void Init() {
		sdl.Init({ m_screen.w, m_screen.h });
		buffer.assign(size_t{ m_screen.GetPixelCount() }, black);
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
