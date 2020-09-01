#include <iostream>

using namespace std;

#define BLACK true
#define RED false

class RBTNode {
public:
	RBTNode* parent;
	RBTNode* left;
	RBTNode* right;
	bool color;
	int data;
};

class RBTree {
public:
	RBTree() {
		NIL = new RBTNode;
		NIL->parent = nullptr;
		NIL->left = nullptr;
		NIL->right = nullptr;
		NIL->color = BLACK;
		root = NIL;
	}
	void rbtRotateRight(RBTNode** root, RBTNode* parent) {
		RBTNode* leftchild = parent->left;
		parent->left = leftchild->right;
		if (leftchild->right != NIL) {
			leftchild->right->parent = parent;
		}
		leftchild->parent = parent->parent;
		if (parent->parent == nullptr) {
			(*root) = leftchild;
		}
		else {
			if (parent == (parent->parent->left)) {
				parent->parent->left = leftchild;
			}
			else {
				parent->parent->right = leftchild;
			}
		}
		leftchild->right = parent;
		parent->parent = leftchild;
	}
	void rbtRotateLeft(RBTNode** root, RBTNode* parent) {
		RBTNode* rightchild = parent->right;
		parent->right = rightchild->left;
		if (rightchild->left != NIL) {
			rightchild->left->parent = parent;
		}
		rightchild->parent = parent->parent;
		if (parent->parent == nullptr) {
			(*root) = rightchild;
		}
		else {
			if (parent == parent->parent->left) {
				parent->parent->left = rightchild;
			}
			else {
				parent->parent->right = rightchild;
			}
		}
		rightchild->left = parent;
		parent->parent = rightchild;
	}
	bool isEmpty() {
		if (root == NIL) {
			return true;
		}
		else {
			return false;
		}
	}
	RBTNode* rbtSearchData(int target) {
		return rbtSearchNode(root, target);
	}
	RBTNode* rbtSearchNode(RBTNode* node, int target) {
		if (node == NIL) {
			return NIL;
		}
		else {
			if ((node->data) == target) {
				return node;
			}
			else if ((node->data) > target) {
				rbtSearchNode(node->left, target);
			}
			else {
				rbtSearchNode(node->right, target);
			}
		}
	}
	void rbtInsertData(int data) {
		rbtInsertNode(data);
	}
	void rbtInsertNode(int data) {
		if (isEmpty()) {
			RBTNode* newnode = new RBTNode;
			newnode->data = data;
			newnode->left = NIL;
			newnode->right = NIL;
			newnode->parent = nullptr;
			newnode->color = BLACK;
			root = newnode;
		}
		else {
			insertNode(root, data);
		}
	}
	void insertNode(RBTNode* node, int data) {
		if (node->data == data) {
			return;
		}
		else if (node->data > data) {
			if (node->left == NIL) {
				RBTNode* newnode = new RBTNode;
				newnode->data = data;
				newnode->left = NIL;
				newnode->right = NIL;
				newnode->parent = node;
				newnode->color = RED;
				node->left = newnode;
				reBuildAfterInsert(newnode);
			}
			else {
				insertNode(node->left, data);
			}
		}
		else {
			if (node->right == NIL) {
				RBTNode* newnode = new RBTNode;
				newnode->data = data;
				newnode->left = NIL;
				newnode->right = NIL;
				newnode->parent = node;
				newnode->color = RED;
				node->right = newnode;
				reBuildAfterInsert(newnode);
			}
			else {
				insertNode(node->right, data);
			}
		}
	}
	void reBuildAfterInsert(RBTNode* node) {
		RBTNode* uncle;
		while ((node != nullptr) && (node != root) && (node->parent != root) && (node->parent->color == RED)) {
			if ((node->parent->parent->left) == (node->parent)) {
				uncle = node->parent->parent->right;
				if (uncle->color == RED) {
					uncle->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else{
					if (node == node->parent->right) {
						rbtRotateLeft(&root, node->parent);
						node = node->left;
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					rbtRotateRight(&root, node->parent->parent);
				}
			}
			else {
				uncle = node->parent->parent->left;
				if (uncle->color == RED) {
					uncle->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						rbtRotateRight(&root, node->parent);
						node = node->right;
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					rbtRotateLeft(&root, node->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	RBTNode* rbtDeleteNode(int target) {
		if (isEmpty()) {
			return NIL;
		}
		else {
			return deleteNode(&root, target);
		}
	}
	RBTNode* deleteNode(RBTNode** node, int target) {
		if ((*node) == NIL) {
			return NIL;
		}
		else {
			RBTNode* remove;
			if ((*node)->data > target) {
				remove = deleteNode(&((*node)->left), target);
			}
			else if ((*node)->data < target) {
				remove = deleteNode(&((*node)->right), target);
			}
			else {
				RBTNode* nodeparent;
				nodeparent = (*node)->parent;
				remove = (*node);
				if ((remove->left == NIL) && (remove->right == NIL)) {
					if (nodeparent != nullptr) {
						if (nodeparent->left == (*node)) {
							nodeparent->left = NIL;
							if (remove->color == BLACK) {
								reBuildAfterDelete(nodeparent, nodeparent->left);
							}
						}
						else {
							nodeparent->right = NIL;
							if (remove->color == BLACK) {
								reBuildAfterDelete(nodeparent, nodeparent->right);
							}
						}
					}
					(*node) = NIL;
				}
				else {
					RBTNode* tmp;
					RBTNode* tmpparent;
					bool tmpcolor;
					if (remove->right != NIL) {
						tmp = remove->right;
						while (tmp->left != NIL) {
							tmp = tmp->left;
						}
						tmpcolor = tmp->color;
						tmpparent = tmp->parent;
						tmp->color = remove->color;
						if (tmpparent == remove) {
							if (nodeparent != nullptr) {
								if (nodeparent->left == remove) {
									nodeparent->left = tmp;
								}
								else {
									nodeparent->right = tmp;
								}
							}
							tmp->parent = nodeparent;
							tmp->left = remove->left;
							remove->left->parent = tmp;
							(*node) = tmp;
							if (tmpcolor == BLACK) {
								if (tmp->right != NIL) {
									tmp->right->color = BLACK;
								}
							}
							return remove;
						}
						tmp->left = remove->left;
						if (remove->left != NIL) {
							remove->left->parent = tmp;
						}
						tmp->parent = nodeparent;
						if (nodeparent != nullptr) {
							if (nodeparent->left == remove) {
								nodeparent->left = tmp;
							}
							else {
								nodeparent->right = tmp;
							}
						}
						tmpparent->left = tmp->right;
						if (tmp->right != NIL) {
							tmp->right->parent = tmpparent;
						}
						tmp->right = remove->right;
						remove->right->parent = tmp;
						(*node) = tmp;
						if (tmpcolor == BLACK) {
							if (tmpparent->left == NIL) {
								reBuildAfterDelete(tmpparent, tmpparent->left);
							}
							else {
								tmpparent->left->color = BLACK;
							}
						}
					}
					else { 
						tmp = remove->left;
						while (tmp->right != NIL) {
							tmp = tmp->right;
						}
						tmpcolor = tmp->color;
						tmpparent = tmp->parent;
						tmp->color = remove->color;
						if (tmpparent == remove) {
							if (nodeparent != nullptr) {
								if (nodeparent->left == remove) {
									nodeparent->left = tmp;
								}
								else {
									nodeparent->right = tmp;
								}
							}
							tmp->parent = nodeparent;
							tmp->right = remove->right;
							(*node) = tmp;
							if (tmpcolor == BLACK) {
								if (tmp->left != NIL) {
									tmp->right->color = BLACK;
								}
							}
							return remove;
						}
						tmp->right = remove->right;
						tmp->parent = nodeparent;
						if (nodeparent != nullptr) {
							if (nodeparent->left == remove) {
								nodeparent->left = tmp;
							}
							else {
								nodeparent->right = tmp;
							}
						}
						tmpparent->right = tmp->left;
						if (tmp->left != NIL) {
							tmp->left->parent = tmpparent;
						}
						tmp->left = remove->left;
						remove->left->parent = tmp;
						(*node) = tmp;
						if (tmpcolor == BLACK) {
							if (tmpparent->right == NIL) {
								reBuildAfterDelete(tmpparent, tmpparent->right);
							}
							else {
								tmpparent->right->color = BLACK;
							}
						}				
					}
				}
			}
			return remove;
		}
	}
	void reBuildAfterDelete(RBTNode* parent, RBTNode* node) {
		if (parent == nullptr) {
			return;
		}
		if (parent->left == node) {
			if (parent->right->color == RED) {
				parent->color = RED;
				parent->right->color = BLACK;
				rbtRotateLeft(&root, parent);
			}
			if ((parent->right->left->color == BLACK) && (parent->right->right->color == BLACK)) {
				parent->right->color = RED;
				if (parent->color == BLACK) {
					reBuildAfterDelete(parent->parent, parent);
				}
				else {
					parent->color = BLACK;
				}
			}
			else {
				if (parent->right->left->color == RED && parent->right->right->color == BLACK) {
					parent->right->color = RED;
					parent->right->left->color = BLACK;
					rbtRotateRight(&root, parent->right);
				}
				parent->right->color = parent->color;
				parent->color = BLACK;
				parent->right->right->color = BLACK;
				rbtRotateLeft(&root, parent);
			}
		}
		else {
			if (parent->left->color == RED) {
				parent->color = RED;
				parent->left->color = BLACK;
				rbtRotateRight(&root, parent);
			}
			if ((parent->left->right->color == BLACK) && (parent->left->left->color == BLACK)) {
				parent->left->color = RED;
				if (parent->color == BLACK) {
					reBuildAfterDelete(parent->parent, parent);
				}
				else {
					parent->color = BLACK;
				}
			}
			else {
				if (parent->left->right->color == RED && parent->left->left->color == BLACK) {
					parent->left->color = RED;
					parent->left->right->color = BLACK;
					rbtRotateLeft(&root, parent->left);
				}
				parent->left->color = parent->color;
				parent->color = BLACK;
				parent->left->left->color = BLACK;
				rbtRotateRight(&root, parent);
			}
		}
	}
	void printRBTree() {
		inorderTraversal(root);
		cout << endl;
		printTree(root, 0, 0);
	}
	void inorderTraversal(RBTNode* node) {
		if (node == NIL) {
			return;
		}
		else {
			inorderTraversal(node->left);
			cout << node->data << ' ';
			inorderTraversal(node->right);
		}
	}
	void printTree(RBTNode* node, int depth, int blackcount) {
		if (node == NIL) {
			return;
		}
		if (depth >= 1) {
			for (int i = 0; i < depth; i++) {
				cout << ' ';
			}
		}
		cout << node->data << ' ';
		if (node->color == BLACK) {
			cout << "BLACK" << ' ';
			blackcount++;
		}
		else{
			cout << "RED" << ' ';
		}
		cout << '[';
		if (node->parent == nullptr) {
			cout << "ROOT";
		}
		else if (node->parent->right == node) {
			cout << 'R' << ',' << node->parent->data;
		}
		else {
			cout << 'L' << ',' << node->parent->data;
		}
		cout << ']';
		if ((node->right == NIL) && (node->left == NIL)) {
			cout << "       " << blackcount;
		}
		cout << endl;
		printTree(node->left, depth + 1, blackcount);
		printTree(node->right, depth + 1, blackcount);
	}
private:
	RBTNode* root;
	RBTNode* NIL;
};
int main() {
	RBTree* tre = new RBTree();
	tre->rbtInsertData(5);
	tre->rbtInsertData(10);
	tre->rbtInsertData(2);
	tre->rbtInsertData(3);
	tre->rbtInsertData(8);
	tre->rbtInsertData(1);
	tre->rbtInsertData(9);
	tre->rbtInsertData(20);
	tre->rbtInsertData(17);
	tre->rbtInsertData(7);
	tre->rbtInsertData(12);
	tre->rbtInsertData(4);
	tre->rbtInsertData(6);
	tre->rbtInsertData(11);
	tre->rbtInsertData(13);
	tre->printRBTree();
	tre->rbtDeleteNode(7);
	tre->rbtDeleteNode(5);
	tre->rbtDeleteNode(8);
	tre->rbtDeleteNode(12);
	tre->rbtDeleteNode(9);
	tre->rbtDeleteNode(17);
	tre->printRBTree();
	return 0;
}