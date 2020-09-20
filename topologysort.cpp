#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Edge;

class Vertex {
public:
	int data;
	bool visited;
	int degree;
	Edge* edges;
};

class Edge {
public:
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
		ver->degree = 0;
		vertices.push_back(ver);
	}
	void addEdge(int fromdata, int targetdata) {
		Edge* tmp;
		Edge* ed;
		if (!isEmpty()) {
			int vertexnumber;
			int fromindex = -1;
			int targetindex = -1;
			ed = new Edge();
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
			if ((fromindex != -1) && (targetindex != -1)) {
				tmp = nullptr;
				ed->target = vertices[targetindex];
				ed->target->degree++;
				if (vertices[fromindex]->edges == nullptr) {
					vertices[fromindex]->edges = ed;
				}
				else {
					tmp = vertices[fromindex]->edges;
					ed->next = tmp;
					vertices[fromindex]->edges = ed;
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
	void dfs(Vertex* ver) {
		Edge* ed;
		ver->visited = true;
		ed = ver->edges;
		while (ed != nullptr) {
			if (ed->target->visited == false) {
				dfs(ed->target);
			}
			ed = ed->next;
		}
		sck.push(ver->data);
	}
	void topologysortstart() {
		for (int i = 0; i < vertexnum(); i++) {
			if (vertices[i]->degree == 0) {
				topologysort(vertices[i]);
			}
		}
	}
	void topologysort(Vertex* ver) {
		dfs(ver);
	}
	void popstack() {
		while (!sck.empty()) {
			cout << sck.top() << ' ';
			sck.pop();
		}
	}
private:
	vector<Vertex*> vertices;
	stack<int> sck;
};


int main() {
	int vertexnumber;
	int edgenumber;
	int fromnumber;
	int targetnumber;
	Graph* g = new Graph();
	cin >> vertexnumber >> edgenumber;
	for (int i = 0; i < vertexnumber; i++) {
		g->addVertex(i + 1);
	}
	for (int i = 0; i < edgenumber; i++) {
		cin >> fromnumber >> targetnumber;
		g->addEdge(fromnumber, targetnumber);
	}
	g->topologysortstart();
	g->popstack();
	return 0;
}