all: build test

build: 
	cmake -S . -B build && cmake --build build

test:
	./build/gmp_test

clean:
	rm -r build