main: run
	@echo main done

build: generate
	cmake --build build --target demoscene

generate:
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
