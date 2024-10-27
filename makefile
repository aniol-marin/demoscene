build: generate
	cmake --build build

generate:
	cmake -Bbuild -GNinja -D CMAKE_CXX_COMPILER=/usr/bin/g++-14

run: build
	./bin/demoscene

changes:
	cd src/; vim; cd ..
clean:
	git clean -fdx
