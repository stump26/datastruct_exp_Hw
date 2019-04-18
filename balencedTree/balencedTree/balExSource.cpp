/*
 ���α׷� ���� : C++�� ������ AVL Ʈ���Դϴ�.
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#define NUM_OF_DATA 10
using namespace std;

// ��� ����ü�� �����մϴ�.
struct nodeAVL
{
	int data;
	struct nodeAVL *left;
	struct nodeAVL *right;
	int bal;
} *root;

// Ŭ������ �����մϴ�.
class classAVL
{
public:
	// ����� ���̸� ��ȯ�մϴ�. 
	int height(nodeAVL *);
	// �����μ�(������ ����)�� ��ȯ�մϴ�. 
	int diff(nodeAVL *);
	// RR ȸ�� �Լ��Դϴ�. 
	nodeAVL *rr(nodeAVL *);
	// LL ȸ�� �Լ��Դϴ�. 
	nodeAVL *ll(nodeAVL *);
	// LR ȸ�� �Լ��Դϴ�. 
	nodeAVL *lr(nodeAVL *);
	// RL ȸ�� �Լ��Դϴ�. 
	nodeAVL *rl(nodeAVL *);
	// Ʈ���� ������ ���ߴ� �Լ��Դϴ�. 
	nodeAVL *balance(nodeAVL *);
	// AVL Ʈ���� ���ο� ���Ҹ� �����մϴ�. 
	nodeAVL *insert(nodeAVL *, int);
	// ������ AVL Ʈ�� ������ �����ִ� �Լ��Դϴ�. 
	void display(nodeAVL *, int);
	// AVL Ʈ���� ���� ��ȸ�մϴ�. 
	void inorder(nodeAVL *);
	// AVL Ʈ���� ���� ��ȸ�մϴ�. 
	void preorder(nodeAVL *);
	// AVL Ʈ���� ���� ��ȸ�մϴ�. 
	void postorder(nodeAVL *);
	// classAVL�� �������Դϴ�.
	classAVL()
	{
		root = NULL;
	}
};

int main(void)
{
	int choice, item;
	classAVL AVL;
	int datas[NUM_OF_DATA] = { 58, 43, 27, 13, 21, 18, 35, 38, 41, 32 };
	
	for (int i = 0; i < NUM_OF_DATA; i++) {
		int value = datas[i];
		cout << "<Data [" << value << "] Insert>" << endl;
		root = AVL.insert(root, value);
		cout << "[ ���� ��ȸ ]" << endl;
		AVL.preorder(root);
		cout << endl;
	}
	return 0;
}

// AVL Ʈ���� ���̸� ����մϴ�.
int classAVL::height(nodeAVL* temp)
{
	int h = 0;
	if (temp != NULL)
	{
		// ��������� ���� Ȥ�� ���������� �˻��մϴ�. 
		int left = height(temp->left);
		int right = height(temp->right);
		int maxHeight = max(left, right);
		h = maxHeight + 1;
	}
	return h;
}

// �����μ�(������ ����)�� ��ȯ�մϴ�.
int classAVL::diff(nodeAVL* temp)
{
	// ���� �ڽ��� ���̿� ������ �ڽ��� ���� ���̸� ��ȯ�մϴ�. 
	int left = height(temp->left);
	int right = height(temp->right);
	temp->bal = left - right;
	return temp->bal;
}

// RR ȸ�� �Լ��Դϴ�.
nodeAVL *classAVL::rr(nodeAVL* parent)
{
	nodeAVL *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

// ll ȸ�� �Լ��Դϴ�.
nodeAVL *classAVL::ll(nodeAVL* parent)
{
	nodeAVL *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

// LR ȸ�� �Լ��Դϴ�. 
nodeAVL *classAVL::lr(nodeAVL* parent)
{
	// LR ȸ���� ���� �ڽ��� �������� RR, ������ �������� LLȸ���մϴ�. 
	nodeAVL * temp;
	temp = parent->left;
	parent->left = rr(temp);
	return ll(parent);
}

// RL ȸ�� �Լ��Դϴ�.
nodeAVL *classAVL::rl(nodeAVL* parent)
{
	// LR ȸ���� �ݴ��Դϴ�.
	nodeAVL * temp;
	temp = parent->right;
	parent->right = ll(temp);
	return rr(parent);
}

//������ ���ߴ� �Լ�
nodeAVL *classAVL::balance(nodeAVL *temp)
{
	int factor = diff(temp);
	// ���� ����Ʈ�������� ������ �Ǿ� ������ ���� ����Դϴ�. 
	if (factor > 1)
	{
		// �� ���� �ڽĳ�忡 ������ �߻��߽��ϴ�. 
		if (diff(temp->left) > 0)
		{
			temp = ll(temp);
		}
		// �� ������ �ڽ� ��忡 ������ �߻��߽��ϴ�. 
		else
		{
			temp = lr(temp);
		}
	}
	else if (factor < -1)
	{
		if (diff(temp->right) > 0)
		{
			temp = rl(temp);
		}
		else
		{
			temp = rr(temp);
		}
	}
	return temp;
}

// Ʈ���� ���Ҹ� �����ϴ� �Լ��Դϴ�.
nodeAVL * classAVL::insert(nodeAVL *root, int value)
{
	// ���� Ʈ���� ����� �� 
	if (root == NULL)
	{
		root = new nodeAVL;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	// ũ�ų� ���� ��� ������ ����Ʈ���� �����մϴ�. 
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}

void classAVL::display(nodeAVL * ptr, int level)
{
	int i;
	// ���� Ʈ���� ������� ���� ����Դϴ�. 
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		// ���� ��Ʈ ����� ����Դϴ�. 
		if (ptr == root)
		{
			cout << "Root -> ";
		}
		// i�� ���������� ���� ��Ʈ�� �ƴ� ����� ������ �Դϴ�. 
		for (i = 0; i < level && ptr != root; i++)
		{
			cout << "        ";
		}
		// �ڽ��� ��ġ�� �����͸� ����մϴ�. 
		cout << ptr->data;
		// ���� ��嵵 ������ݴϴ�.
		display(ptr->left, level + 1);
	}
}

/* Ʈ���� ��ȸ�ϴ� �� ���� �Լ��Դϴ�. */
void classAVL::inorder(nodeAVL *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}
void classAVL::preorder(nodeAVL *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);
}
void classAVL::postorder(nodeAVL *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	inorder(tree->right);
	cout << tree->data << "  ";
}