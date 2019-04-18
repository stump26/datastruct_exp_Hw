//input={50,85,12,80,120,70,150,10,60,37,100,25,62,67,110,65,6}
#include <iostream>
using namespace std;

static const int _DEGREE = 4;

typedef struct _node {
	int key[_DEGREE - 1];
	struct _node *son[_DEGREE];
	struct _node *father;
	int numKeys;
	int numTrees;
}Node;
Node *root;
class M_Tree {
public:
	Node *maketree(int);
	Node *search(Node *,int*,int);	
	Node *find(Node*, int, int*, bool*);
	Node *Insert(Node* root, int key);
	int nodeSearch(Node *, int);
	void insleaf(Node*, int*, int);
	void insfull(Node*, int*, int);
	void traverse(Node*);
	M_Tree() {
		root = NULL;
	}

};

//main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main

int main(void) {
	M_Tree mtree;
	int key;
	while(1) {
		cout << "data>>";
		cin >> key;
		root = mtree.Insert(root, key);
		mtree.traverse(root);
		cout << endl;
	}
	
	return 0;
}
Node *M_Tree::maketree(int key) {
	Node *q = new Node;
	q->numKeys = 0;
	q->father = NULL;
	q->numTrees = 0;
	for (int i = 0; i < _DEGREE - 1; i++) {
		q->key[i] = 0;
		q->son[i] = NULL;
	}
	q->son[_DEGREE-1] = NULL;
	q->key[0] = key;
	q->numKeys++;

	return q;
}

Node* M_Tree::search(Node *root, int *position,int key) {
	int i;
	Node *p = root;
	if (p == NULL) {
		*position = -1;
		return p;
	}
	i = nodeSearch(p, key);
	if (i < p->numTrees - 1 && key == p->key[i]) {
		*position = i;
		return p;
	}
	return(search(p->son[*position], position,key));
}

int M_Tree::nodeSearch(Node *p,int key) {
	int h = 0;
	int min = p->key[p->numKeys-1];
	int min_index=-1;
	for (int i = 0; i < p->numKeys; i++) {
		if (key <= p->key[i]) {
			if (p->key[i] <= min) {
				min = p->key[i];
				min_index = i;
			}
		}
	}
	if (min_index == -1) {
		return p->numKeys;
	}
	return min_index;
}
Node* M_Tree::find(Node* root, int key, int *position, bool *pfound) {
	Node *q = NULL;
	Node *p = root;
	int i;
	while (p != NULL) {
		i = nodeSearch(p, key);
		q = p;
		if (i < p->numKeys && key == p->key[i]) {
			*pfound = true;
			*position = i;
			return(p);
		}
		p = p->son[i];
	}
	*pfound = false;
	*position = i;
	return(q);

}
void M_Tree::insleaf(Node *s, int *position, int key) {
	int nt = s->numKeys;
	s->numKeys++;
	for (int i = _DEGREE - 1; i > *position; i--) { //position뒤의 key를 하나씩 밀기
		s->key[i] = s->key[i-1];
	}
	s->key[*position] = key;
}
void M_Tree::insfull(Node *s, int *position, int key) {
	Node *p = maketree(key);
	s->son[*position] = p;
	s->numTrees++;
	p->father = s;
}
void M_Tree::traverse(Node *root) {
	if (root != NULL) {
		for (int i = 0; i < root->numKeys; i++) {
			if(root->son[i]!=NULL){
				traverse(root->son[i]);
			}
			cout << root->key[i]<<" ";
		}
		if (root->son[root->numKeys] != NULL) { 
			traverse(root->son[root->numKeys]); 
		}
		
	}
}
Node* M_Tree::Insert(Node* root, int key) {
	bool found;
	int position;
	if (root == NULL) {
		root = maketree(key);
		position = 0;
		return(root);
	}
	Node* s = find(root, key, &position, &found);
	if (found == true) {
		return root;
	}
	if (s->numKeys < _DEGREE-1) {
		insleaf(s, &position, key);
		return root;
	}
	else {
		insfull(s, &position, key);
		return root;
	}
}