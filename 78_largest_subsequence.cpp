#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::string;
string largest_subsequence(string s) {
	char max = s.at(s.length() - 1);
	string sub = "";
	for (int j = s.length(); j != -1; --j) {
		if (s[j] >= max) {
			sub.insert(sub.begin(), s[j]);
			max = s[j];
		}
	}
	return sub;
}

int main() {
	int n;
	string s;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		cin >> s;
		cout << largest_subsequence(s)<<"\n";
	}
	return 0;
}