#include <iostream>
#include <vector>
using namespace std;

class Edge;

class Vertex {
public:
	int data;
	bool visited;
	Edge* edges;
};

class Edge {
public:
	int weight;
	Vertex* target;
	Edge* next;
};

class Graph {
public:
	void addVertex(int data) {
		Vertex* ver = new Vertex();
		ver->data = data;
		ver->visited = false;
		ver->edges = nullptr;
		vertices.push_back(ver);
	}
	void addEdge(int weight, int fromdata, int targetdata) {
		Edge* tmp;
		Edge* ed;
		if (!isEmpty()) {
			int vertexnumber;
			int fromindex = -1;
			int targetindex = -1;
			ed = new Edge();
			ed->weight = weight;
			ed->next = nullptr;
			vertexnumber = vertexnum();
			for (int i = 0; i < vertexnumber; i++) {
				if (vertices[i]->data == fromdata) {
					fromindex = i;
				}
				if (vertices[i]->data == targetdata) {
					targetindex = i;
				}
			}
			if ((fromindex != - 1) && (targetindex != -1)) {
				tmp = nullptr;
				ed->target = vertices[targetindex];
				if (vertices[fromindex]->edges == nullptr) {
					vertices[fromindex]->edges = ed;
				}
				else {
					tmp = vertices[fromindex]->edges;
					while (tmp->next != nullptr) {
						tmp = tmp->next;
					}
					tmp->next = ed;
				}
			}
		}
	}
	int vertexnum() {
		return vertices.size();
	}
	bool isEmpty() {
		return vertices.empty();
	}
	void printGraph() {
		if (!isEmpty()) {
			int vertexnumber = vertexnum();
			Edge* tmp;
			for (int i = 0; i < vertexnumber; i++) {
				tmp = vertices[i]->edges;
				cout << '[' << vertices[i]->data << ']' << ' ';
				while (tmp != nullptr) {
					cout << tmp->target->data << '(' << tmp->weight << ')' << ' ';
					tmp = tmp->next;
				}
				cout << endl;
			}
		}
		else {
			cout << "Graph doesn't exist" << endl;
		}
	}
private:
	vector<Vertex*> vertices;
};

int main() {
	Graph* g = new Graph();
	g->addVertex(1);
	g->addVertex(2);
	g->addVertex(3);
	g->addVertex(4);
	g->addVertex(5);
	g->addVertex(6);
	g->addVertex(7);
	g->addEdge(3, 1, 2);
	g->addEdge(5, 1, 3);
	g->addEdge(10, 2, 4);
	g->addEdge(7, 2, 5);
	g->addEdge(4, 3, 4);
	g->addEdge(3, 3, 6);
	g->addEdge(20, 4, 5);
	g->addEdge(13, 4, 7);
	g->addEdge(6, 5, 7);
	g->addEdge(8, 6, 7);
	g->printGraph();
	return 0;
}