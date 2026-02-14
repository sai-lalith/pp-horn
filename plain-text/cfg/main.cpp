#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>
#include <ranges>

struct literal {
	bool sign;
	char letter;
};

using clause = std::vector<literal>;

using horn_formula = std::vector<clause>;

bool check_type_goal (clause c) {
	bool type_goal {true};

	for (literal& l : c) {
		if (l.sign) {
			type_goal = false;
			break;
		}
	}
	return type_goal;
}

bool check_type_rule (clause c) {
	bool type_goal {false};

	for (literal& l : c) {
		if (l.sign) {
			type_goal = true;
			break;
		}
	}
	return type_goal;
}

bool check_assignment_true_for_neg (clause c, std::unordered_map<char, bool> assignments) {
	for (literal& l : c) {
		if(!l.sign && ! (assignments[l.letter] == true)) {return false;}
	}
	return true;
}

bool check_assignment_true_for_pos (clause c, std::unordered_map<char, bool> assignments) {
	for (literal& l : c) {
		if(l.sign && ! (assignments[l.letter] == true)) {return false;}
	}
	return true;
}

char pos_assignment_letter (clause c){ 
	for (size_t i = 0; i < c.size(); ++i){
		if(c[i].sign) {
			return c[i].letter;
		}
	}
}

int main() {
	// considerations:
	// we assume everything is in reduced format, meaning it's preprocessed already

	bool consistent {true};
	bool change {true};

	std::unordered_map<char, bool> assignments = {
		{'a', true}, 
		{'b', false},
		{'c', false}
	}; // initialized with truth pebbles to be true TODO: Write code to do this automatically

	horn_formula S = {
		{{true, 'a'}, {false, 'b'}},
		{{false, 'b'}},
		{{false, 'c'}}
	}; // TODO: either CIN or fstream for more test cases, dimacs parser might be good
	
	while(change && consistent) {
		change = false;

		if (!consistent) {break;}
		for (auto it = S.begin(); it != S.end();) {
       			clause& c = *it;
			if (check_type_goal(c) && check_assignment_true_for_neg(c, assignments)) {
				consistent = false;
			}
			else{
				if(check_type_rule(c) && check_assignment_true_for_neg(c, assignments)
				&& !check_assignment_true_for_pos(c, assignments)) {
					assignments[pos_assignment_letter(c)] = true;
					it = S.erase(it);
					change = true;
					continue;
				}
			}
       			++it;
		}
	}
	
	if (consistent) {
		std::cout << "The formula is satisfiable" << std::endl;
		std::cout << "The satisfying assignment is : " << std::endl;
		for (const auto& [key, value] : assignments) {
			std::cout << key << ": " << (value ? "true" : "false") << '\n';
		}	
	}
	else {
		std::cout << "The formula is not satisfiable";
	}

	return 0;
}
