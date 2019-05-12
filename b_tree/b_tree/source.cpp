//input={7 20 3 12 11 8 9 13 17 19 14 1 5 10 6 2 15 18 16 21}
//input={1 7 1 20 1 3 1 12 1 11 1 8 1 9 1 13 1 17 1 19 1 14 1 1 1 5 1 10 1 6 1 2 1 15 1 18 1 16 1 21}
#include<iostream>
#include<string>
using namespace std;

const static int DEGREE=5;

typedef struct _node {
	int k[DEGREE - 1];
	struct _node *son[DEGREE];
	struct _node *father;
	int numtree;
	int numkey;
	_node() {
		for (int i = 0; i < DEGREE; i++) {
			this->k[i] = 0;
			this->son[i] = NULL;
		}
		this->son[DEGREE-1] = NULL;
		this->father = NULL;
		this->numtree = 0;
		this->numkey = 0;
	}
}Node;
class BTree {
public:
	Node *makeTree(int);
	void insleaf(int,Node**);
	void delNode(int, Node**);
	void insnode(Node*, int, int, Node*);
	void split(Node*, int, int, Node*, Node*, int*);
	void copy(Node*, int, int, Node*);
	void delkey(Node*, int,int);
	void mergeNode(Node*, Node*, int,int);
	int check_numTree(Node*);
	int index(Node*);
	int findpos(Node*,int);
	Node *findnode(Node *,int);
	void traverse(Node*);
	string node_print(Node*);
	BTree() {}
};


int main() {
	int input,mod;
	BTree tree;
	Node *root=NULL;
	while (true) {
		cout << "-----------" << endl;
		cout << "1.����"<<endl;
		cout << "2.����" << endl;
		cout << "3.���" << endl;
		cout << "��� ���� >> ";
		cin >> mod;

		switch (mod)
		{
		case 1:
			cout << "data>>";
			cin >> input;
			if (root == NULL) {
				root = tree.makeTree(input);
			}
			else {
				tree.insleaf(input, &root);
			}
			break;
		case 2:
			cout << "data>>";
			cin >> input;
			if (root == NULL) {
				cout << "ERROR!! empty tree" << endl;
				break;
			}
			else {
				tree.delNode(input, &root);
			}
			break;
		case 3:
			traverse(root);
			cout << endl;
			break;
		default:
			cout << "===!!����!!====" << endl;
			cout << "�ùٸ� �Է��� ���ּ���." << endl;
			cout << "(1-3 ���� ���� �Է�)" << endl;
			break;
		}
	}
	return 0;
}
void BTree::copy(Node *nd1, int first, int last, Node* nd2) {
	for (int i = 0; i <= last-first; i++) {
		if (first + i <= nd1->numkey) {
			nd2->k[i] = nd1->k[first + i];
			nd1->k[first + i] = 0;

			nd1->numkey--;
			nd2->numkey++;
		}
		if (nd1->son[i+first]!=NULL) {
			nd2->son[i] = nd1->son[i + first];
			nd1->son[i + first] = NULL;

			nd1->numtree--;
			nd2->numtree++;
		}
		
	}
}
void BTree::split(Node* nd, int pos, int newkey, Node* newnode, Node* nd2, int *midkey){
	int ndiv2 = DEGREE / 2;
	
	if (pos > ndiv2) {        /* newkey �� ��� node(nd2)�� ���Ѵ� */
		copy(nd, ndiv2 + 1, DEGREE - 1, nd2);
		insnode(nd2, pos - ndiv2 - 1, newkey, newnode);
		*midkey = nd->k[ndiv2];
		nd->k[ndiv2] = 0;
		nd->numkey--;
		nd->numtree = check_numTree(nd);
		nd2->numtree = check_numTree(nd2);
		return;
	}
	if (pos == ndiv2) {      /* newkey �� �߰� Ű�� �ȴ�. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		nd2->son[0] = newnode;
		*midkey = newkey;
		nd->numtree = check_numTree(nd);
		nd2->numtree = check_numTree(nd2);
		return;
	}
	if (pos < ndiv2) {        /* newkey �� ��� node(nd)�� ���Ѵ�. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		insnode(nd, pos, newkey, newnode);
		*midkey = nd->k[ndiv2];
		nd->k[ndiv2] = 0;
		nd->numkey--;
		nd->numtree = check_numTree(nd);
		nd2->numtree = check_numTree(nd2);
		return;
	}
}
void BTree::insnode(Node* nd, int pos, int newkey, Node* newnode) {
	for (int i = nd->numkey; i > pos; i--) {
		nd->son[i+1] = nd->son[i];
		nd->k[i] = nd->k[i-1];
	}
	nd->son[pos + 1] = newnode;
	nd->k[pos] = newkey;
 	nd->numkey++;
}
int BTree::index(Node *nd) {
	for (int i = 0; i < nd->father->numtree; i++) {
		if (nd == nd->father->son[i])
			return i;
	}
	return -1;
}
int BTree::findpos(Node *nd,int key) {
	if (key <= nd->k[0]) return 0;
	for (int i = 0; i < nd->numkey; i++) {
		if (key > nd->k[i] && key<=nd->k[i+1]) {
			return i+1;
		}
	}
	return nd->numkey;
}
void BTree::insleaf(int key, Node** s){
	Node *nd = findnode(*s,key);
	Node *newnode = NULL;
	int newkey = key;
	Node *f = nd->father;
	//���� ��尡 ��Ʈ��尡 �ƴ��� Ȯ��
	while (f != NULL && nd->numkey + 1 == DEGREE) {
		Node *nd2 = new Node();
		int midkey = nd->k[nd->numkey / 2];
		split(nd, findpos(nd, key), newkey, newnode,nd2, &midkey);
		f->numtree = check_numTree(f);
		nd2->father = f;
		newnode = nd2;
		nd = f;
		f = nd->father;
		newkey = midkey;	
	}
	//��尡 ������ ����
	if (nd->numkey < DEGREE-1) {
		insnode(nd, findpos(nd,key), newkey, newnode);
		return;
	}
	//��Ʈ��尡 ���� split �� �� ��Ʈ��� ����
	Node *nd2 = new Node();
	int midkey = nd->k[nd->numkey / 2];
	split(nd, findpos(nd, key), newkey, newnode, nd2, &midkey);
	Node *tree = new Node();
	tree->k[0] = midkey;
	tree->numkey++;
	nd->father = tree;
	nd2->father = tree;
	tree->son[0] = nd;
	tree->son[1] = nd2;
	tree->numtree = check_numTree(tree);
	*s = tree;
}

Node *BTree::makeTree(int key) {
	Node *nd = new Node();
	nd->father = NULL;
	nd->k[0] = key;
	nd->numkey++;
	return nd;
}
Node *BTree::findnode(Node *s,int key) {
	Node * nd=s;
	while (nd->numtree > 0) {
		int pos = findpos(nd, key);
		if (nd->son[pos] != NULL) {
			nd = nd->son[pos];
		}
	}
	return nd;
}
void BTree::traverse(Node* s) {
	string* result = new string[];
	result[0] = node_print(s);
	if (s->numtree != 0) {
		for (int i = 0; i < s->numtree; i++) {
			Node* nd = s->son[i];
			while (nd->numtree != 0) {

			}
		}
	}

}
/*
void traverse(Node *s) {
	if (s->father == NULL) {
		node_print(s);
		cout << endl;
	}
	for (int i = 0; i < DEGREE; i++) {
		if(s->son[i]!=NULL)
			node_print(s->son[i]);
	}
	cout << endl;
	for (int i = 0; i < DEGREE; i++) {
		if (s->son[i] != NULL)
			traverse(s->son[i]);
	}
}*/
string BTree::node_print(Node *nd) {
	string print="";
	print += "{";
	for (int i = 0; i < DEGREE-1; i++) {
		if (nd!=NULL && nd->k[i] != 0){
			print += nd->k[i]+", ";
		}
	}
	print += "}";

	return print;
}
void BTree::delNode(int key, Node** s) {
	Node* nd = findnode(*s, key);
	int pos = findpos(nd, key);
	if (nd->k[pos] != key) {
		cout << "Key(" << key << ") is not found." << endl;
	}
	else {
		delkey(nd, key, pos);
		if (nd->numkey >= DEGREE / 2) {//����÷ο� ���°��
			return;
		}
		else {//����÷ο��ִ°��
			int nd_pos;
			Node* f=nd->father;
			while (f!=NULL && nd->numkey <= DEGREE/2){
				for (int i = 0; i < f->numtree; i++) {
					if (nd == f->son[i]) { 
						nd_pos = i; break; 
					}
				}
				//numkey > n/2�� ������ �����������.
				if (f->numtree - 1 > nd_pos && f->son[nd_pos + 1]->numkey > DEGREE / 2) {
					int shift_key = f->son[nd_pos+1]->k[0];
					delkey(f->son[nd_pos+1], shift_key, 0);
						
					int tmp = f->k[nd_pos];
					f->k[nd_pos] = shift_key;
					shift_key = tmp;

					insnode(nd, nd->numkey, shift_key, NULL);
				}
				////numkey > n/2�� ���� �����������.
				else if (nd_pos != 0 && f->son[nd_pos - 1]->numkey > DEGREE / 2) {
					int shift_key = f->son[nd_pos - 1]->k[f->son[nd_pos - 1]->numkey-1];
					delkey(f->son[nd_pos - 1], shift_key, f->son[nd_pos - 1]->numkey-1);

					int tmp = f->k[nd_pos-1];
					f->k[nd_pos-1] = shift_key;
					shift_key = tmp;

					insnode(nd, 0, shift_key, NULL);
				}
				//������ ���� ��� ���������� f->son[nd_pos + 1]->numkey<=n/2
				else if (f->numtree - 1> nd_pos && f->son[nd_pos+1]->numkey<=DEGREE/2) {
					mergeNode(nd, f->son[nd_pos + 1], f->k[nd_pos],nd_pos+1);
					delkey(f, f->k[nd_pos], nd_pos);
				}
				//�������� ��� ���������� f->son[nd_pos - 1]->numkey <= n/2 
				else if (nd_pos != 0 && f->son[nd_pos-1]->numkey<=DEGREE/2) {
					mergeNode(f->son[nd_pos-1],nd, f->k[nd_pos-1],nd_pos+1);
					delkey(f, f->k[nd_pos-1], nd_pos-1);
				}
				nd = f;
				f = nd->father;
			}
			if ((*s)->numkey==0) {
				*s = (*s)->son[0];
			}
		}
	}
}
void BTree::delkey(Node* nd, int key, int pos) {
	int diff = nd->numkey - pos;
	for (int i = 0; i < diff; i++) {
		if (i + pos +1 < nd->numkey) {
			nd->k[i + pos] = nd->k[i + pos + 1];
		}
		else {
			nd->k[i + pos] = 0;
		}
	}
	nd->numkey--;
}
void BTree::mergeNode(Node* nd, Node* nd2, int shiftkey,int pos) {
	insnode(nd, nd->numkey, shiftkey, NULL);
	for (int i = 0; i < nd2->numkey; i++) {
		insnode(nd, nd->numkey, nd2->k[i], NULL);
	}
	for (int i = 0; i < nd2->numtree; i++) {
		nd->son[nd->numtree] = nd2->son[i];
		nd->numtree++;
	}
	for (int i = pos; i < nd->father->numtree-1;i++) {
		nd->father->son[i] = nd->father->son[i + 1];
	}
	nd->father->numtree--;
	nd->father->son[nd->father->numtree] = NULL;
}
int BTree::check_numTree(Node* nd){
	int i = 0;
	while (nd->son[i] != NULL) {
		i++;
	}
	return i;
}
