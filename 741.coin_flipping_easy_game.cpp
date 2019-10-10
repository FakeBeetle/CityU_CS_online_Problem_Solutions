#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
void flip(int chess[][10],int rows,int cols,int flipped_index, bool row_flipping) {
	if (row_flipping) {
		for (int j = 0; j != cols; ++j)
			chess[flipped_index][j] = 1-chess[flipped_index][j];
	}
	else {
		for (int i = 0; i != rows; ++i)
			chess[i][flipped_index] = 1 - chess[i][flipped_index];
	}
}
void multiflip(int chess[][10], int rows, int cols, int flipped_code, bool row_flipping) {
	int index = 0;
	while (flipped_code != 0) {
		if (flipped_code % 2)
			flip(chess, rows, cols, index, row_flipping);
		flipped_code = flipped_code >> 1;
		++index;
	}
}

int main() {
	while(!cin.eof()) {
		int a[1000][10] = {0};
		int n;//rows
		int m;//cols
		cin >> n;
		cin >> m;
		int line;
		for (int i = 0; i != n; ++i) {
			cin >> line;
			for (int j = 0; j != m; ++j) {
				a[i][j] = line % 10;
				line = line / 10;
			}
		}
		int initial_state[1000][10];
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != n; ++j)
				initial_state[i][j] = a[i][j];
		}
		int max = 0;
		for (int k = 0; k != pow(2, m); ++k) {
			//reset
			for (int i = 0; i != n; ++i) {
				for (int j = 0; j != n; ++j)
					a[i][j] = initial_state[i][j];
			}
			int heads = 0;
			multiflip(a, n, m, k, 0);
			//
			for (int i = 0; i != n; ++i) {
				int cnt = 0;
				for (int j = 0; j != m; ++j)
					cnt += a[i][j];
				if (cnt < m / 2.0) {
					flip(a, n, m, i, 1);
					cnt = m - cnt;
				}
				heads += cnt;
			}
			if (heads > max)
				max = heads;
		}
		cout << max <<"\n";
	}
	return 0;
}
