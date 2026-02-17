algorithm1:
	@mkdir -p build
	g++ -std=c++23 -O3 -Wall -Wextra -Wpedantic -march=native -o build/solver src/plaintext/Algorithm1.cpp && ./build/solver

algorithm2:
	@mkdir -p build
	g++ -std=c++23 -O3 -Wall -Wextra -Wpedantic -march=native -o build/solver src/plaintext/Algorithm2.cpp && ./build/solver

clean:
	rm -rf build

.PHONY: solver clean
