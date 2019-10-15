#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using std::vector;
using std::cin;
using std::string;
using std::cout;
bool same_color(int start_row, int start_col, int end_row, int end_col, vector<vector<int>> image);
int count_nodes(int start_row, int start_col, int end_row, int end_col, const vector<vector<int>> &a) {
	if (same_color(start_row,start_col,end_row,end_col,a))
		return 1;
	else
		return count_nodes(start_row,start_col,(start_row+end_row)/2,(start_col+end_col)/2,a)
		+count_nodes(start_row, (start_col + end_col) / 2+1, (start_row + end_row) / 2,end_col , a) 
		+ count_nodes((start_row + end_row) / 2+1, start_col,end_row, (start_col + end_col) / 2,a) 
		+ count_nodes((start_row + end_row) / 2 + 1, (start_col + end_col) / 2 + 1,end_row,end_col,a);
}
bool same_color(int start_row, int start_col, int end_row, int end_col,vector<vector<int>> image){ 
	int first_color = image[start_row][start_col];
	for (vector<vector<int>>::iterator outer_iter = image.begin() + start_row; outer_iter != image.end() + end_row; ++outer_iter) {
		for (vector<int>::iterator inter_iter = outer_iter->begin() + start_col; inter_iter != outer_iter->begin() + end_col; ++inter_iter) {
			if (*inter_iter != first_color)
				return false;
		}
	}
	return true;
}
int main() {
	int k;
	vector<vector<int>> image(1024);
	cin >> k;
	string line;
	for (int i = 0; i != pow(2, k); ++i) {
		cin >> line;
		for (int j = 0; j != pow(2, k); ++j) {
			image[i].push_back(int(line.at(j) - '0'));
		}
	}
	cout << count_nodes(0, 0, pow(2, k) - 1, pow(2, k) - 1, image);
	return 0;
}
