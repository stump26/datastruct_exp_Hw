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
	Node *insleaf(int,Node*,int);
	Node *makeTree(int);
	Node *insnode(Node*, int, int, Node*);
	void *split(Node*, int, int, Node*, Node*, int);
	void copy(Node*, int, int, Node*);
	int index(Node*);
	BTree() {}
	BTree(int key) {
		makeTree(key);
	}
};

int main() {
	int input;
	BTree tree;
	Node* root; 
	cout << "data>>";
	cin >> input;
	tree.insleaf(input, root, 0);
	return 0;
}
void BTree::copy(Node *nd1, int first, int last, Node* nd2) {
	nd1->numtree = last - first + 1;
	for (int i = first; i <= last; i++) {
		nd1->k[i] = nd2->k[i - first];
		nd1->son[i] = nd2->son[i - first];
		nd2->numtree++;
	}
}
void *BTree::split(Node* nd, int pos, int newkey, Node* newnode, Node* nd2, int midkey) {
	nd2 = new Node;
	nd2->numtree = 0;
	int ndiv2 = DEGREE / 2;
	if (pos > ndiv2) {        /* newkey 는 노드 node(nd2)에 속한다 */
		copy(nd, ndiv2 + 1, DEGREE - 2, nd2);
		insnode(nd2, pos - ndiv2 - 1, newkey, newnode);
		nd->numtree = ndiv2 + 1;
		midkey = nd->k[ndiv2];
		return;
	}
	if (pos == ndiv2) {      /* newkey 가 중간 키가 된다. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		nd->numtree = ndiv2 + 1;
		nd2->son[0] = newnode;
		midkey = newkey;
		return;
	}
	if (pos < ndiv2) {        /* newkey 는 노드 node(nd)에 속한다. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		nd->numtree = ndiv2;
		insnode(nd, pos, newkey, newnode);
		midkey = nd->k[ndiv2];
		return;
	}
}
Node *BTree::insnode(Node* nd, int pos, int newkey, Node* newnode) {
	for (int i = nd->numtree - 1; i >= pos + 1; i--) {
		nd->son[i+1] = nd->son[i];
		nd->k[i] = nd->k[i-1];
	}
	nd->son[pos + 1] = newnode;
	nd->k[pos] = newkey;
	nd->numtree += 1;
}
int BTree::index(Node *nd) {
	for (int i = 0; i < nd->father->numtree; i++) {
		if (nd == nd->father->son[i])
			return i;
	}
	return -1;
}
Node *BTree::insleaf(int key, Node* s, int position) {
	Node *tree;
	Node *nd = s;
	int pos = position;
	Node *newnode = NULL;
	int newkey = key;
	Node *f = nd->father;
	//Node *nd2;
	while (f != NULL && nd->numtree == DEGREE) {
		Node *nd2 =NULL;
		int midkey = nd->k[nd->numtree / 2];
		split(nd, pos, newkey, newnode,nd2, midkey);
		newnode = nd2;
		pos = index(nd);
		nd = f;
		f = nd->father;
		newkey = midkey;	
	}
	if (nd->numtree < DEGREE) {
		insnode(nd, pos, newkey, newnode);
		return;
	}
	Node *nd2 = NULL;
	int midkey = nd->k[nd->numtree / 2];
	split(nd, pos, newkey, newnode, nd2, midkey);
	tree = new Node();
	tree->k[0] = midkey;
	tree->son[0] = nd;
	tree->son[1] = nd2;

}