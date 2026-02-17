#include <iostream>
#include <algorithm>
#include <optional>
#include "../common/Types.hpp"

using namespace Horn;

// All negative literals
bool is_goal_clause (const Clause& c) {
	return std::all_of(c.cbegin(), c.cend(),
		    [](const Literal& lit){return !lit.is_positive;} );
}

// One positive literal
bool is_rule_clause (const Clause& c) {
	return std::any_of(c.cbegin(), c.cend(),
		    [](const Literal& lit){return lit.is_positive;});
}

bool negative_literals_satisfied(const Clause& c, const Assignment& assignments) {
	return std::all_of(c.cbegin(), c.cend(), 
	    [&assignments](const Literal& lit) {
	    return lit.is_positive || assignments[lit.var];
	    }
	);
}

bool positive_literal_satisfied(const Clause& c, const Assignment& assignments) {
	return std::any_of(c.cbegin(), c.cend(), 
	    [&assignments](const Literal& lit) {
	    return lit.is_positive && assignments[lit.var];
	    }
	);
}

std::optional<VarID> get_positive_literal(const Clause& c){
	auto pos_lit = std::find_if(c.cbegin(), c.cend(),
	      [](const Literal& lit) {
		return lit.is_positive;
	      }
	);
	return pos_lit != c.cend() ? std::optional<VarID>(pos_lit->var) : std::nullopt;
}

void print_result(bool satisfiable, const Assignment& assignments) {
	if (satisfiable) {
		std::cout << "The formula is satisfiable \nAssignment: \n";
		for(size_t i=1; i < assignments.size(); ++i) {
			std::cout << "Variable "<< i << " : " <<  
				 (assignments[i] ? "true" : "false") << '\n';
        	}
        	std::cout << "\n";
	} 

	else {
		std::cout << "The formula is not satisfiable \n";
	}
}

void HornSat(HornFormula S, Assignment assignments) {

	bool consistent {true};
	bool change {true};


	while(change && consistent) {
		change = false;

		if (!consistent) {break;}
		for (auto it = S.begin(); it != S.end();) {
       			Clause& c = *it;
			if (is_goal_clause(c) && negative_literals_satisfied(c, assignments)) {
				consistent = false;
				break;
			}
			if(is_rule_clause(c)
			&& negative_literals_satisfied(c, assignments)
			&& !positive_literal_satisfied(c, assignments)) {
				auto letter = get_positive_literal(c);
				assignments[letter.value()] = true;
				it = S.erase(it); // TODO: Time complexity concern here
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
	int num_vars = 4; // TODO:Should be automated and part of the parser 

	Assignment assignments(num_vars + 1, false);

	HornFormula S = {
		{{false, 1}, {false, 2}},
		{{false, 2}},
		{{false, 3}},
		{{true, 4}}
	}; // TODO: either CIN or fstream for more test cases, dimacs parser might be good
	
	HornSat(S, assignments);
	return 0;
}
