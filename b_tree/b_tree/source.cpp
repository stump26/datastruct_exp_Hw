#include<iostream>
using namespace std;

const static int DEGREE=5;

typedef struct _node {
	int k[DEGREE - 1];
	Node *son[DEGREE];
	Node *father;
	int numtree;
}Node;
class BTree {
public:
	Node *find();
	Node *insleaf(int,Node*,Node*);
	Node *makeTree(int);
	Node *insnode(Node*, Node*, int, Node*);
	void *split(Node*, Node*, int, Node*, Node*, int);
	int index(Node*);
	BTree() {}
	BTree(int key) {
		makeTree(key);
	}
};

int main() {


	return 0;
}
void *split(Node* nd, Node* pos, int newkey, Node* newnode, Node* nd2, int midkey) {

}
Node *insnode(Node* nd, Node* pos, int newkey, Node* newnode) {
	
}
Node *insleaf(int key, Node* s, Node* position) {
	Node *nd = s;
	Node *pos = position;
	Node *newnode = NULL;
	int newkey = key;
	Node *f = nd->father;
	//Node *nd2;
	while (f != NULL && nd->numtree ==DEGREE) {
		Node *nd2 =NULL;
		split(nd, pos, newkey, newnode,nd2, nd->k[nd->numtree / 2]);
	}
}