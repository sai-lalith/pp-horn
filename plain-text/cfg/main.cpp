#include <iostream>
#include <vector>

struct literal {
	bool sign;
	char letter;
};

using clause = std::vector<literal>;

using horn_formula = std::vector<clause>;

int main() {
	int K = 10; // K denotes number of unique variables
	int M = 10; // M denotes clauses
	bool consistent, change;
	std::vector<bool> V (K, true);
	std::cout << V[1];
	return 0;
}
