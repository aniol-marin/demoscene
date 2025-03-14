main: run
	@echo main done

build: generate
	cmake --build build --target demoscene

generate:
	@#workaround
	mkdir -p ./build
	mkdir -p ./build/_deps
	mkdir -p ./build/_deps/raudio-src
	cp ./resources/CMakeLists.txt ./build/_deps/raudio-src/CMakeLists.txt
	@#end workaround
	cmake\
		-S.\
		-Bbuild\
		-GNinja\
		--log-level=NOTICE

run: build
	./bin/demoscene

clean:
	rm -rf build
	rm -rf lib
	rm -rf bin
