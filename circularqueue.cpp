#include <iostream>

using namespace std;

class Node {
public:
	int data;
};

class CircularQueue {
public:
	CircularQueue() {
		capacity = 10;
		front = 0;
		rear = 0;
		nodes = new Node[capacity + 1];
	}
	CircularQueue(int capacity) {
		this->capacity = capacity;
		front = 0;
		rear = 0;
		nodes = new Node[capacity + 1];
	}
	~CircularQueue() {
		delete[]nodes;
		nodes = nullptr;
	}
	void enqueue(int num) {
		if (!isFull()) {
			nodes[rear].data = num;
			rear = (rear + 1) % (capacity + 1);
		}
		else {
			cout << "FULL" << endl;
		}
	}
	int dequeue() {
		int result;
		if (!isEmpty()) {
			result = nodes[front].data;
			front = (front + 1) % (capacity + 1);
		}
		else {
			result = -1;
		}
		return result;
	}
	bool isEmpty() {
		if (front == rear) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFull() {
		if (front == ((rear + 1) % (capacity + 1))) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int capacity;
	int front;
	int rear;
	Node* nodes;
};
int main() {
	CircularQueue cirq = CircularQueue(5);
	cirq.enqueue(1);
	cirq.enqueue(2);
	cirq.enqueue(3);
	cirq.enqueue(4);
	cirq.enqueue(5);
	cirq.enqueue(6);
	cout << cirq.dequeue() << endl;
	cout << cirq.dequeue() << endl;

	return 0;
}