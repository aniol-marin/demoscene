import demo;

int main()
{
	MoleDemo::Demo demo{ "project.json" }; // TODO load from project timeline

	demo.Init();
	demo.Run();
	demo.Finalize();

	return 0;
}