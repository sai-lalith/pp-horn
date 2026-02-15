#pragma once
#include <vector>
#include <unordered_map>

struct Literal {
	bool sign;
	char letter;
};

using Clause = std::vector<Literal>;

using HornFormula = std::vector<Clause>;

using Assignment = std::unordered_map<char, bool>;


