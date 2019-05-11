//data:[58 43 27 13 21 18 35 38 41 32]

#include<iostream>
using namespace std;

typedef struct _node {
	int key;
	struct _node *left;
	struct _node *right;
	int bal;
}Node;
Node * root;
class Bal_Tree {
public:
	Node *maketree(int);
	int height(Node*);
	Node *checkbal(Node*);
	Node *R_rotation(Node*);
	Node *L_rotation(Node*);
	Node *insert(Node*,int);
	Node *balenced(Node*);
	void inorder(Node*);
	void preorder(Node*);
	Bal_Tree() {
	}
};

int main(void) {
	int input;
	Bal_Tree Tree;
	
	while (1) {
		cout << "data>>";
		cin >> input;
		root = Tree.insert(root,input);
		Tree.preorder(root);
	}

	return 0;
}

Node * Bal_Tree::insert(Node* root, int key) {
	Node *q;
	Node *fp = NULL;
	Node *fya = NULL;
	Node *ya = root;
	Node *p = root;
	if (root == NULL) {
		q = maketree(key);
		return q;
	}
	while (p != NULL) {
		if (key == p->key)
			return(p);
		q = (key < p->key) ? p->left : p->right;
		if (q != NULL)
			if (q->bal != 0) {
				fya = p;
				ya = q;
			}
		fp = p;
		p = q;
	}
	q = maketree(key);
	q->bal = 0;
	(key < fp->key) ? fp->left = q: fp->right = q;

	checkbal(root);
	root=balenced(root);
	return root;
}

Node * Bal_Tree::maketree(int key) {
	Node *q = new Node;
	q->key = key;
	q->bal = 0;
	q->left=NULL;
	q->right= NULL;
	return q;
}

int Bal_Tree::height(Node* p) {
	int h = 0;
	if (p != NULL) {
		int left = height(p->left);
		int right = height(p->right);
		int maxH = (left < right) ? right : left;
		p->bal = left - right;
		h = maxH+1;
	}
	return h;
}
Node *Bal_Tree::checkbal(Node *root) {
	int left, right;
	if (root != NULL) {
		height(root);		
	}
	return root;
}
void Bal_Tree::inorder(Node *p) {
	if (p == NULL)	return;
	inorder(p->left);
	cout << p->key<<"(" << p->bal << ")" << " ";
	inorder(p->right);
}
void Bal_Tree::preorder(Node *p) {
	if (p == NULL)
		return;
	cout << p->key << "(" << p->bal << ")" << " ";
	preorder(p->left);
	preorder(p->right);
}

Node *Bal_Tree::R_rotation(Node *p) {
	Node *q,*hold;
	q = p->left;
	hold = q->right;
	q->right = p;
	p->left = hold;
	return q;
}
Node *Bal_Tree::L_rotation(Node *p) {
	Node *q, *hold;
	q = p->right;
	hold = q->left;
	q->left = p;
	p->right = hold;
	return q;
}
Node *Bal_Tree::balenced(Node *p) {
	if (p != NULL) {
		p->left=balenced(p->left);
		p->right=balenced(p->right);
	}
	else {
		return p;
	}
	if (p->bal > 1)
	{
		if ((p->bal)-(p->left->bal)>2)
		{
			p->left = L_rotation(p->left);
			p = R_rotation(p); 
			checkbal(root);
		}
		else
		{
			p = R_rotation(p);
			checkbal(root);
		}
	}
	else if (p->bal < -1)
	{
		if ((p->bal) - (p->left->bal)<2)
		{
			p->right=R_rotation(p->right);
			p=L_rotation(p);
			checkbal(root);
		}
		else
		{
			p=L_rotation(p);
			checkbal(root);
		}
	}
	return p;
}