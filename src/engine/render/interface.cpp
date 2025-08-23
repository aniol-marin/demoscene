export module render;

import std;
import definitions;
import effect;
import renderables;
import sdl;

namespace MoleDemo
{
	using size_t = std::size_t;
	export class RenderManager;

	class RenderQueue;
	struct Blending;
	struct OverrideBlend;
	struct AlphaBlend;
}


class MoleDemo::RenderManager : public Initializable
{
		const Screen m_screen;
		RenderQueue* queue;
		PixelBuffer buffer;
		StencilBuffer mask;
		SDL::SDLManager& sdl;

		void Lock();
		void Unlock();
		void Render();

	public:
		RenderManager() = delete;
		RenderManager(Screen& screen, SDL::SDLManager& sdl);
		RenderManager(const RenderManager&) = default;
		RenderManager(RenderManager&&) = default;
		~RenderManager() = default;

		void Init();
		void Finalize();
		void Draw(Renderables& renderables);
		StencilBuffer& GetMask();
};

