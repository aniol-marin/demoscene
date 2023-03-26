export module timeline;

import definitions;
import interfaces;
import timer;
import cycle;
import sound;
import program;
import render;
import <string>;
import <list>;
import <vector>;

namespace MoleDemo {
	export class Timeline :
		public Initializable,
		public Loadable {
		SoundManager* const sound;
		Screen* const screen;
		Timer* const timer;
		Program* const program;
		Cycle* const cycle;
		std::vector<Layer*> layers;
		std::list<std::pair<int_fast8_t, std::vector<Layer*>*>> events;
		void UpdateLayers(std::vector<Layer*>& newLayers) {

			std::vector<Layer*>* oldLayers = &layers;

			// unload previously loaded effects (no longer needed)
			for (Layer* oldLayer : *oldLayers) {
				std::vector<Layer*>::iterator unused = std::find(newLayers.begin(), newLayers.end(), oldLayer);
				if (unused != newLayers.end()) {
					(*unused)->effect->Unload();
				}
			}

			// load previously unloaded effects
			for (Layer* newLayer : newLayers) {
				std::vector<Layer*>::iterator unloaded = std::find(oldLayers->begin(), oldLayers->end(), newLayer);
				if (unloaded == oldLayers->end()) {
					newLayer->effect->Load();
				}
			}

			layers = newLayers;
		}
		void HandleTimeline() {

			if (!events.empty() && timer->GetTime() == events.front().first) {

				std::vector<Layer*>* nextLayers = events.front().second;
				UpdateLayers(*nextLayers);
				events.pop_front();
			}
				cycle->SetLayers(layers); // TODO check, redundant?
		}
	public:
		Timeline(Timer* timer, Program* program, Cycle* cycle, SoundManager* sound, Screen* screen) :
			timer{ timer },
			program{ program },
			cycle{ cycle },
			sound{ sound },
			screen{ screen },
			layers{} {}

		void Init() {
			cycle->SetLayers(layers); // TODO check, redundant?
		}

		void Load(std::string content) {
			// TODO load project from JSON

			Stars* stars = new Stars{ timer, screen };
			Plasma* plasma = new Plasma{ timer, screen };

			Layer* first = new Layer{ BlendMode::AlphaBlend, stars };
			Layer* second = new Layer{ BlendMode::Override, plasma };


			std::vector<Layer*> initialLayers{ first };
			events.push_back({ 2, new std::vector<Layer*>{ second} });
			events.push_back({ 6, new std::vector<Layer*>{first, second} });
			events.push_back({ 8, new std::vector<Layer*>{second, first} });
			events.push_back({ 12, new std::vector<Layer*>{first} });

			layers.insert(layers.end(), initialLayers.begin(), initialLayers.end());
			UpdateLayers(layers);
		}

		void Start() {
			timer->SetEndTime(sound->GetMusicDuration());
		}

		void Update() {

			HandleTimeline();

			cycle->PollEvents();
			cycle->Update(sound->GetCurrentIntensity());
			cycle->Draw();
			cycle->Synch();
		}

		void Unload() {}

		void Finalize() {
			/*
			for (Layer* layer : layers) {
				delete layer;
				layer = nullptr;
			}
			layers.clear();
			*/
		}
	};
}