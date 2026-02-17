#pragma once
#include <cstdint>
#include <vector>

namespace Horn {
	using VarID = uint32_t;

	struct Literal {
		bool is_positive;
		VarID var;
	};

	using Clause = std::vector<Literal>;
	using HornFormula = std::vector<Clause>;
	using Assignment = std::vector<bool>;
}
