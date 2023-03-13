export module demo;

import timeline;
import <string>;
import <thread>;

using namespace Temp;

namespace MoleDemo {


	export class Demo {
		Data data;
		std::thread mainThread;
		std::thread musicThread;
		std::thread loadingThread;
		Timeline timeline;
		void LoadData(std::string source) {}
		void LoadTimeline(std::string source) {	}
	public:
		Demo(std::string project) :
			data{ Point2D{640, 480},100, 100, 24 } {}

		void Init() {
			Temp::Init(data);
		}

		void Run() {

			while (data.Running()) {
				PollEvents(data);
				Update(data);
				Draw(data);
				Synch(data);
			}
		}

		void Finalize() {
			Temp::Finalize(data);
		}
	};

}