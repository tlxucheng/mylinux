// RBTree-master.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include "RBTree-master.h"
#include<cstdio>
#include<iostream>
//#include"RBTree.h"
using namespace std;


/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template<class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)//��������Ǳ���ģ�ɾ�˻ᱨ��
{
	RBTNode<T>* y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	RBTNode<T>* x = y->left;
	y->left = x->right;
	if (x->right != nullptr)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* y = nullptr;
	RBTNode<T>* x = root;

	while (x != nullptr)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != nullptr)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	node->color = RED;

	insertFixUp(root, node);
}

template<class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *parent;
	RBTNode<T> *gparent;

	while ((parent = rb_parent(node)) && rb_is_red(parent))//whileѭ���������Ǹ��ڵ�Ϊ�졣���ں�����ĸ���Ϊ�ڣ����Ը��������Ǹ���������ϱ��Դ��ڵ㼴�游��
	{
		gparent = rb_parent(parent);

		if (parent == gparent->left)
		{
			RBTNode<T> *uncle = gparent->right;

			//Case1����������ڵ��Ǻ�ɫ
			if (uncle && rb_is_red(uncle))//�ں�����У�Ҷ�ӽڵ�����null��Ҳ���Ǻ�ɫ�ڵ㣬��˼�ʹuncle��nullptr��Ҳ�����Ǻ�ɫ�Ľڵ�
			{
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//Case2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if ((!uncle || rb_is_black(uncle)) && (parent->right == node))
			{
				RBTNode<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
				continue;
			}

			//Case3�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if ((!uncle || rb_is_black(uncle)) && (parent->left == node))
			{
				rb_set_black(parent);
				rb_set_red(gparent);
				rightRotate(root, gparent);
				continue;
			}
		}

		else//���ڵ����游�ڵ���Һ���  //�ܶ�ԳƷ������
		{
			RBTNode<T>* uncle = gparent->left;
			//Case1�����������ڵ��Ǻ�ɫ
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(uncle);
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//Case2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if ((!uncle || rb_is_black(uncle)) && (parent->left == node))//�������
			{
				RBTNode<T>* tmp;
				rightRotate(root, parent);//�������
				tmp = parent;
				parent = node;
				node = tmp;
				continue;
			}

			//Case3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if ((!uncle || rb_is_black(uncle)) && (parent->right == node))//�������
			{
				rb_set_black(parent);
				rb_set_red(gparent);
				leftRotate(root, gparent);//�������
				continue;
			}
		}
	}

	rb_set_black(root);//������Ľڵ��Ǹ��ڵ���ֱ��Ϳ�ڣ�������Ľڵ�ĸ��ڵ��Ǻ�ɫ��ʲôҲ���ùܼ���
}


template<class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* child, *parent;
	RBTColor color;

	if ((node->left != nullptr) && (node->right != nullptr))// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	{
		RBTNode<T>* replace = node;

		replace = replace->right;
		while (replace->left != nullptr)
			replace = replace->left;

		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			root = replace;

		child = replace->right;//�����child��replace�ĺ�һ���ڵ�
		parent = rb_parent(replace);
		color = rb_color(replace);

		if (parent == node)
			parent = replace;//parent���մ洢����child�ĸ��ڵ�
		else
		{
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)//��������ע������������ʧ������replace�ڵ㣬color�洢���ǡ���ʧ���Ľڵ����ɫ
			removeFixUp(root, child, parent);//ͨ��RB - DELETE�㷨������֪����ɾ���ڵ�y֮��xռ����ԭ���ڵ�y��λ�á�������node�ڵ㱻replace�滻�ˣ�ʵ�ʡ���ʧ������replace�ڵ㣬child�ڵ�ռ����ԭreplace�ڵ����λ��

		delete node;
		return;
	}

	if (node->left != nullptr)
		child = node->left;//�����child��node�ĺ�һ���ڵ�
	else
		child = node->right;

	parent = node->parent;
	color = node->color;//color�洢���ǡ���ʧ���Ľڵ����ɫ

	if (child)
		child->parent = parent;

	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)//���ɾ�����Ǻ�ɫ�ڵ㣬��ôԭ��������������ɱ��֣���ʱ��������������
		removeFixUp(root, child, parent); //ͨ��RB - DELETE�㷨������֪����ɾ���ڵ�y֮��xռ����ԭ���ڵ�y��λ�á����������ʧ���ľ���node��child�ڵ�ռ����node�ڵ����λ��

	delete node;
}

template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent)//ֻ�С���ʧ����ɫ�ڵ��ʱ��Ż���øú�����������ʧ�ĺ�ɫ����Ϊ������ָ�ġ�����һ��ĺ�ɫ��
{
	RBTNode<T>* other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;

			//Case1��x���ֵ�w�Ǻ�ɫ��
			if (other && rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			//Case2��x���ֵ�w�Ǻ�ɫ�ģ���w����������Ҳ���Ǻ�ɫ��
			if ((!other || rb_is_black(other)) && (!other->left || rb_is_black(other->left)) && (!other->right || rb_is_black(other->right)))
			{
				rb_set_red(other);
				node = parent;//node�������parent����������һ���������ߵ���Ը���λ�ù�ϵ�Ա��ֲ���
				parent = rb_parent(node);
				continue;
			}
			//Case3��x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ����Ǻ�ɫ
			if ((!other || rb_is_black(other)) && (other->left && rb_is_red(other->left)) && (!other->right || rb_is_black(other->right)))
			{
				rb_set_black(other->left);
				rb_set_red(other);
				rightRotate(root, other);
				other = parent->right;
				continue;
			}
			//Case4��x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ���������
			if ((!other || rb_is_black(other)) && (other->right && rb_is_red(other->right)))
			{
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;//��һ������˵��������㷨Ӧ�ý���������
			}

		}
		else//�ܶ�ԳƷ������
		{
			other = parent->left;//�������
								 //Case1��x���ֵ�w�Ǻ�ɫ��
			if (other && rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);//�������
				other = parent->left;//�������
				continue;
			}
			//Case2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
			if ((!other || rb_is_black(other)) && (!other->left || rb_is_black(other->left)) && (!other->right || rb_is_black(other->right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
				continue;
			}
			//Case3��x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ�ģ��Һ���Ϊ��ɫ��
			if ((!other || rb_is_black(other)) && (other->left && rb_is_red(other->left)) && (!other->right || rb_is_black(other->right)))
			{
				rb_set_black(other->right);//�������
				rb_set_red(other);
				leftRotate(root, other);//�������
				other = parent->left;//�������
				continue;
			}
			//Case4��x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ
			if ((!other || rb_is_black(other)) && (other->right && rb_is_red(other->right)))
			{
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);//�������
				rightRotate(root, parent);//�������
				node = root;
				break;
			}

		}
	}

	if (node)//���node�Ǻ�ɫ��ֱ�Ӱ�nodeͿ�ɺ�ɫ���ɣ����node�Ǻ�ɫ���Ǹ��������κβ�������
		rb_set_black(node);
}

template<class T>
RBTree<T>::RBTree() :mRoot(nullptr) {}

template<class T>
RBTree<T>::~RBTree()
{
	destroy();
}

template<class T>
void RBTree<T>::preOrder(RBTNode<T>* tree)const
{
	if (tree != nullptr)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void RBTree<T>::inOrder(RBTNode<T>* tree)const
{
	if (tree != nullptr)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}

template<class T>
void RBTree<T>::postOrder(RBTNode<T>* tree)const
{
	if (tree != nullptr)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}

/*
* (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
*/
template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key)const
{
	if (x == nullptr || x->key == key)
		return x;
	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

/*
* (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
*/
template<class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key)const
{
	while ((x != nullptr) && (x->key != key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

/*
* ������С��㣺����treeΪ�����ĺ��������С��㡣
*/
template<class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

/*
* ��������㣺����treeΪ�����ĺ����������㡣
*/
template<class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

/*
* �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
*/
template<class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T>* x)
{
	if (x->right != nullptr)
		return minimum(x->right);
	// ���xû���Һ��ӡ���x���������ֿ��ܣ�
	// (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
	// (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
	RBTNode<T>* y = x->parent;
	while ((y != nullptr) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
* �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
*/
template<class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T>* x)
{
	if (x->left != nullptr)
		return maximum(x->left);

	// ���xû�����ӡ���x���������ֿ��ܣ�
	// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
	// (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
	RBTNode<T>* y = x->parent;
	while ((y != nullptr) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
	if (tree == nullptr)
		return;
	if (tree->left != nullptr)
		destroy(tree->left);//�Ҳ���return��û����ţ���
	if (tree->right != nullptr)
		destroy(tree->right);

	delete tree;
	tree = nullptr;
}

/*
* ��ӡ"���������"
*
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
template<class T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
	if (tree != nullptr)
	{
		if (direction == 0)
			cout << tree->key << "(B) is root" << endl;
		else
			cout << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") << "is" << key << "'s" << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}


//���Գ���
int main()
{
	int a[] = { 10,40,30,60,90,70,20,50,80 };
	int len = sizeof(a) / sizeof(a[0]);//��sizeof(int)Ҫ�õö�
	RBTree<int>* tree = new RBTree<int>();//tree��ֻ��һ�Ѻ����ļ��ϣ����������ڵ�����RBTNode

	cout << "==ԭʼ���ݣ�";
	for (int i = 0; i < len; ++i)
		cout << a[i] << " ";
	cout << endl;

	for (int i = 0; i < len; ++i)
	{
		RBTNode<int>* z = new RBTNode<int>(a[i], RED, nullptr, nullptr, nullptr);//����дRED
		tree->insert(tree->mRoot, z);
		cout << "==��ӽڵ㣺" << a[i] << endl;
		cout << "==������ϸ��Ϣ��" << endl;
		tree->print(tree->mRoot, tree->mRoot->key, 0);
		cout << endl;
	}

	cout << "==ǰ�������";
	tree->preOrder(tree->mRoot);

	cout << "\n==���������";
	tree->inOrder(tree->mRoot);

	cout << "\n==���������";
	tree->postOrder(tree->mRoot);
	cout << endl;

	cout << "==��Сֵ��" << tree->minimum(tree->mRoot)->key << endl;
	cout << "==���ֵ��" << tree->maximum(tree->mRoot)->key << endl;
	cout << "==������ϸ��Ϣ��" << endl;
	tree->print(tree->mRoot, tree->mRoot->key, 0);

	for (int i = 0; i < len; ++i)
	{
		//RBTNode<int>* z = new RBTNode<int>(a[i], RED, nullptr, nullptr, nullptr);//�½��ĵ㣬���Ҹ�����nullptr�����������������еĽڵ㣡
		RBTNode<int>* node;
		if ((node = tree->search(tree->mRoot, a[i])) != nullptr)
		{
			tree->remove(tree->mRoot, node);
			cout << "==ɾ���ڵ㣺" << a[i] << endl;
			cout << "==������ϸ��Ϣ��" << endl;
			if (tree->mRoot != nullptr)
				tree->print(tree->mRoot, tree->mRoot->key, 0);
			cout << endl;
		}
	}

	tree->destroy(tree->mRoot);

	return 0;
}

