#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using std::vector;
using std::cin;
using std::string;
using std::cout;
bool same_color(int length, int irow,int icol, const vector<vector<int>> &A) {
	int first_color = A[irow][icol];
	for (int i = irow; i != irow + length; ++i) {
		for (int j = icol; j != icol + length; ++j) {
			if (A[i][j] != first_color)
				return false;
		}
	}
	return true;

}
int count_nodes(int length, int irow, int icol, const vector<vector<int>> &A) {
	if (same_color(length, irow, icol,A))
		return 1;
	else
		return (1
			+ count_nodes(length / 2, irow, icol,A)
			+ count_nodes(length / 2, irow + length / 2, icol,A)
			+ count_nodes(length / 2, irow, icol + length / 2,A)
			+ count_nodes(length / 2, irow + length / 2, icol + length / 2,A)
		);
}

int main() {
	int k;
	while (cin >> k) {
		vector<vector<int>> image(1024);
		string line;
		for (int i = 0; i != pow(2, k); ++i) {
			cin >> line;
			for (int j = 0; j != pow(2, k); ++j) {
				image[i].push_back(int(line.at(j) - '0'));
			}
		}
		cout << count_nodes(pow(2, k), 0, 0, image)<<"\n";
	}
	return 0;
}
