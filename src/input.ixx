export module input;

import definitions;
import sdl;

export struct InputManager {
	ProgramStatus PollEvents() {
		return SDL::PollSDLEvents();
	}
};