export module input;

import definitions;
import sdl;

namespace MoleDemo {

	export struct InputManager;
}

struct MoleDemo::InputManager {
	ProgramStatus PollEvents() {
		return SDL::PollSDLEvents();
	}
};