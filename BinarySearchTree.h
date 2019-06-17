#pragma once
#include <iostream>
#include <string>

using namespace std;

// Tree를 구성하는 Node (node data, left 포인터, right 포인터)
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
	// 생성자
	BinarySearchTree();

	// 소멸자
	~BinarySearchTree();

	// 복사생성자
	BinarySearchTree(BinarySearchTree<T>& Tree);

	// 대입연산자
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& Tree);

	/**
	*	@brief	Tree가 Empty인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 비어있으면 true리턴, 아니면 false 리턴
	*/
	bool IsEmpty()const;

	/**
	*	@brief	Tree가 Full인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 Full이면 true 리턴, 아니면 false 리턴
	*/
	bool IsFull()const;

	/**
	*	@brief	Tree를 비운다
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree에 node가 몇 개인지 확인함
	*	@pre	none
	*	@post	none
	*	@return	Tree의 node 개수를 리턴
	*/
	int GetLength() const;

	/**
	*	@brief	Tree에 새 node를 추가한다
	*	@pre	ItemType의 객체를 생성
	*	@post	Tree에 새 node가 추가됨
	*	@return	새 node 추가에 성공하면 return 1, 아니면 return 0
	*/
	int Add(T& item);

	/**
	*	@brief	Tree에서 지우고자 하는 node를 찾고 지움
	*	@pre	ItemType의 객체를 생성
	*	@post	Tree에서 입력한 node가 삭제됨
	*	@return	node 삭제에 성공하면 return 1, 아니면 return 0
	*/
	int DeleteItem(T item);

	/**
	*	@brief	입력한 값의 node를 Tree에서 검색함
	*	@pre	찾고자 하는 item과 검색결과에 대한 found 설정
	*	@post	node가 Tree에 있는지 검색결과를 알려줌
	*/
	void RetrieveItem(T& item, bool &found)const;

	/**
	*	@brief	Tree의 node를 스크린에 출력한다.
	*	@pre	none
	*	@post	스크린에 Tree가 InOrder, PreOrder, PostOrder 방법으로 각각 출력됨.
	*/
	void PrintTree(ostream &out)const;

	/**
	*	@brief	data의 name과 name이 같은 T데이터가 있으면 포인터 주소 반환
	*	@pre	none.
	*	@post	none.
	*	@param	data	반환하고자 하는 데이터의 name을 가짐
	*	@return	data의 name과 데이터의 name이 같으면 해당 데이터의 포인터 주소 반환, 같은 name을 가진 데이터가 없으면 NULL 반환
	*/
	T* GetPointer(T& data);

	/**
	*	@brief	DataList에 node의 data의 주소값을 담음
	*	@pre	none.
	*	@post	none.
	*	@param	DataList	node의 data의 주소값을 담을 배열
	*/
	void StoreData(T** DataList);

private:
	Node<T>* root;		// Node 타입의 root
};

// 생성자
template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}

// 소멸자
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

// Tree가 비어있는지 확인
template<class T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root == NULL)			// root 노드가 NULL인 경우 true 리턴
		return true;
	else
		return false;			// root 노드가 NULL이 아닌 경우 false 리턴
}



// Tree가 Full인지 확인
template<class T>
bool BinarySearchTree<T>::IsFull()const
{
	Node* room;					// 임시의 node를 만들고
	try
	{
		room = new Node;		// 새 노드를 추가할 수 있는지 확인
		delete room;			// 임시로 만든 room 노드를 지움
		return false;			// isFull에 대한 false 리턴
	}
	catch (std::bad_alloc exception)		// 더 이상 아이템 추가를 할 수 없고 Full일 경우
	{
		return true;					// isFull에 대한 true 리턴
	}
}

// Tree를 비움
template<class T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(root);				// Tree 초기화 함수 호출
}

// Tree의 node개수를 알려줌
template<class T>
int BinarySearchTree<T>::GetLength()const
{
	return CountNodes(root);			// node 개수를 새는 함수 호출
}

// Tree에 새로운 node 추가
template<class T>
int BinarySearchTree<T>::Add(T& item)
{
	return Insert(root, item);	// 새 node 추가하는 함수 호출
}

// Tree의 node를 지움
template<class T>
int BinarySearchTree<T>::DeleteItem(T item)
{
	return Delete(root, item);					// 존재하는 node 삭제하는 함수를 호출
}

// Tree에서 찾고자 하는 값의 node를 검색
template<class T>
void BinarySearchTree<T>::RetrieveItem(T& item, bool &found)const
{
	Retrieve(root, item, found);		// Tree 검색 함수 호출
}

// Tree의 node를 각각의 방법대로 출력함
template<class T>
void BinarySearchTree<T>::PrintTree(ostream &out)const
{
	cout << "\t[InOrder]" << endl;
	PrintInOrderTraversal(root, out);			// InOrder 방법으로 출력

	cout << endl << "\t[PreOrder]" << endl;
	PrintPreOrderTraversal(root, out);			// PreOrder 방법으로 출력

	cout << endl << "\t[PostOrder]" << endl;
	PrintPostOrderTraversal(root, out);			// PostOrder 방법으로 출력
}

// data의 name과 name이 같은 T데이터가 있으면 포인터 주소 반환
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
// Tree를 초기화하는 함수
template<class T>
void MakeEmptyTree(Node<T>*& root)
{
	if (root != NULL)								// root가 존재하는 경우
	{
		MakeEmptyTree(root->left);	// root의 왼쪽으로 가서 다시 MakeEmptyTree 함수 호출
		MakeEmptyTree(root->right);	// root의 오른쪽으로 가서 다시 MakeEmptyTree 함수 호출
		delete root;
	}
}

// Tree의 node 개수를 세는 함수
template<class T>
int CountNodes(Node<T>* root)
{
	if (root == NULL)		// root 노드가 null일경우 0을 리턴
		return 0;
	else
		return CountNodes(root->left) + CountNodes(root->right) + 1;		// 노드의 왼쪽, 오른쪽에 대한 재귀적 호출과 root에 해당하는 1을 더해서 값을 리턴
}

// BinarySearchTree에 새로운 노드 추가
template<class T>
int Insert(Node<T>*& root, T& item)
{
	if (root == NULL)				// root가 null일 경우 
	{
		root = new Node<T>;	// root 노드 생성
		root->left = NULL;			// root 노드이므로 left와 right는 NULL로 설정
		root->right = NULL;
		root->data = item;			// root 노드의 값
	}
	else if (root->data > item)		// root가 존재하고, 그 값이 새로운 item 값보다 클 때
		Insert(root->left, item);	// root의 왼쪽으로 Insert 함수 다시 호출
	else if (root->data < item)		// root가 존재하고, 그 값이 새로운 item 값보다 작을 때
		Insert(root->right, item);	// root의 오른쪽으로 Insert 함수 다시 호출
	else
		return 0;	//root와 item이 같을 때
	return 1;
}

// 가장 큰 값을 찾는 함수 
template<class T>
void GetPredecessor(Node<T> *root, T& item)
{
	while (root->right != NULL)			// root의 오른쪽이 존재할 경우
		root = root->right;				// root의 오른쪽 노드값이 root에 오도록 한다
	item = root->data;					// root 노드의 값을 item에 복사한다.
}

// 지우려는 노드를 찾으면 실제로 트리에서 그 노드를 지우는 함수
template<class T>
void DeleteNode(Node<T> *&root)
{
	T item;
	Node<T>* tempPtr;			// 임시 노드를 생성하고 root 노드를 임시 노드에 복사
	tempPtr = root;

	if (root->left == NULL)				// 왼쪽노드가 없을 때
	{
		root = root->right;				// 오른쪽 노드가 root가 되도록 복사하고 임시노드를 지움
		delete tempPtr;
	}
	else if (root->right == NULL)		// 오른쪽노드가 없을 때
	{
		root = root->left;				// 왼쪽 노드가 root가 되도록 복사하고 임시노드를 지움
		delete tempPtr;
	}
	else
	{
		GetPredecessor(root->left, item);	// 중간에 있는 노드를 지우고 싶을 때 (left, right, child 노드 있을 경우)
		root->data = item;					// 지우려는 노드보다 작은 노드들 중에 가장 큰 노드를 찾음
		Delete(root->left, item);			// 그 값을 지울 노드에 복사를 해서 지운 것처럼 눈속임
	}
}

// 내가 지우려고 하는 노드를 찾는 recursive 함수
template<class T>
int Delete(Node<T> *&root, T item)
{
	if (root == NULL)
		return 0;
	else if (item < root->data)				// root노드값보다 item노드가 작을 때
	{
		if (!Delete(root->left, item))		// 왼쪽노드로 가서 delete함수 호출
			return 0;
	}
	else if (item > root->data)			// root노드값보다 item노드가 클 때
	{
		if (!Delete(root->right, item))		// 오른쪽노드로 가서 delete함수 호출
			return 0;
	}
	else
		DeleteNode(root);				// 찾고자 하는 값이 일치하는 경우 deletenode 함수 호출
	return 1;
}

// Tree에서 node를 검색하는 함수
template<class T>
void Retrieve(Node<T> *root, T& item, bool &found)
{
	if (root == NULL)						// root가 NULL인 경우 found는 false 
		found = false;
	else if (item < root->data)				// 찾고자 하는 아이템값이 root값보다 작을 때 
		Retrieve(root->left, item, found);	// 왼쪽 노드로 가서 retrieve 함수 호출
	else if (item > root->data)				// 찾고자 하는 아이템값이 root값보다 클 때
		Retrieve(root->right, item, found);	// 오른쪽 노드로 가서 retrieve 함수 호출
	else
	{										// 찾고자 하는 값과 일치할 때
		item = root->data;					// item에 노드 정보를 복사
		found = true;						// found값을 true로 해서 찾는 과정을 멈춤
	}
}

// InOrder 방법으로 출력하는 함수 
template<class T>
void PrintInOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root가 존재하는 경우
	{
		PrintInOrderTraversal(root->left, out);		// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		out << "\t" << root->data;					// root 출력
		PrintInOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
	}
}

// PreOrder 방법으로 출력하는 함수
template<class T>
void PrintPreOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root가 존재하는 경우
	{
		out << "\t" << root->data;					// root를 먼저 출력
		PrintPreOrderTraversal(root->left, out);	// root의 왼쪽으로 가서 PreOrder 함수 다시 호출
		PrintPreOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 PreOrder 함수 다시 호출
	}
}

// PostOrder 방법으로 출력하는 함수
template<class T>
void PrintPostOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root가 존재하는 경우
	{
		PrintPostOrderTraversal(root->left, out);	// root의 왼쪽으로 가서 다시 PostOrder 함수 호출
		PrintPostOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 다시 PostOrder 함수 호출
		out << "\t" << root->data;					// root의 값 출력
	}
}

template<class T>
void GetDataPointer(Node<T> *root, T& item, T*& pointer)
{
	if (root == NULL)						// root가 NULL인 경우 found는 false 
		pointer = NULL;
	else if (item < root->data)				// 찾고자 하는 아이템값이 root값보다 작을 때 
		GetDataPointer(root->left, item, pointer);	// 왼쪽 노드로 가서 retrieve 함수 호출
	else if (item > root->data)				// 찾고자 하는 아이템값이 root값보다 클 때
		GetDataPointer(root->right, item, pointer);	// 오른쪽 노드로 가서 retrieve 함수 호출
	else									// 찾고자 하는 값과 일치할 때
		pointer = &(root->data);			// pointer에 data의 주소값 대입
}

template<class T>
void AccessInOrder(Node<T>* root, T** DataList, int& num)
{
	if (root != NULL)								// root가 존재하는 경우
	{
		AccessInOrder(root->left, DataList, num);	// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		DataList[num++] = &root->data;					// data 복사
		AccessInOrder(root->right, DataList, num);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
	}
}