#include <iostream>
#include <queue>
using namespace std;//为了考试,暂时这样写
class Customer {
public:
	Customer(int finish_time) {
		this->finish_time = finish_time;//这是唯一在入队后还会被保留的信息,A,O,L蕴含的信息都在处理下一个顾客前处理完毕，体现为是否take这个任务和什么时候完成
	}
	int finish_time;
};

int main() {
	int N;
	while (cin >> N) {
		queue <Customer> waiting_queue;
		int time;
		for (int i = 0; i != N;++i) {
			int A, O, L;
			cin >> A;
			cin >> O;
			cin >> L;
			if (time < A) {
				time = A;//跳过空档期0
			}
			while (!waiting_queue.empty()&& waiting_queue.front().finish_time <= A) {//小于等于A的是在该顾客到达前已完成的，大于的是未完成的，这在time时间依然可以判断是因为{┏<=A}
				waiting_queue.pop();//已完成的任务出队（在当前任务arrive之前)，前一个任务的结束时间，是后一个任务的开始时间，因此结束时间是递增的
			 }
			if (i == N - 1) {//如果这是最后一个，那就返回
				cout << ((L < waiting_queue.size()) ? (-1) : time) << "\n";
			}
			else if (L >= waiting_queue.size()) {//take 这个顾客，要是括号内条件不满足就什么也不做（他会直接离开，take care下一个输入）
				time += O;//否则把这个任务做了
				waiting_queue.push(Customer(time));
				//只有被take的任务才入队，并不直接出队，对每一个arrive的任务，判断前面进行的任务完成时间在此到达时间之前（出队）还是之后（留在队列中）
			}
		}
	}
	return 0;
}
