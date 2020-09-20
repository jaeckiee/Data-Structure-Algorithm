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
	void addEdge(int fromdata, int targetdata) {
		Edge* tmp;
		Edge* ed;
		Edge* ed2;
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
					cout << tmp->target->data  << ' ';
					tmp = tmp->next;
				}
				cout << endl;
			}
		}
		else {
			cout << "Graph doesn't exist" << endl;
		}
	}
	void visitedInitialization() {
		if (!isEmpty()) {
			int vertexnumber = vertexnum();
			for (int i = 0; i < vertexnumber; i++) {
				vertices[i]->visited = false;
			}
		}
	}
	void dfsStart(int data) {
		if (!isEmpty()) {
			int vertexnumber = vertexnum();
			for (int i = 0; i < vertexnumber; i++) {
				if (vertices[i]->data == data) {
					dfs(vertices[i]);
					break;
				}
			}
			cout << endl;
			visitedInitialization();
		}
	}
	void dfs(Vertex* ver) {
		Edge* ed;
		ver->visited = true;
		cout << ver->data << ' ';
		ed = ver->edges;
		while (ed != nullptr) {
			if (ed->target->visited == false) {
				dfs(ed->target);
			}
			ed = ed->next;
		}
	}
	void bfsStart(int data) {
		if (!isEmpty()) {
			vector<Vertex*>* queue;
			queue = new vector<Vertex*>;
			int vertexnumber = vertexnum();
			for (int i = 0; i < vertexnumber; i++) {
				if (vertices[i]->data == data) {
					vertices[i]->visited = true;
					queue->insert(queue->begin(), vertices[i]);				
					bfs(queue);
					break;
				}
			}
			visitedInitialization();
			cout << endl;
		}
	}
	void bfs(vector<Vertex*>* queue) {
		Vertex* ver;
		Edge* ed;
		if (!queue->empty()) {
			ver = queue->back();
			queue->pop_back();
			cout << ver->data << ' ';
			ed = ver->edges;
			while (ed != nullptr) {
				if (ed->target->visited == false) {
					queue->insert(queue->begin(), ed->target);
					ed->target->visited = true;
				}
				ed = ed->next;
			}
			bfs(queue);
		}
	}
private:
	vector<Vertex*> vertices;
};


int main() {
	
	return 0;
}