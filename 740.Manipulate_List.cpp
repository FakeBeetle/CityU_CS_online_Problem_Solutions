#include <iostream>
using std::cin;
class ListNode {
public:
    ListNode() {
        data = 0;
        next = NULL;
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

class Linked_list_singly {
public:
    friend class Linked_list_doubly;
    Linked_list_singly();
    Linked_list_singly(ListNode* head) {
        this->head = head;
    }
    Linked_list_singly(int A[],int n){
        ListNode* head = new ListNode;
        head->setData(A[0]);
        this->head = head;
        ListNode* current = head;
        for (int i = 1;i!=n;++i){
            ListNode* newnode = new ListNode;
            current->setNext(newnode);
            newnode->setData(A[i]);
            current = newnode;
        }
    };
    ListNode* getHead() {
        return this->head;
    }
    void setHead(ListNode* new_head) {
        this->head = new_head;
    }

    void insert_by_order(ListNode* newnode) {//按顺序插入
        if (this->head == NULL)
            this->head = newnode;
        else if (newnode->getData() < head->getData()) {
            newnode->setNext(head->getNext());
            this->head = newnode;
        }
        else {
            ListNode* p = head;
            while (p->getNext() != NULL && p->getNext()->getData() < newnode->getData()) {
                p = p->getNext();
            }
            newnode->setNext(p->getNext());
            p->setNext(newnode);
        }
    }
    void insert(ListNode* after_which, ListNode* newnode) {
        newnode->setNext(after_which->getNext());
        after_which->setNext(newnode);
    }
    void insert_at(int loc, ListNode* node){
        if (this->head == NULL){
            this->head = node;
        }
        else if (loc == 0){
            node->setNext(this->head);
            this->head = node;
        }
        else{
            ListNode* p_prev = this->head;
            int i = 1;
            while (p_prev->getNext()!=NULL&&i!=loc){
                p_prev = p_prev->getNext();
                ++i;
            }
            node->setNext(p_prev->getNext());
            p_prev->setNext(node);

        }
    }

    ListNode* search(int data) {
        ListNode* current = this->head;
        if (current == NULL)
            return NULL;
        while (current->getNext() != NULL && current->getNext()->getData() != data) {
            current = current->getNext();
        }
        return  current->getNext();
    }
    ListNode* search_at(int loc) {
        ListNode* current = this->head;
        if (current == NULL||loc<=0)
            return NULL;
        int i = 1;
        while(current!=NULL&&i!=loc){
            current = current->getNext();
            ++i;
        }
        return current;
    }
    ListNode* remove(ListNode*  deleted_node) {
        ListNode* current = getHead();
        if (current) {
            while (current->getNext() != NULL && current->getNext() != deleted_node) {
                current = current->getNext();
            }
            if (current->getNext()) {
                current->setNext(deleted_node->getNext());
                return deleted_node;
            }
        }
        return NULL;
    }

    ListNode* remove_at(int loc){
        ListNode* deleted_node = NULL;
        if (loc == 1){
            deleted_node = this->head;
            this->head = this->head->getNext();
        }
        else{
            ListNode* p_prev = this->head;
            int i = 2;
            while(p_prev->getNext()!=NULL && i!=loc){
                p_prev = p_prev->getNext();
                ++i;
            }
            deleted_node = p_prev->getNext();
            p_prev->setNext(p_prev->getNext()->getNext());

        }
        return deleted_node;
    }
    void reverse(int start,int end){
        if (start >= end){
            return;
        }
        else {
            ListNode *before_start;
            ListNode *after_end;
            ListNode *start_node;
            ListNode *end_node;
            if (start == 1) {
                //需要考慮start是否為第一個，因為要求start前面的節點指向end，
                // 但不必考慮end是否為最後一個，因為end後面的節點只會被指
                before_start = NULL;
                start_node = this->head;
            }
            else {
                ListNode *p_prev = this->head;
                int i = 2;
                while (p_prev->getNext() != NULL && i != start) {
                    p_prev = p_prev->getNext();
                    ++i;
                }
                before_start = p_prev;
                start_node = p_prev->getNext();
            }
            ListNode *p = start_node;
            int j = start;
            while (p->getNext() != NULL && j != end) {
                p = p->getNext();
                ++j;
            }
            end_node = p;
            after_end = end_node->getNext();

            if (end - start == 1) {
                before_start->setNext(end_node);
                end_node->setNext(start_node);
                start_node->setNext(after_end);
            }
            else {
                ListNode *prev = start_node;
                ListNode *current = start_node->getNext();
                ListNode *next = start_node->getNext()->getNext();
                if (before_start!=NULL) {
                    before_start->setNext(end_node);
                }
                else{
                    this->head = end_node;
                }
                start_node->setNext(after_end);
                while (next != end_node) {
                    current->setNext(prev);
                    prev = current;
                    current = next;
                    next = next->getNext();
                }
                current->setNext(prev);
                next->setNext(current);

            }
        }
    };
private:
    ListNode* head;

};
int main(){
    int n;//num_of_elements in the initial list
    cin>>n;
    int* A = new int[n];//initial list
    for (int i = 0;i!=n;++i){
        cin>>A[i];
    }
    Linked_list_singly my_list(A,n);
    int k;//num_of_operations_to_take
    cin >> k;
    int operation_type;
    int location;
    int val;
    int start;
    int end;
    int len = n;
    for (int i = 0;i!=k;++i){
        cin >> operation_type;
        if (operation_type == 1){
            cin >> location;
            cin >> val;
            ListNode* to_be_inserted = new ListNode(val,NULL);
            my_list.insert_at(location,to_be_inserted);
            ++len;
        }
        else if (operation_type == 2){
            cin >> location;
            my_list.remove_at(location);
            --len;
        }
        else if (operation_type == 3){
            cin>>start;
            cin>>end;
            my_list.reverse(start,end);
        }
        else if (operation_type == 4){
            cin>>location;
            std::cout<<(my_list.search_at(location)->getData());
        }
        ListNode* p = my_list.getHead();
        std::cout<<"--------------\n";
        for (int j = 0;j!=len;++j){
            std::cout<<p->getData()<<" ";
            p = p->getNext();
        }
     

    }

    return 0;
}

