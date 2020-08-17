#include <iostream>

using namespace std;

class BSTNode {
public:
	BSTNode* right;
	BSTNode* left;
	int data;
};

class BSTree {
public:
	BSTree() {
		root = nullptr;
	}
	BSTNode* bstSearchNode(BSTNode* node, int target) {
		if (node == nullptr) {
			return nullptr;
		}
		else {
			if ((node->data) == target) {
				return node;
			}
			else if ((node->data) > target){
				bstSearchNode(node->left, target);
			}
			else {
				bstSearchNode(node->right, target);
			}
		}
	}
	void bstInsertData(int data) {
		if (root == nullptr) {
			BSTNode* newnode = new BSTNode;
			newnode->data = data;
			newnode->left = nullptr;
			newnode->right = nullptr;
			root = newnode;
		}
		else {
			insertNode(root, data);
		}
	}
	void insertNode(BSTNode* node, int data) {
		if (node->data == data) {
			return;
		}
		else if (node->data > data) {
			if (node->left == nullptr) {
				BSTNode* newnode = new BSTNode;
				newnode->data = data;
				newnode->left = nullptr;
				newnode->right = nullptr;
				node->left = newnode;
			}
			else {
				insertNode(node->left, data);
			}
		}
		else {
			if (node->right == nullptr) {
				BSTNode* newnode = new BSTNode;
				newnode->data = data;
				newnode->left = nullptr;
				newnode->right = nullptr;
				node->right = newnode;
			}
			else {
				insertNode(node->right, data);
			}
		}
	}
	BSTNode* bstDeleteNode(int target) {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			return deleteNode(&root, nullptr, target);
		}
	}
	BSTNode* deleteNode(BSTNode** node, BSTNode* parent, int target) {
		if (node == nullptr) {
			return nullptr;
		}
		else {
			BSTNode* remove;
			if ((*node)->data > target) {
				remove = deleteNode(&(*node)->left, (*node), target);
			}
			else if ((*node)->data < target) {
				remove = deleteNode(&(*node)->right, (*node), target);
			}
			else {
				remove = (*node);
				if (((*node)->left == nullptr) && ((*node)->right == nullptr)) {
					if (parent != nullptr) {
						if (parent->left == (*node)) {
							parent->left = nullptr;
						}
						else {
							parent->right = nullptr;
						}
					}
					(*node) = nullptr;
				}
				else {
					BSTNode* tmp;
					if (((*node)->left != nullptr) && ((*node)->right != nullptr)) {
						BSTNode* par;
						par = (*node);
						tmp = (*node)->right;
						while (tmp->left != nullptr) {
							par = tmp;
							tmp = tmp->left;
						}
						tmp->left = (*node)->left;
						if (par != (*node)) {
							if (tmp->right != nullptr) {
								par->left = tmp->right;
							}
							else {
								par->left = nullptr;
							}
							tmp->right = (*node)->right;
						}
					}
					else {
						if ((*node)->left != nullptr) {
							tmp = (*node)->left;
						}
						else {
							tmp = (*node)->right;
						}
					}
					if (parent != nullptr) {
						if (parent->right == (*node)) {
							parent->right = tmp;
						}
						else {
							parent->left = tmp;
						}
					}
					(*node) = tmp;
				}
			}
			return remove;
		}
	}
	void bstInorderTraversal() {
		inorderTraversal(root);
	}
	void inorderTraversal(BSTNode* node) {
		if (node == nullptr) {
			return;
		}
		else {
			inorderTraversal(node->left);
			cout << node->data << ' ';
			inorderTraversal(node->right);
		}
	}
	bool isEmpty() {
		if (root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	BSTNode* root;
};

int main() {
	BSTree* bstree = new BSTree;
	bstree->bstInsertData(10);
	bstree->bstInsertData(10);
	bstree->bstInsertData(5);
	bstree->bstInsertData(15);
	bstree->bstInsertData(3);
	bstree->bstInsertData(7);
	bstree->bstInsertData(18);
	bstree->bstInsertData(25);
	bstree->bstInsertData(1);
	bstree->bstInsertData(9);
	bstree->bstInorderTraversal();
	cout << endl;
	bstree->bstDeleteNode(15);
	bstree->bstInorderTraversal();
	cout << endl;
	bstree->bstDeleteNode(18);
	bstree->bstInorderTraversal();
	cout << endl;
	bstree->bstDeleteNode(25);
	bstree->bstInorderTraversal();
	return 0;
}