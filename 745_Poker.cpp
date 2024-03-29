#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
using namespace std;
int max(vector<int> A) {
	int maximum = *A.begin();
	for (vector<int>::iterator iter = A.begin(); iter != A.end(); ++iter) {
		if (*iter > maximum) {
			maximum = *iter;
		}
	}
	return maximum;
}
int main() {
	int T;
	cin >> T;

	for (int i = 0; i != T; ++i) {
		int n;
		cin >> n;
		int card;
		vector<int> pile;
		for (int j = 0; j != n; ++j) {
			cin >> card;
			pile.push_back(card);
		}
		int m;
		cin >> m;
		char operation;
		for (int j = 0; j != m; ++j) {
			cin >> operation;
			if (operation == 'm') {
				cout << max(pile) << "\n";
			}
			else if (operation == 'r') {
				pile.pop_back();
			}
			else if (operation == 'a') {
				int value;
				cin >> value;
				pile.push_back(value);
			}
		}
	}
	return 0;
}
