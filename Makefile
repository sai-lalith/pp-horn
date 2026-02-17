solver:
	@mkdir -p build
	g++ -std=c++23 -O3 -Wall -Wextra -Wpedantic -march=native -o build/solver src/plaintext/Solver.cpp && ./build/solver

clean:
	rm -rf build

.PHONY: solver clean
