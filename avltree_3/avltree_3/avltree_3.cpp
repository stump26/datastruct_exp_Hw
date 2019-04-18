/*
다음과 같이 10 개의 정수들이 균형이진탐색트리(balanced binary search tree)를 수행하는 C++ 프로그램을 작성하시오.
      58    43    27    13    21    18    35    38    41    32
정수를 차례로 하나씩 입력하며, 
정수가 입력될 때마다 균형이진탐색트리를 형성하고, 
트리를 preorder traverse한 결과를 출력한다.
*/
#include <iostream>
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
	Node *insert(Node*, int);
	Node *balenced(Node*);
	void inorder(Node*);
	void preorder(Node*);
	Bal_Tree() {}
};

int main()
{
	int input;
	Bal_Tree Tree;

	while (1) {
		cout << "data>>";
		cin >> input;
		root = Tree.insert(root, input);
		Tree.preorder(root);
		cout << endl;
	}

	return 0;

}
Node * Bal_Tree::insert(Node *root, int key) {
	Node *fp = NULL;
	Node *p = root;
	Node *q;
	Node *fya = NULL;
	Node *ya = p;
	Node *s;
	int imbal;
	if (root == NULL) {
		q = maketree(key);
		q->bal = 0;
		return q;
	}
	while (p != NULL) {  /* 위치 탐색 */
		if (key == p->key)   //키값이 동일한경우 그대로 반환
			return(root);
		q = (key < p->key) ? p->left : p->right; //키의 크기가 노드p의 값보다 작으면 왼쪽 크면 오른쪽 주소를 q에넣어준다.
		if (q != NULL)  //p가 리프노드일떄까지 
			if (q->bal != 0) {
				fya = p;
				ya = q;
			} /* end if */
		fp = p; //노드를 한단계 내려간다.
		p = q;
	}

	/* 새로운 노드를 삽입 */
	q = maketree(key);
	q->bal = 0;
	(key < fp->key) ? fp->left = q : fp->right = q;
	/* 노드 ya 와 노드 q 사이에 있는 노드들의
		균형 값을  0 으로부터 바꿔준다. */
	p = (key < ya->key) ? ya->left : ya->right;
	s = p;                     /* ya의 자식 노드 */
	while (p != q) {     /* 균형 값 교체 */
		if (key < p->key) {
			p->bal = 1;
			p = p->left;
		}
		else {
			p->bal = -1;
			p = p->right;
		}
	} /* end while */

	/* 트리는 균형된 상태로 남는다. */
	imbal = (key < ya->key) ? 1 : -1;
	if (ya->bal == 0) {
		ya->bal = imbal;
		return(root);
	}
	if (ya->bal != imbal) {   /* 반대방향으로노드 삽입 */
		ya->bal = 0;                   
		return(root);
	}
	/* 필요한 회전으로 다시 균형 잡기 */
	if (s->bal == imbal) {  /* ya와 s는같은 방향으로균형이 깨졌음 (a) 경우      */
		p = s;                          
		if (imbal == 1)           
			R_rotation(ya);
		else
			L_rotation(ya);
		ya->bal = 0;
		s->bal = 0;
	} /* end if */
	else {                           /* ya 와 s 는 반대 방향으로 균형이 깨졌음(b)의 경우 */
		if (imbal == 1) {         
			p = s->right;             
			L_rotation(s);
			ya->left = p;
			R_rotation(ya);
		} /* end if */
		else {
			p = s->left;
			R_rotation(s);
			ya->right = p;
			L_rotation(ya);
		} /* end else */
		if (p->bal == 0) {   /* 포함된 노드들의 균형 값을 조정 */
			ya->bal = 0;           
			s->bal = 0;
		}
		else{
			if (p->bal == imbal) {  /* (b) 경우 */
				ya->bal = -imbal;
				s->bal = 0;
			}
			else {
				ya->bal = 0;
				s->bal = imbal;
			} /* end else */
		}
		p->bal = 0;
	} /* end else */
	if (fya == NULL)    /* 회전된 서브 트리의  포인터를 조정          */
		root = p;             
	else
	{
		(ya == fya->right) ? fya->right = p :fya->left = p;
	}
	return(root);
}
Node *Bal_Tree::R_rotation(Node *p) {
	Node *q, *hold;
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
Node * Bal_Tree::maketree(int key) {
	Node *q = new Node;
	q->key = key;
	q->bal = 0;
	q->left = NULL;
	q->right = NULL;
	return q;
}
void Bal_Tree::inorder(Node *p) {
	if (p == NULL)	return;
	inorder(p->left);
	cout << p->key <<" ";
	inorder(p->right);
}
void Bal_Tree::preorder(Node *p) {
	if (p == NULL)
		return;
	cout << p->key << " ";
	preorder(p->left);
	preorder(p->right);
}