export module cycle;

import definitions;
import effects;
import timer;
import program;
import input;
import render;
import <vector>;

namespace MoleDemo {
	export class Cycle {
		std::vector<Layer*> layers;
		Program* const program;
		Timer* const timer;
		InputManager* const inputManager;
		RenderManager* const renderManager;
	public:
		Cycle(Program* program, Timer* timer, InputManager* input, RenderManager* render) :
			program{ program },
			inputManager{ input },
			renderManager{ render },
			timer{ timer } {}

		void PollEvents() {
			if (timer->EndReached()) {
				program->SetStatus(ProgramStatus::TERMINATE_OK);
			}
			else {
				program->SetStatus(inputManager->PollEvents());
			}
		}

		void Update(uint_fast16_t intensity) {
			for (Layer* layer : layers) {
				layer->effect->Update(intensity);
			}
		}

		void Draw() {
			for (Layer* layer : layers) {
				layer->effect->Cache(renderManager->GetMask());
			}

			renderManager->Draw(layers);
		}

		void Synch() {
			timer->WaitUntilNextFrame();
		}

		void SetLayers(std::vector<Layer*>& layers) {
			this->layers = layers;
		}
	};
}