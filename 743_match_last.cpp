#include <stack>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#define SUCCESS 0
using std::cin;
using std::cout;
using std::stack;
using std::string;
using std::vector;
using std::pair;
using std::getline;

stack<pair<char, int>> reverse(stack<pair<char, int>> old_stack) {
	stack<pair<char, int>> new_stack;
	while (!old_stack.empty()) {
		new_stack.push(old_stack.top());
		old_stack.pop();
	}
	return new_stack;
}

int find_unmatched(string s) {
	stack<pair<char, int>> visited_brackets;
	if (s.empty()) {
		return SUCCESS;
	}
	for (int i = 0; i != s.length(); ++i) {
		if (s.at(i) == '(' || s.at(i) == '[' || s.at(i) == '{') {
			visited_brackets.push(pair<char, int>(s.at(i), i));
		}
		else if (s.at(i) == ')' || s.at(i) == ']' || s.at(i) == '}') {
			char paired_bracket = s.at(i) - 1 - (s.at(i) != ')');
			pair<char, int> current('\0', i);
			stack<pair<char, int>> temp;
			stack<pair<char, int>> temp_reverse_stack = reverse(visited_brackets);
			while (!temp_reverse_stack.empty() && current.first != paired_bracket) {
				current = temp_reverse_stack.top();
				temp_reverse_stack.pop();
				temp.push(current);
			}
			if (current.first == paired_bracket) {
				temp.pop();//首个元素是配对括号
				while (!temp.empty()) {
					temp_reverse_stack.push(temp.top());
					temp.pop();
				}
				visited_brackets = reverse(temp_reverse_stack);
			}

			else
				return i + 1;
		}

	}
	if (visited_brackets.empty()) {
		return SUCCESS;//
	}
	else {
		pair<char, int> c;
		while (!visited_brackets.empty()) {
			c = visited_brackets.top();
			visited_brackets.pop();
		}
		return c.second + 1;
	}
}
int main() {
	string text;
	while (getline(cin, text)) {
		int x = find_unmatched(text);
		if (x)
			cout << x << std::endl;
		else
			cout << "Success" << std::endl;
	}
	return 0;
}
