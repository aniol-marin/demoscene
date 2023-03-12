

import demo;

int main(int argc, char* args[])
{
	MoleDemo::Demo demo{"project.json"};

	demo.Init();
	demo.Run();
	demo.Finalize();

	return 0;
}
