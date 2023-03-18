export module demo;

import timeline;
import injection;
import <string>;
import <thread>;

//debugging
import <iostream>;

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
		void InstallBindings() {
			Container container{};
			//container.BindUnique<Point2D, Point2D>();
			container.BindShared<Point2D, Point3D>();
			Point2D* point = container.InjectShared<Point2D>();
			Point2D* point2 = container.InjectShared<Point2D>();
			Point2D* point3 = container.InjectShared<Point2D>(1);

			std::cout << "uninitialized: [" << point->x << "][" << point->y << "]\n";
			std::cout << "uninitialized: [" << point2->x << "][" << point2->y << "]\n";
			std::cout << "uninitialized: [" << point3->x << "][" << point3->y << "]\n";

			point->x = 4;
			point2->y = 5;
			point3->x = 37;
			point3->y = 37;


			std::cout << "initialized: [" << point->x << "][" << point->y << "]\n";
			std::cout << "initialized: [" << point2->x << "][" << point2->y << "]\n";
			std::cout << "initialized: [" << point3->x << "][" << point3->y << "]\n";


			point->x = 4;
			/*
			std::unique_ptr<Point2D> uPoint1 = container.InjectNewInstance<Point2D>();
			std::unique_ptr<Point2D> uPoint2 = container.InjectNewInstance<Point2D>();
			*/
			/*
			std::shared_ptr<Point2D> sPoint1 = container.InjectSharedInstance<Point2D>();
			std::shared_ptr<Point2D> sPoint2 = container.InjectSharedInstance<Point2D>();
			std::shared_ptr<Point2D> sPoint3 = container.InjectSharedInstance<Point2D>(1);
			*/

			//point->x = 5;

			//std::cout << std::string("point: [") << (int)point->x << "][" << (int)point->y << "]" << std::endl;

			//container.BindShared<Star, Star>(); //ok
			//container.BindUnique<Star, Star>(); //ok
			//container.BindSharingFactory<Star, Star, Screen, uint8_t, const int>(); // WIP
			//container.BindNewInstancesFactory<Star, Star, Screen, uint8_t, const int>(); // TODO
		}
	public:
		Demo(std::string project) :
			data{ Point2D{640, 480},100, 100, 24 } {}

		void Init() {
			InstallBindings();
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