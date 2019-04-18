#include "pch.h"
#include <iostream>
using namespace std;

typedef struct _balnode {
	int key, r;
	Node left, right;
	int bal;
}Node;
Node *maketree(int rec, int key);
class balTree {
public:
	Node Height(Node *);
	int diff(Node);
	Node *R_rotation(Node *);
	Node *L_rotarion(Node *);
	Node *balance(Node *);
	Node *insert(Node *, int);
	void display(Node * ,int);
	void inorder(Node *);
	void preorder(Node *);
	balTree() {
		
	}
};
int main()
{

}
Node * balTree::insert(Node *p, int value)
{
	// 현재 트리가 비었을 때 
	if (p == NULL){
		p = new Node;
		p->key = value;
		p->bal = 0l
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	else if (value < p->key){
		p->left = insert(p->left, value);
		p = balance(p);
	}else if (value == p->key) {
		return ;
	}
	// 크기가 큰경우 오른쪽 서브트리에 삽입합니다. 
	else if (value >= p->key){
		p->right = insert(p->right, value);
		p = balance(p);
	}
	return p;
}
Node *balance(fp) {
	int factor
}

