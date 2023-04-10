module;
#include <SDL.h>

export module sdl;

import definitions;
import <string>;
import <iostream>;

namespace SDL {

	export bool InitAudio();
	export void FinalizeAudio();

	export bool InitVideo(const Screen& screen);
	export void FinalizeVideo();

	export ProgramStatus PollSDLEvents();

	export void LockSurface();
	export void UnlockSurface();
	export void UpdateSurface();
	export void PutPixel(uint16_t x, uint16_t y, const uint32_t rgba);

	export void LoadMusic(std::string source);
	export void PlayMusic();
	export Uint16 GetMusicDuration();
	export Uint16 GetMusicIntensity();

	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event events;

	SDL_AudioDeviceID audioDeviceId;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	using Pixel = uint32_t;
	Pixel* getPixel(uint16_t x, uint16_t y);
}

bool SDL::InitAudio() {

	return 0 != SDL_InitSubSystem(SDL_INIT_AUDIO);
}

void SDL::FinalizeAudio() {

	SDL_CloseAudioDevice(audioDeviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool SDL::InitVideo(const Screen& screen) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) >= 0) {

		window = SDL_CreateWindow("Mole Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
		surface = SDL_GetWindowSurface(window);
	}

	return window != nullptr;
}

void SDL::FinalizeVideo() {
	SDL_DestroyWindow(window);
	SDL_Quit(); // assumes video is the last
}

ProgramStatus SDL::PollSDLEvents() {
	ProgramStatus status = ProgramStatus::RUNNING;
	while (SDL_PollEvent(&events) != 0)
	{
		if (events.type == SDL_KEYDOWN) {
			if (events.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				status = ProgramStatus::TERMINATE_OK;
			}
		}
		//User requests quit
		if (events.type == SDL_QUIT)
		{
			status = ProgramStatus::TERMINATE_OK;
		}
	}

	return status;
}

void SDL::LockSurface() {
	SDL_LockSurface(surface);
}

void SDL::UnlockSurface() {
	SDL_UnlockSurface(surface);
}

void SDL::UpdateSurface() {
	SDL_UpdateWindowSurface(window);
}

SDL::Pixel* SDL::getPixel(uint16_t x, uint16_t y) {
	return reinterpret_cast<uint32_t*>((uint8_t*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
}

void SDL::PutPixel(uint16_t x, uint16_t y, const uint32_t rgba) {
	Pixel* pixel = getPixel(x, y);
	*pixel = rgba;
}

void SDL::LoadMusic(std::string source) {

	SDL_LoadWAV(source.c_str(), &wavSpec, &wavBuffer, &wavLength);
	audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	std::cout << "id: " << (int)audioDeviceId << "\n";
}

void SDL::PlayMusic() {
	SDL_QueueAudio(audioDeviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(audioDeviceId, 0);
	std::cout << "buffer " << (int)wavBuffer << "\n";
	std::cout << "length " << (int)wavLength << "\n";
}


export Uint16  SDL::GetMusicDuration() {
	return 255; // wavLength;
}
export Uint16  SDL::GetMusicIntensity() {
	return 1000;
}