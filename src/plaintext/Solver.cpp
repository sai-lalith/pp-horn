#include <iostream>
#include <algorithm>
#include <optional>
#include "../common/Types.hpp"

// All negative literals
bool is_goal_clause (const Clause& c) {
	return std::all_of(c.cbegin(), c.cend(),
		    [](const Literal& lit){return !lit.sign;} );
}

// One positive literal
bool is_rule_clause (const Clause& c) {
	return std::any_of(c.cbegin(), c.cend(),
		    [](const Literal& lit){return lit.sign;});
}

bool negative_literals_satisfied(const Clause& c, const Assignment& assignments) {
	return std::all_of(c.cbegin(), c.cend(), 
	    [&assignments](const Literal& lit) {
	    return lit.sign || assignments.at(lit.letter);
	    }
	);
}

bool positive_literal_satisfied(const Clause& c, const Assignment& assignments) {
	return std::any_of(c.cbegin(), c.cend(), 
	    [&assignments](const Literal& lit) {
	    return lit.sign && assignments.at(lit.letter);
	    }
	);
}

std::optional<char> get_positive_literal(const Clause& c){
	auto pos_lit = std::find_if(c.cbegin(), c.cend(),
	      [](const Literal& lit) {
		return lit.sign;
	      }
	);
	return pos_lit != c.cend() ? std::optional<char>(pos_lit->letter) : std::nullopt;
}

void initalize_assignments (const HornFormula& S, Assignment& assignments) {
	for (const Clause& c : S) {
		if (c.size() == 1) {
			assignments[c[0].letter] = true; 
		}
	}
}

void print_result(bool satisfiable, const Assignment& assignments) {
	if (satisfiable) {
		std::cout << "The formula is satisfiable" << std::endl;
		std::cout << "The satisfying assignment is : " << std::endl;
		for (const auto& [key, value] : assignments) {
			std::cout << key << ": " << (value ? "true" : "false") << '\n';
		}	
	}
	else {
		std::cout << "The formula is not satisfiable";
	}
}

void algorithm1(HornFormula S, Assignment assignments) {

	bool consistent {true};
	bool change {true};


	while(change && consistent) {
		change = false;

		if (!consistent) {break;}
		for (auto it = S.begin(); it != S.end();) {
       			Clause& c = *it;
			if (is_goal_clause(c) && negative_literals_satisfied(c, assignments)) {
				consistent = false;
			}
			if(is_rule_clause(c)
			&& negative_literals_satisfied(c, assignments)
			&& !positive_literal_satisfied(c, assignments)) {
				auto letter = get_positive_literal(c);
				assignments[letter.value()] = true;
				it = S.erase(it);
				change = true;
				continue;
			}
       			++it;
		}
	}
	print_result(consistent, assignments);
}

int main() {
	// considerations:
	// we assume everything is in reduced format, meaning it's preprocessed already
	Assignment assignments = {
		{'a', false}, 
		{'b', false},
		{'c', false}
	};

	HornFormula S = {
		{{false, 'a'}, {false, 'b'}},
		{{false, 'b'}},
		{{false, 'c'}},
		{{true, 'a'}},
	}; // TODO: either CIN or fstream for more test cases, dimacs parser might be good
	
	algorithm1(S, assignments);
	return 0;
}
