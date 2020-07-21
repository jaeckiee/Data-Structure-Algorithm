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
	/*sll_appendnode(List, newnode);*/
	sll_appendnode(&List, newnode);
	if (List == nullptr) {
		cout << "fail" << endl;
	}
	else {
		cout << "correct" << endl;
	}
	return 0;
}