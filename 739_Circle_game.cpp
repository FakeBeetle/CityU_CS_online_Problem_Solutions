#include <iostream>
using std::cin;
class ListNode {
public:
	ListNode() {
		data = 0;
		next = NULL;
	}
	ListNode(int data) {
		this->data = data;
	}
	ListNode(int data, ListNode* next) {
		this->data = data;
		this->next = next;

	};
	ListNode* getNext() {
		return this->next;
	}
	void setNext(ListNode* p) {
		this->next = p;
	}
	int getData() {
		return this->data;
	}
	void setData(int data) {
		this->data = data;
	}

private:
	int data;
	ListNode* next;
};

class Linked_list_circular {
public:
	Linked_list_circular();
	Linked_list_circular(int A[], int length) {
		this->length = length;
		ListNode* initial_head = new ListNode;
		initial_head->setData(A[0]);
		this->head = initial_head;
		ListNode* current = initial_head;
		int i = 1;
		while (i != length) {
			ListNode* newnode = new ListNode;
			current->setNext(newnode);
			newnode->setData(A[i]);
			current = newnode;
			++i;
			current->setNext(this->head);
		}
	}
	ListNode* getHead() {
		return this->head;
	}
	void setHead(ListNode* new_head) {
		this->head = new_head;
	}
	void insert_at(ListNode* newnode,int n) {
		if (this->length == 0) {
			this->head = newnode;
			this->head->setNext(this->head);
		}
		else {
			n = (n-1) % (this->length)+1;
			ListNode* p = this->head;
			for (int i = 1; i != n; ++i)
				p = p->getNext();
			newnode->setNext(p->getNext());
			p->setNext(newnode);
			this->head = newnode;
		}
		++(this->length);
	}

	void insert_by_order(ListNode* newnode) {//°´Ë³Ðò²åÈë
		if (this->head == NULL) {
			this->head = newnode;
			this->head->setNext(this->head);
		}
		else if (newnode->getData() < head->getData()) {
			newnode->setNext(head->getNext());
			this->head = newnode;
		}
		else {
			ListNode* p = head;
			while (p->getNext() != this->head && p->getNext()->getData() < newnode->getData()) {
				p = p->getNext();
			}
			newnode->setNext(p->getNext());
			p->setNext(newnode);
		}
		++(this->length);
	}
	void insert(ListNode* after_which, ListNode* newnode) {
		newnode->setNext(after_which->getNext());
		after_which->setNext(newnode);
		++(this->length);
	}

	ListNode* search(int data) {
		ListNode* current = getHead();
		if (current == NULL)
			return NULL;
		while (current->getNext() != this->head && current->getNext()->getData() != data) {
			current = current->getNext();
		}
		return  current->getNext();
	}
	ListNode* search_at(int n) {
		n = (n - 1) % (this->length) + 1;
		ListNode* p = this->head;
		for (int i = 1; i != n; ++i)
			p = p->getNext();
		this->head = p;
		return p;
	}
	void remove_at(int n) {
		if(length != 0) {
			n = (n - 2) % (this->length) + 2;
			ListNode* p_prev = this->head;
			for (int i = 2; i != n; ++i)
				p_prev = p_prev->getNext();
			this->head = (p_prev->getNext()->getNext());
			p_prev->setNext(p_prev->getNext()->getNext());
		}
		--(this->length);
	}
	ListNode* remove(ListNode*  deleted_node) {
		ListNode* current = getHead();
		if (current) {
			while (current->getNext() != this->head && current->getNext() != deleted_node) {
				current = current->getNext();
			}
			if (current->getNext()!=this->head) {
				current->setNext(deleted_node->getNext());
				return deleted_node;
			}
		}
		return NULL;
		--(this->length);
	}
private:
	ListNode* head;
	int length;
};

int main() {
	int no_of_students;
	int no_of_operations;
	cin >> no_of_students;
	int* A = new int[no_of_students];
	for (int i = 0; i != no_of_students; ++i)
		cin >> A[i];
	cin >> no_of_operations;
	Linked_list_circular students(A, no_of_students);
	int operation_type;
	int location;
	int tag;
	for (int i = 0; i != no_of_operations; ++i) {
		cin >> operation_type;
		if (operation_type == 1) {
			cin >> location;
			cin >> tag;
			ListNode* newnode = new ListNode;
			newnode->setData(tag);
			students.insert_at(newnode,location);
		}
		if (operation_type == 2) {
			cin >> location;
			students.remove_at(location);
		}
		if (operation_type == 3) {
			cin >> location;
			std::cout << students.search_at(location)->getData();
		}
	}
	return 0;
}