main: run
	@echo main done

debug: build
	gdb ./bin/demoscene

build: generate
	cmake --build build --target demoscene

generate:
	cmake\
		-S.\
		-Bbuild\
		-GNinja\
		-DCMAKE_BUILD_TYPE=Debug
		--log-level=NOTICE

run: build
	./bin/demoscene

.PHONY: test
test:
	cmake --build build --target test
	./bin/test

clean:
	rm -rf build
	rm -rf lib
	rm -rf bin
