all: build

build: 
	cmake -S . -B build && cmake --build build

test:
	./build/tests/gmpLearningTests

clean:
	rm -r build