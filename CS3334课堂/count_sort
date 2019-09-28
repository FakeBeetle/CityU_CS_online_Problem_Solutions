#include<iostream>
void count_sort(int lower, int upper, int A[], int n) {
	if (lower < 0) {
		for (int i = 0; i < n; ++i)
			A[i] -= lower;
		count_sort(0, upper - lower, A, n);
		for (int i = 0; i < n; ++i)
			A[i] += lower;
	}
	int* B = new int[n] {0};//存放结果
	int* C = new int[upper+1] {0};//计数
	for (int i = 0; i != n; ++i) {
		++C[A[i]];
		std::cout << "C[" << A[i] << "]: " << C[A[i]] << "\n";
	}
	for (int j = 1; j != upper+1; ++j) {
		C[j] += C[j - 1];
	}
	int index = n - 1;
	//std::cout << "upper: " << upper << "\nlower: " << lower << "\n";
	for (int j = upper; j != lower; --j) {
		while (C[j] > C[j - 1]) {
			B[index] = j;
			//std::cout << "B[" << index << "]: " << B[index]<<"\n";
			--C[j];
			--index;
		}
	}
	while (C[lower] > 0) {
		B[index] = lower;
		//std::cout << "B[" << index << "]: " << B[index] << "\n";
		--C[lower];
		--index;
	}
	for (int i = 0; i != n; ++i)
		A[i] = B[i];
	delete[] B;
	B = NULL;
	delete[] C;
	C = NULL;
	
}

int main() {
	int A[10] = { 3,3,6,9,1,4,4,4,8,-1 };
	count_sort(-1, 9, A, 10);
	for (int i = 0; i != 10; ++i)
		std::cout << A[i];
	return 0;
}
