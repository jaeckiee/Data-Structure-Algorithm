//주석
//(1) : Node* head 대신 Node** head를 써야한다. - automatic memory에 생성되므로 주소값을 이용해야 한다.

#include <iostream>

using namespace std;

struct Node {
	int data;
	struct Node* nextnode;
};

Node* sll_createnode(int newdata) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = newdata;
	newnode->nextnode = nullptr;
	return newnode;
}

void sll_destroynode(Node* node) {
	free(node);
}

//(1)
//void sll_appendnode(Node* head, Node* newnode) {
//	if (head == nullptr) {
//		head = newnode;
//	}
//	else {
//		Node* tail = head;
//		while (tail->nextnode != nullptr) {
//			tail = tail->nextnode;
//		}
//		tail->nextnode = newnode;
//	}
//}


void sll_appendnode(Node** head, Node* newnode) {
	if (*head == nullptr) {
		*head = newnode;
	}
	else {
		Node* tail = *head;
		while (tail->nextnode != nullptr) {
			tail = tail->nextnode;
		}
		tail->nextnode = newnode;
	}
}

int main(){
	Node* List = nullptr;
	Node* newnode = nullptr;
	newnode = sll_createnode(10);
	//(1)sll_appendnode(List, newnode);
	sll_appendnode(&List, newnode);
	if (List == nullptr) {
		cout << "fail" << endl;
	}
	else {
		cout << "correct" << endl;
	}
	return 0;
}