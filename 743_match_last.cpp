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
/*
bool char_in_str(string s,char a) {
	for (int i = 0; i != s.length(); i++)
		if (a == s[i])
			return true;
	return false;
}
bool flag(string s) {
	return char_in_str(s, '(') || char_in_str(s, ')') || char_in_str(s, '[') || char_in_str(s, ']') || char_in_str(s, '{') || char_in_str(s, '}');
}
*/
int find_unmatched(string s) {
	
	stack<pair<char, int>> visited_brackets;
	for (int i = 0; i != s.length(); ++i) {
		if (s.at(i) == '(' || s.at(i) == '[' || s.at(i) == '{') {
			visited_brackets.push(pair<char,int>(s.at(i),i));
		}
		else if (s.at(i) == ')' || s.at(i) == ']' || s.at(i) == '}') {
			char paired_bracket = s.at(i) - 1 - (s.at(i) != ')');
			pair<char,int> current('\0',i);
			stack<pair<char,int>> temp;
			while (!visited_brackets.empty() && current.first != paired_bracket) {
				current = visited_brackets.top();
				visited_brackets.pop();
				temp.push(current);
			}
			if (current.first == paired_bracket) {
				temp.pop();//首个元素是配对括号
				while (!temp.empty()) {
					visited_brackets.push(temp.top());
					temp.pop();
				}
			}
			else
				return i+1;
		}

	}
	if (visited_brackets.empty()) {
		return SUCCESS;//
	}
	else {
		pair<char,int> c;
		while (!visited_brackets.empty()) {
			c = visited_brackets.top();
			visited_brackets.pop();
		}
		return c.second+1;
	}
}
int main() {
	string text;
	while (getline(cin, text)) {
		int x = find_unmatched(text);
		if (x)
			cout << x << "\n";
		else {
			//if (flag(text))
				cout << "Success\n";
		}
	}
	return 0;
}
