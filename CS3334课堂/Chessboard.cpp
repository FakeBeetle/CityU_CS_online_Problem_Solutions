enum UP { tail = 0,head };
class ChessBoard {
public:
	ChessBoard();
	~ChessBoard();
	void count_sort();
	void swap(Row* row1, Row* row2);
private:
	Row* rows;
	int* same_row_count;
};


class Row {
public:
	Row() {
		for (int i = 0; i != 9; ++i)
			data[i] = tail;
	};
	Row(int status) {
		this->status = status;
		int a = status;
		for (int i = 0; i != 9; ++i) {
			data[i] = (status % 2) ? head : tail;
			status /= 2;
		}
	}
private:
	UP data[9];
	int status;
};
