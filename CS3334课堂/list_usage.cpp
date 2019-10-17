#include<iostream>
using std::cin;
using std::cout;
#include<string>
using std::string;
using std::getline;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<map>
using std::map;
#include<cmath>
#include<stack>
using std::stack;
#include<list>
using std::list;
//增
void insert_at(list<int> &A, int pos, int data, bool start_counting_from_1 = 0) {
	list<int>::iterator iter = A.begin();
	for (int i = 0; i != pos - start_counting_from_1; ++i) {
		++iter;
	}
	A.insert(iter, data);
}// for multiple insertion,create anoter list first,and use the built-in function//
//查
list<int>::iterator find_iter_by_data(list<int> &A, int data) {
	list<int>::iterator iter = A.begin();
	while (iter!=A.end()&&*iter != data) {
		++iter;
	}
	return iter;
}
int find_pos_by_data(list<int>&A, int data) {
	int order = 0;
	list<int>::iterator iter = A.begin();
	while (iter != A.end() && *iter != data) {
		++iter;
		++order;
	}
	if (iter != A.end())
		return order;
	else
		return -1;
}
list<int>::iterator find_iter_by_pos(list<int>&A, int pos, bool start_counting_from_1 = 0) {
	list<int>::iterator iter = A.begin();
	for (int i = start_counting_from_1; i != pos; ++i) {
		++iter;
	}
	return iter;

}
int find_data_by_pos(list<int>&A, int pos, bool start_counting_from_1 = 0) {
	return *find_iter_by_pos(A, pos, start_counting_from_1);
}
//逆序
void reverse_by_iter(list<int> &A, list<int>::iterator begin,list<int>::iterator end) {
	list<int> temp(begin, end);
	list<int>::iterator pos = A.erase(begin, end);
	A.insert(pos, temp.rbegin(), temp.rend());
}
void reverse_by_pos(list<int> &A, int lower, int upper, bool start_counting_from_1 = 0) {
	list<int>::iterator iter1 = A.begin();
	list<int>::iterator iter2 = A.begin();
	for (int i = 0; i != lower - start_counting_from_1; ++i) {
		++iter1;
	}
	for (int i = 0; i != upper + 1 - start_counting_from_1; ++i) {
		++iter2;
	}
	reverse_by_iter(A, iter1, iter2);

}
//删
list<int>::iterator delete_by_pos(list<int> &A,int pos, bool start_counting_from_1 = 0) {//return the following iterator
	list<int>::iterator iter = A.begin();
	for (int i = 0; i != pos - start_counting_from_1; ++i) {
		++iter;
	}
	return A.erase(iter);
}
list<int>::iterator delete_by_data(list<int>&A, int data) { //return the following iterator
	list<int>::iterator iter = find_iter(A,data);
	return A.erase(iter);
}
//打印
void show(list<int> &A) {
	for (list<int>::iterator iter = A.begin(); iter != A.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << "\n";
}


int main() {
	list<int> A;
	int element;
	for (int i = 0; i != 10; ++i) {
		cin >> element;
		A.push_back(element);
	}
	//insert_at(A,4, -100,0);

	/*

		show(A);
		reverse_by_iter(A, A.begin(), A.end());
		show(A);
	*/
	cout << A.;

	


	return 0;
}
