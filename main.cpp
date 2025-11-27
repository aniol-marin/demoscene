#include <iostream>
#include "./messages.pb.h"

int main()
{
	test::Hello h {};
	h.set_world("hi");
	std::cout << h.DebugString();
}

