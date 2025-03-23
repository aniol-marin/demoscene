module;

#include <vector> // required while including due to unexported symbols

export module cycle;

import definitions;
import effects;
import renderables;
import timer;
import program;
import input;
import render;

namespace MoleDemo {

	export class Cycle;
}

class MoleDemo::Cycle {
	Renderables renderables {};
	Program& program;
	Timer& timer;
	InputManager& inputManager;
	RenderManager& renderManager;
public:
	Cycle(Program& program, Timer& timer, InputManager& input, RenderManager& render) :
		program{ program },
		inputManager{ input },
		renderManager{ render },
		timer{ timer } {}

	void PollEvents() {
		if (timer.EndReached()) {
			program.SetStatus(ProgramStatus::TERMINATE_OK);
		}
		else {
			program.SetStatus(inputManager.PollEvents());
		}
	}

	void Update(permille intensity) {
		for(Renderable* renderable : renderables )
		{
			renderable->Update(intensity, timer.GetDeltaTime());
		}
	}

	void Draw() {
		renderManager.Draw(renderables);
	}

	void Synch() {
		timer.WaitUntilNextFrame();
	}

	void SetRenderables(const Renderables& aRenderables)
	{
		renderables.clear();
		renderables.insert(renderables.begin(), aRenderables.cbegin(), aRenderables.cend());
	}
};
