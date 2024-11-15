build: generate
	cmake --build build

generate:
	cmake -Bbuild -GNinja -D CMAKE_CXX_COMPILER=/usr/local/bin/g++

run: build
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64/
	./bin/demoscene

changes:
	cd src/; vim; cd ..

save:
	git add .
	git commit
	git push

clean:
	git clean -fdx
