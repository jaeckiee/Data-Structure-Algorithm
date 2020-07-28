#include <iostream>

using namespace std;

class Node {
public:
	Node(){
		data = 0;
	}
	Node(int num) {
		data = num;
	}
	int returndata() {
		return data;
	}
private:
	int data;
};

class Stack {
public:
	Stack() {
		capacity = 10;
		nodes = new Node[10];
		top = 0;
	}
	Stack(int capacity) {
		this->capacity = capacity;
		nodes = new Node[capacity];
		top = 0;
	}
	~Stack() {
		delete nodes;
		nodes = nullptr;
	}
	void push(int num) {
		nodes[top++] = Node(num);
	}
	int pop() {
		int result = nodes[--top].returndata();
		return result;
	}
private:
	int capacity;
	int top;
	Node* nodes;
};
int main(void) {
	Stack s = Stack(20);
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(6);
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	return 0;
}