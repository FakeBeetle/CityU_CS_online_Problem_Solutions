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

void reverse(list<int> &A,int lower,int upper) {
	list<int>::iterator iter1 = A.begin();
	list<int>::iterator iter2 = A.begin();
	for (int i = 0; i != lower; ++i) {
		++iter1;
	}
	for (int i = 0; i != upper + 1; ++i) {
		++iter2;
	}
	list<int> temp(iter1, iter2);
	list<int>::iterator pos = A.erase(iter1,iter2);
	A.insert(pos,temp.rbegin(),temp.rend());
}
int main() {
	list<int> A;
  /*
    int element;
    for (int i = 0; i != 10; ++i) {
      cin >> element;
      A.push_back(element);
    }
    reverse(A,0,8);
    for (list<int>::iterator iter = A.begin(); iter != A.end(); ++iter) {
      cout << *iter;
    }
  */


	return 0;
}
