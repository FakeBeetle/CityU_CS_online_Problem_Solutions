#include<iostream>
#include<stack>
#include<vector>
#include<utility>
#include<map>
using std::cin;
using std::cout;
using std::stack;
using std::vector;
using std::pair;
using std::map;
typedef int Order;
void move(stack<int> s1, stack<int> s2) {
	if (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}
}
int order_of(int element, stack <pair<int, Order>> A) {
	while (!A.empty() && A.top().first != element) {
		A.pop();
	}
	if (!A.empty())
		return A.top().second;
	else
		return -1;
}
bool Aye(stack<pair<int,Order>>A, vector<pair<int,Order>>B,int n) {
	stack <pair<int, Order>> S;
	//stack <pair<int, Order>> DB;
	int finished_num = 0;
	vector<pair<int, Order>>::iterator bottom = B.begin();
	while (finished_num!=n) {
		if (bottom!=B.begin()&&bottom->second > (bottom-1)->second) {//bottom+1已经进入栈S
			if (bottom->first != S.top().first)
				return false;
			else {
				//DB.push(S.top())
				finished_num++;
				S.pop();
			}
		}
		else {
			while (A.top().first != bottom->first) {
				S.push(A.top());
				A.pop();
			}
			//S.push(A.top())
			//DB.push(S.top());
			++finished_num;
			//S.pop()
			A.pop();
		}
		bottom = bottom + 1;
	}
	return true;
}
int main() {
	int T;
	cin >> T;
	for (int i = 0; i != T; ++i) {
		/*
			stack<int> A;
			stack<int> B;
			stack<int> S;
		*/
		int n;// number of elements in A
		cin >> n;
		stack<pair<int,Order>> A;
		int element = 0;
		for (int j = 0; j != n; ++j) {
			cin >> element;
			A.push(pair<int,Order>(element,j+1));
		}
		int m;//number of permutations
		cin >> m;
		for (int j = 0; j != m; ++j) {
			vector<pair<int,Order>> B;//元素进入B的顺序，是元素弹出S的顺序
			for (int k = 0; k != n; ++k) {
				cin >> element;
				B.push_back(pair<int, Order>(element, order_of(element,A)));
			}
			if ((Aye(A, B,n)))
				cout << "Aye\n";
			else
				cout << "Impossible\n";
		}

	}
	return 0;
}
