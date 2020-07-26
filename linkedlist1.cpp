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

Node* sll_getnodeat(Node* head, int location) {
	Node* current = head;
	while (current != nullptr && (--location) > 0) {
		current = current->nextnode;
	}
	return current;
}

void sll_removenode(Node** head, Node* remove) {
	if (*head == remove) {
		*head = remove->nextnode;
	}
	else {
		Node* current = *head;
		while (current != nullptr && current->nextnode != remove) {
			current = current->nextnode;
		}
		current->nextnode = remove->nextnode;
	}
}
int main(){
	Node* List = nullptr;
	Node* newnode = nullptr;
	Node* getnode = nullptr;
	newnode = sll_createnode(10);
	//(1)sll_appendnode(List, newnode);
	sll_appendnode(&List, newnode);
	if (List == nullptr) {
		cout << "fail" << endl;
	}
	else {
		cout << "correct" << endl;
	}
	getnode = sll_getnodeat(List, 1);
	cout << getnode->data << endl;
	return 0;
}