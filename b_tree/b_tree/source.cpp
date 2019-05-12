//input={7 20 3 12 11 8 9 13 17 19 14 1 5 10 6 2 15 18 16 21}
//input={1 7 1 20 1 3 1 12 1 11 1 8 1 9 1 13 1 17 1 19 1 14 1 1 1 5 1 10 1 6 1 2 1 15 1 18 1 16 1 21}
#include<iostream>
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
	int index(Node*);
	int findpos(Node*,int);
	Node *findnode(Node *,int);
	BTree() {}
};
void traverse(Node *);
void node_print(Node *);

int main() {
	int input,mod;
	BTree tree;
	Node *root=NULL;
	while (true) {
		cout << "-----------" << endl;
		cout << "1.삽입"<<endl;
		cout << "2.삭제" << endl;
		cout << "3.출력" << endl;
		cout << "기능 선택 >> ";
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
			cout << "===!!오류!!====" << endl;
			cout << "올바른 입력을 해주세요." << endl;
			cout << "(1-3 내의 정수 입력)" << endl;
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
	if (pos > ndiv2) {        /* newkey 는 노드 node(nd2)에 속한다 */
		copy(nd, ndiv2 + 1, DEGREE - 1, nd2);
		insnode(nd2, pos - ndiv2 - 1, newkey, newnode);
		*midkey = nd->k[ndiv2];
		nd->k[ndiv2] = 0;
		nd->numkey--;
		return;
	}
	if (pos == ndiv2) {      /* newkey 가 중간 키가 된다. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		nd2->son[0] = newnode;
		*midkey = newkey;
		return;
	}
	if (pos < ndiv2) {        /* newkey 는 노드 node(nd)에 속한다. */
		copy(nd, ndiv2, DEGREE - 2, nd2);
		insnode(nd, pos, newkey, newnode);
		*midkey = nd->k[ndiv2];
		nd->k[ndiv2] = 0;
		nd->numkey--;
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
	//꽉찬 노드가 루트노드가 아닌지 확인
	while (f != NULL && nd->numkey + 1 == DEGREE) {
		Node *nd2 = new Node();
		int midkey = nd->k[nd->numkey / 2];
		split(nd, findpos(nd, key), newkey, newnode,nd2, &midkey);
		f->numtree++;
		nd2->father = f;
		newnode = nd2;
		nd = f;
		f = nd->father;
		newkey = midkey;	
	}
	//노드가 꽉차지 않음
	if (nd->numkey < DEGREE-1) {
		insnode(nd, findpos(nd,key), newkey, newnode);
		return;
	}
	//루트노드가 꽉차 split 후 새 루트노드 생성
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
	tree->numtree = DEGREE / 2;
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
}
void node_print(Node *nd) {
	cout << "{";
	for (int i = 0; i < DEGREE-1; i++) {
		if (nd!=NULL && nd->k[i] != 0){
			cout << nd->k[i]<<", ";
		}
	}
	cout << "}"<<nd->numtree;
}
void BTree::delNode(int key, Node** s) {
	Node* nd = findnode(*s, key);
	int pos = findpos(nd, key);
	if (nd->k[pos] != key) {
		cout << "Key(" << key << ") is not found." << endl;
	}
	else {
		delkey(nd, key, pos);
		if (nd->numkey >= DEGREE / 2) {//언더플로우 없는경우
			return;
		}
		else {//언더플로우있는경우
			int nd_pos;
			Node* f=nd->father;
			while (f!=NULL){
				for (int i = 0; i < f->numtree; i++) {
					if (nd == f->son[i]) { 
						nd_pos = i; break; 
					}
				}
				//numkey > n/2인 오른쪽 형제노드존재.
				if (f->numtree - 1 > nd_pos && f->son[nd_pos + 1]->numkey > DEGREE / 2) {
					int shift_key = f->son[nd_pos+1]->k[0];
					delkey(f->son[nd_pos+1], shift_key, 0);
						
					int tmp = f->k[nd_pos];
					f->k[nd_pos] = shift_key;
					shift_key = tmp;

					insnode(nd, nd->numkey, shift_key, NULL);
				}
				////numkey > n/2인 왼쪽 형제노드존재.
				else if (nd_pos != 0 && f->son[nd_pos - 1]->numkey > DEGREE / 2) {
					int shift_key = f->son[nd_pos - 1]->k[f->son[nd_pos - 1]->numkey-1];
					delkey(f->son[nd_pos - 1], shift_key, f->son[nd_pos - 1]->numkey-1);

					int tmp = f->k[nd_pos-1];
					f->k[nd_pos-1] = shift_key;
					shift_key = tmp;

					insnode(nd, 0, shift_key, NULL);
				}
				nd = f;
				f = nd->father;
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