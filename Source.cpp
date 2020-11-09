#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_set>

using std::cin;
using std::vector;
using std::stack;
using std::pair;

class MyProblemSolver {

public:
	std::string ans;
	MyProblemSolver(const std::string& reg_expr) {
		if (!_parse_input(reg_expr, _reg_expression, _target_c, _n)) {
			ans = "ERROR";
		}
		_solve();
	}

private:
	
	struct _vertex {
		bool can_skip = 0;
		int index;

		vector<int> remainders;

		_vertex(int _index, std::vector<int> _rem) : index(_index) {
			for (int val : _rem) {
				remainders.push_back(val);
			}
		}
	};

	void _delete_duplicates(int ind) {
		//_all_vetrices[ind].remainders.resize(std::unique(_all_vetrices[ind].remainders.begin(), _all_vetrices[ind].remainders.end()) - _all_vetrices[ind].remainders.begin());

		std::unordered_set<int> sett;
		for (int elem : _all_vetrices[ind].remainders)
			sett.insert(elem);

		_all_vetrices[ind].remainders.clear();
		for (int elem : sett) {
			_all_vetrices[ind].remainders.push_back(elem);
		}
	}

	bool _parse_input(std::string str, std::string& automat, char& c, int& n) {

		while (str.size() > 0 && str.back() == ' ') {
			str.pop_back();
		}

		std::string number;

		int index = (int)str.size() - 1;
		for (; index >= 0; --index) {
			if (str[index] >= '0' && str[index] <= '9') {
				number += str[index];
			}
			else {
				break;
			}
		}

		if (number.size() == 0) {
			return 0;
		}

		reverse(number.begin(), number.end());

		n = 0;
		for (int i = 0; i < number.size(); ++i) {
			n *= 10;
			n += (number[i] - '0');
		}

		if (index - 1 < 0)
			return 0;

		c = str[index - 1];
		if (!(c >= 'a' && c <= 'z')) {
			return 0;
		}

		for (int i = 0; i < index - 1; ++i) {
			automat += str[i];
		}

		return 1;
	}


	vector<_vertex> _all_vetrices;
	std::string _reg_expression;
	char _target_c;
	int _n;
	int _cnt_vert = 0;
	stack<pair<int, int>> _st;

	void _multiply() {
		
		if (_st.size() < 2) {
			ans = "ERROR";
			return;
		}
		pair<int, int> high = _st.top();
		_st.pop();
		pair<int, int> low = _st.top();
		_st.pop();

		// ind1 -> low.first -> ... -> low.second ------> high.first -> .... -> high.second -> ind2

		int ind1 = _cnt_vert++;
		int ind2 = _cnt_vert++;

		_all_vetrices.push_back({ ind1, {} });
		_all_vetrices.push_back({ ind2, {} });

		if (_all_vetrices[high.second].can_skip && _all_vetrices[low.second].can_skip) {
			_all_vetrices[ind2].can_skip = 1;
		}

		for (int s1 : _all_vetrices[low.second].remainders) {
			for (int s2 : _all_vetrices[high.second].remainders) {
				_all_vetrices[ind2].remainders.push_back((s1 + s2) % _n);
			}
		}
		if (_all_vetrices[high.second].remainders.empty() || _all_vetrices[high.second].can_skip) {
			for (int s1 : _all_vetrices[low.second].remainders)
				_all_vetrices[ind2].remainders.push_back(s1);
		}
		if (_all_vetrices[low.second].remainders.empty() || _all_vetrices[low.second].can_skip) {
			for (int s2 : _all_vetrices[high.second].remainders)
				_all_vetrices[ind2].remainders.push_back(s2);
		}

		_delete_duplicates(ind2);

		_st.push({ ind1, ind2 });
	}

	void _addition() {  // yes
		if (_st.size() < 2) {
			ans = "ERROR";
			return;
		}
		pair<int, int> high = _st.top();
		_st.pop();
		pair<int, int> low = _st.top();
		_st.pop();

		int new_first_node = _cnt_vert++;
		_all_vetrices.push_back({ new_first_node, {0} });


		//                     low.first -> ... -> low.second 
		// new_first_node ->                                    -> new_second_node
		//                     high.first -> .. -> high.second

		int new_second_node = _cnt_vert++;
		_all_vetrices.push_back({ new_second_node, {} });

		for (int elem : _all_vetrices[low.second].remainders)
			_all_vetrices[new_second_node].remainders.push_back(elem);

		for (int elem : _all_vetrices[high.second].remainders)
			_all_vetrices[new_second_node].remainders.push_back(elem);

		_delete_duplicates(new_second_node);

		if (_all_vetrices[low.second].can_skip && _all_vetrices[high.second].can_skip) {
			_all_vetrices[new_second_node].can_skip = 1;
		}

		_st.push({ new_first_node, new_second_node });
	}

	void _klinis_star() {
		if (_st.empty()) {
			ans = "ERROR";
			return;
		}

		int ind_lower = _st.top().first;
		int ind_higher = _st.top().second;

		int ind1 = _cnt_vert++;
		int ind2 = _cnt_vert++;

		// ind1 -> ind_lower ------> ind_higher -> ind2

		_all_vetrices.push_back(_vertex(ind1, _all_vetrices[ind_lower].remainders));
		_all_vetrices.push_back(_vertex(ind2, _all_vetrices[ind_higher].remainders));

		pair<int, int> prev = { ind1, ind2 };
		for (int iter = 0; iter < _n * _n; ++iter) { //_st.push({ ind1, ind2 });
			_st.push(_st.top());
			_st.push({ ind1, ind2 });
			_multiply();
			_addition();
		}

		_all_vetrices[_st.top().second].can_skip = 1;
	}

	void _solve() {
		for (char c : _reg_expression) {
			if (c == '1') {
				int ind1 = _cnt_vert++;
				int ind2 = _cnt_vert++;

				_all_vetrices.push_back(_vertex(ind1, {}));
				_all_vetrices.push_back(_vertex(ind2, {}));
				_all_vetrices[ind2].can_skip = 1;

				_st.push({ ind1, ind2 });
			}
			else if (c == 'a' || c == 'b' || c == 'c') { // yes
				int ind1 = _cnt_vert++;
				int ind2 = _cnt_vert++;

				_all_vetrices.push_back(_vertex(ind1, {}));
				if (c == _target_c) {
					_all_vetrices.push_back(_vertex(ind2, { 1 }));
				}
				else {
					_all_vetrices.push_back(_vertex(ind2, {}));
				}

				_st.push({ ind1, ind2 });
			}
			else if (c == '*') {  // no
				_klinis_star();
			}
			else if (c == '.') {
				_multiply();
			}
			else if (c == '+') {
				_addition();
			}
			else if (c == ' ') {
				continue;
			}
			else {
				ans = "ERROR";
				return;
			}
		}
		if (_st.size() > 1) {
			ans = "ERROR";
		}

		if (ans != "ERROR") {
			ans = "NO";
			for (int elem : _all_vetrices[_st.top().second].remainders) {
				if (elem % _n == 0) {
					ans = "YES";
				}
			}
		}
	}
};

int getAnswer(const std::string &input_line) {
 
	MyProblemSolver solver(input_line);

	if (solver.ans == "YES")
           return  1;
        if (solver.ans == "NO")
           return 0;
        return -1;
}

/*
aa+ b 1

ab + * a 5

ab + c.aba. * .bac. + . 2

aba.+ b 1



ab + c.aba. * .bac. + . + * a 2
aba. * .a. * ab1 + .. a 2
*/
