#pragma once
#include <iostream>
#include <string>

using namespace std;

// Tree�� �����ϴ� Node (node data, left ������, right ������)
template<class T>
struct Node
{
	T data;
	Node* left;
	Node* right;
};


/**
*	Binary Search Tree
*/
template<class T>
class BinarySearchTree
{
public:
	// ������
	BinarySearchTree();

	// �Ҹ���
	~BinarySearchTree();

	// ���������
	BinarySearchTree(BinarySearchTree<T>& Tree);

	// ���Կ�����
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& Tree);

	/**
	*	@brief	Tree�� Empty���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� ��������� true����, �ƴϸ� false ����
	*/
	bool IsEmpty()const;

	/**
	*	@brief	Tree�� Full���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� Full�̸� true ����, �ƴϸ� false ����
	*/
	bool IsFull()const;

	/**
	*	@brief	Tree�� ����
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree�� node�� �� ������ Ȯ����
	*	@pre	none
	*	@post	none
	*	@return	Tree�� node ������ ����
	*/
	int GetLength() const;

	/**
	*	@brief	Tree�� �� node�� �߰��Ѵ�
	*	@pre	ItemType�� ��ü�� ����
	*	@post	Tree�� �� node�� �߰���
	*	@return	�� node �߰��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int Add(T& item);

	/**
	*	@brief	Tree���� ������� �ϴ� node�� ã�� ����
	*	@pre	ItemType�� ��ü�� ����
	*	@post	Tree���� �Է��� node�� ������
	*	@return	node ������ �����ϸ� return 1, �ƴϸ� return 0
	*/
	int DeleteItem(T item);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã���� �ϴ� item�� �˻������ ���� found ����
	*	@post	node�� Tree�� �ִ��� �˻������ �˷���
	*/
	void RetrieveItem(T& item, bool &found)const;

	/**
	*	@brief	Tree�� node�� ��ũ���� ����Ѵ�.
	*	@pre	none
	*	@post	��ũ���� Tree�� InOrder, PreOrder, PostOrder ������� ���� ��µ�.
	*/
	void PrintTree(ostream &out)const;

	/**
	*	@brief	data�� name�� name�� ���� T�����Ͱ� ������ ������ �ּ� ��ȯ
	*	@pre	none.
	*	@post	none.
	*	@param	data	��ȯ�ϰ��� �ϴ� �������� name�� ����
	*	@return	data�� name�� �������� name�� ������ �ش� �������� ������ �ּ� ��ȯ, ���� name�� ���� �����Ͱ� ������ NULL ��ȯ
	*/
	T* GetPointer(T& data);

	/**
	*	@brief	DataList�� node�� data�� �ּҰ��� ����
	*	@pre	none.
	*	@post	none.
	*	@param	DataList	node�� data�� �ּҰ��� ���� �迭
	*/
	void StoreData(T** DataList);

private:
	Node<T>* root;		// Node Ÿ���� root
};

// ������
template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}

// �Ҹ���
template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	MakeEmpty();
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& Tree)
{
	root = NULL;
	T** DataList = new T*[Tree.GetLength()];
	Tree.StoreData(DataList);

	for (int i = 0; i < Tree.GetLength(); i++)
	{
		this->Add(*DataList[i]);
	}
	delete[] DataList;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& Tree)
{
	root = NULL;
	T* DataList = new T[Tree.GetLength()];
	Tree.StoreData(DataList);

	for (int i = 0; i < Tree.GetLength(); i++)
	{
		this.Add(DataList[i]);
	}
	delete[] DataList;

	return (*this);
}

// Tree�� ����ִ��� Ȯ��
template<class T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root == NULL)			// root ��尡 NULL�� ��� true ����
		return true;
	else
		return false;			// root ��尡 NULL�� �ƴ� ��� false ����
}



// Tree�� Full���� Ȯ��
template<class T>
bool BinarySearchTree<T>::IsFull()const
{
	Node* room;					// �ӽ��� node�� �����
	try
	{
		room = new Node;		// �� ��带 �߰��� �� �ִ��� Ȯ��
		delete room;			// �ӽ÷� ���� room ��带 ����
		return false;			// isFull�� ���� false ����
	}
	catch (std::bad_alloc exception)		// �� �̻� ������ �߰��� �� �� ���� Full�� ���
	{
		return true;					// isFull�� ���� true ����
	}
}

// Tree�� ���
template<class T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(root);				// Tree �ʱ�ȭ �Լ� ȣ��
}

// Tree�� node������ �˷���
template<class T>
int BinarySearchTree<T>::GetLength()const
{
	return CountNodes(root);			// node ������ ���� �Լ� ȣ��
}

// Tree�� ���ο� node �߰�
template<class T>
int BinarySearchTree<T>::Add(T& item)
{
	return Insert(root, item);	// �� node �߰��ϴ� �Լ� ȣ��
}

// Tree�� node�� ����
template<class T>
int BinarySearchTree<T>::DeleteItem(T item)
{
	return Delete(root, item);					// �����ϴ� node �����ϴ� �Լ��� ȣ��
}

// Tree���� ã���� �ϴ� ���� node�� �˻�
template<class T>
void BinarySearchTree<T>::RetrieveItem(T& item, bool &found)const
{
	Retrieve(root, item, found);		// Tree �˻� �Լ� ȣ��
}

// Tree�� node�� ������ ������ �����
template<class T>
void BinarySearchTree<T>::PrintTree(ostream &out)const
{
	cout << "\t[InOrder]" << endl;
	PrintInOrderTraversal(root, out);			// InOrder ������� ���

	cout << endl << "\t[PreOrder]" << endl;
	PrintPreOrderTraversal(root, out);			// PreOrder ������� ���

	cout << endl << "\t[PostOrder]" << endl;
	PrintPostOrderTraversal(root, out);			// PostOrder ������� ���
}

// data�� name�� name�� ���� T�����Ͱ� ������ ������ �ּ� ��ȯ
template<class T>
T* BinarySearchTree<T>::GetPointer(T& data)
{
	T* pointer;
	GetDataPointer(root, data, pointer);
	return pointer;
}

template<class T>
void BinarySearchTree<T>::StoreData(T** DataList)
{
	int num = 0;
	AccessInOrder(root, DataList, num);
}

/////////////////////////////Global functions//////////////////////////
// Tree�� �ʱ�ȭ�ϴ� �Լ�
template<class T>
void MakeEmptyTree(Node<T>*& root)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		MakeEmptyTree(root->left);	// root�� �������� ���� �ٽ� MakeEmptyTree �Լ� ȣ��
		MakeEmptyTree(root->right);	// root�� ���������� ���� �ٽ� MakeEmptyTree �Լ� ȣ��
		delete root;
	}
}

// Tree�� node ������ ���� �Լ�
template<class T>
int CountNodes(Node<T>* root)
{
	if (root == NULL)		// root ��尡 null�ϰ�� 0�� ����
		return 0;
	else
		return CountNodes(root->left) + CountNodes(root->right) + 1;		// ����� ����, �����ʿ� ���� ����� ȣ��� root�� �ش��ϴ� 1�� ���ؼ� ���� ����
}

// BinarySearchTree�� ���ο� ��� �߰�
template<class T>
int Insert(Node<T>*& root, T& item)
{
	if (root == NULL)				// root�� null�� ��� 
	{
		root = new Node<T>;	// root ��� ����
		root->left = NULL;			// root ����̹Ƿ� left�� right�� NULL�� ����
		root->right = NULL;
		root->data = item;			// root ����� ��
	}
	else if (root->data > item)		// root�� �����ϰ�, �� ���� ���ο� item ������ Ŭ ��
		Insert(root->left, item);	// root�� �������� Insert �Լ� �ٽ� ȣ��
	else if (root->data < item)		// root�� �����ϰ�, �� ���� ���ο� item ������ ���� ��
		Insert(root->right, item);	// root�� ���������� Insert �Լ� �ٽ� ȣ��
	else
		return 0;	//root�� item�� ���� ��
	return 1;
}

// ���� ū ���� ã�� �Լ� 
template<class T>
void GetPredecessor(Node<T> *root, T& item)
{
	while (root->right != NULL)			// root�� �������� ������ ���
		root = root->right;				// root�� ������ ��尪�� root�� ������ �Ѵ�
	item = root->data;					// root ����� ���� item�� �����Ѵ�.
}

// ������� ��带 ã���� ������ Ʈ������ �� ��带 ����� �Լ�
template<class T>
void DeleteNode(Node<T> *&root)
{
	T item;
	Node<T>* tempPtr;			// �ӽ� ��带 �����ϰ� root ��带 �ӽ� ��忡 ����
	tempPtr = root;

	if (root->left == NULL)				// ���ʳ�尡 ���� ��
	{
		root = root->right;				// ������ ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else if (root->right == NULL)		// �����ʳ�尡 ���� ��
	{
		root = root->left;				// ���� ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else
	{
		GetPredecessor(root->left, item);	// �߰��� �ִ� ��带 ����� ���� �� (left, right, child ��� ���� ���)
		root->data = item;					// ������� ��庸�� ���� ���� �߿� ���� ū ��带 ã��
		Delete(root->left, item);			// �� ���� ���� ��忡 ���縦 �ؼ� ���� ��ó�� ������
	}
}

// ���� ������� �ϴ� ��带 ã�� recursive �Լ�
template<class T>
int Delete(Node<T> *&root, T item)
{
	if (root == NULL)
		return 0;
	else if (item < root->data)				// root��尪���� item��尡 ���� ��
	{
		if (!Delete(root->left, item))		// ���ʳ��� ���� delete�Լ� ȣ��
			return 0;
	}
	else if (item > root->data)			// root��尪���� item��尡 Ŭ ��
	{
		if (!Delete(root->right, item))		// �����ʳ��� ���� delete�Լ� ȣ��
			return 0;
	}
	else
		DeleteNode(root);				// ã���� �ϴ� ���� ��ġ�ϴ� ��� deletenode �Լ� ȣ��
	return 1;
}

// Tree���� node�� �˻��ϴ� �Լ�
template<class T>
void Retrieve(Node<T> *root, T& item, bool &found)
{
	if (root == NULL)						// root�� NULL�� ��� found�� false 
		found = false;
	else if (item < root->data)				// ã���� �ϴ� �����۰��� root������ ���� �� 
		Retrieve(root->left, item, found);	// ���� ���� ���� retrieve �Լ� ȣ��
	else if (item > root->data)				// ã���� �ϴ� �����۰��� root������ Ŭ ��
		Retrieve(root->right, item, found);	// ������ ���� ���� retrieve �Լ� ȣ��
	else
	{										// ã���� �ϴ� ���� ��ġ�� ��
		item = root->data;					// item�� ��� ������ ����
		found = true;						// found���� true�� �ؼ� ã�� ������ ����
	}
}

// InOrder ������� ����ϴ� �Լ� 
template<class T>
void PrintInOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(root->left, out);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		out << "\t" << root->data;					// root ���
		PrintInOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// PreOrder ������� ����ϴ� �Լ�
template<class T>
void PrintPreOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		out << "\t" << root->data;					// root�� ���� ���
		PrintPreOrderTraversal(root->left, out);	// root�� �������� ���� PreOrder �Լ� �ٽ� ȣ��
		PrintPreOrderTraversal(root->right, out);	// root�� ���������� ���� PreOrder �Լ� �ٽ� ȣ��
	}
}

// PostOrder ������� ����ϴ� �Լ�
template<class T>
void PrintPostOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintPostOrderTraversal(root->left, out);	// root�� �������� ���� �ٽ� PostOrder �Լ� ȣ��
		PrintPostOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� PostOrder �Լ� ȣ��
		out << "\t" << root->data;					// root�� �� ���
	}
}

template<class T>
void GetDataPointer(Node<T> *root, T& item, T*& pointer)
{
	if (root == NULL)						// root�� NULL�� ��� found�� false 
		pointer = NULL;
	else if (item < root->data)				// ã���� �ϴ� �����۰��� root������ ���� �� 
		GetDataPointer(root->left, item, pointer);	// ���� ���� ���� retrieve �Լ� ȣ��
	else if (item > root->data)				// ã���� �ϴ� �����۰��� root������ Ŭ ��
		GetDataPointer(root->right, item, pointer);	// ������ ���� ���� retrieve �Լ� ȣ��
	else									// ã���� �ϴ� ���� ��ġ�� ��
		pointer = &(root->data);			// pointer�� data�� �ּҰ� ����
}

template<class T>
void AccessInOrder(Node<T>* root, T** DataList, int& num)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		AccessInOrder(root->left, DataList, num);	// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		DataList[num++] = &root->data;					// data ����
		AccessInOrder(root->right, DataList, num);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}