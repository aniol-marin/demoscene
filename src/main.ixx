import demo;

int main()
{
	MoleDemo::Demo demo{ "project.json" };

	demo.Init();
	demo.Run();
	demo.Finalize();

	return 0;
}