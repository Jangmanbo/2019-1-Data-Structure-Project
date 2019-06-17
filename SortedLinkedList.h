#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

/**
*	Structure for NodeType to use in Linked structure.
*/
template <typename T>
struct NodeType
{
	T data;	///< A data for each node.
	NodeType* next;	///< A node pointer to point succeed node.
};


/**
*	Simple sorted list class for managing items.
*/
template <typename T>
class SortedLinkedList
{
public:
	/**
	*	default constructor.
	*/
	SortedLinkedList();

	/**
	*	destructor.
	*/
	~SortedLinkedList();


	//복사생성자
	SortedLinkedList(SortedLinkedList<T>& item)
	{
		m_nLength = item.m_nLength;
		item.ResetList();

		if (item.m_nLength==0)
		{
			m_pList = NULL;
			m_pCurPointer = NULL;
		}
		else
		{
			T folder;
			item.GetNextItem(folder);

			m_pList = new NodeType<T>;
			m_pList->data = folder;
			m_pList->next = NULL;

			NodeType<T>* pre;
			pre = m_pList;

			while (1)
			{
				if (item.m_pCurPointer->next==NULL)
				{
					break;
				}
				else
				{
					item.GetNextItem(folder);
					NodeType<T>* node = new NodeType<T>;
					node->data = folder;
					node->next = NULL;
					pre->next = node;
					pre = pre->next;
				}
			}
		}
	}

	// 대입 연산자
	SortedLinkedList<T>& operator=(SortedLinkedList<T>& item)
	{
		m_nLength = item.m_nLength;
		item.ResetList();

		if (item.m_nLength == 0)
		{
			m_pList = NULL;
			m_pCurPointer = NULL;
		}
		else
		{
			T folder;
			item.GetNextItem(folder);

			m_pList = new NodeType<T>;
			m_pList->data = folder;
			m_pList->next = NULL;

			NodeType<T>* pre;
			pre = m_pList;

			while (1)
			{
				if (m_pCurPointer->next == NULL)
				{
					break;
				}
				else
				{
					item.GetNextItem(folder);
					NodeType<T>* node = new NodeType<T>;
					node->data = folder;
					node->next = NULL;
					pre->next = node;
					pre = pre->next;
				}
			}
		}
		return (*this);
	}

	/**
	*	@brief	list가 비어있는지 확인.
	*	@detail	list가 비어있는지 확인.
	*	@pre	none.
	*	@post	none.
	*	@return	list가 비어있으면 return 1, 아니면 return 0.
	*/
	bool IsEmpty();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	void GetNextItem(T& item);

	/**
	*	@brief	item과 일치하는 name을 가진 데이터를 제거.
	*	@pre	해당하는 name을 가진 데이터가 있어야함
	*	@post	해당 데이터가 제거됨.
	*	@return	데이터가 제거되면 return 1, 아니면 return 0
	*/
	int Delete(T item);

	/**
	*	@brief	item과 일치하는 name을 가진 데이터를 갱신.
	*	@pre	해당하는 name을 가진 데이터가 있어야함
	*	@post	해당 데이터가 item의 내용으로 갱신됨.
	*	@param	itme	갱신하고자 하는 데이터
	*	@return	데이터가 갱신되면 return 1, 아니면 return 0
	*/
	int Replace(T item);

	/**
	*	@brief	item과 일치하는 name을 가진 데이터의 순서를 재배치
	*	@pre	데이터의 name이 변경되었음
	*	@post	해당 데이터의 순서를 다시 정해줌
	*	@param	item	순서를 바꿀 데이터
	*	@return	해당 데이터를 찾아 순서를 다시 정해주었으면 return 1, 아니면 return 0
	*/
	int ChangeSequence(T item);

	/**
	*	@brief	모든 데이터의 이름을 출력
	*	@detail	모든 데이터의 이름을 출력하며 데이터가 없으면 데이터가 존재하지 않음을 알려줌
	*	@pre	iterator 초기화
	*	@post	none.
	*/
	void DisplayAllName();

	/**
	*	@brief	fdata의 name과 데이터의 name이 같은지 판단
	*	@detail	fdata의 name과 데이터의 name이 같은지 판단하여 같으면 포인터 주소 반환
	*	@pre	iterator 초기화
	*	@post	none.
	*	@param	fdata	반환하고자 하는 데이터의 name을 가짐
	*	@return	fdata의 name과 데이터의 name이 같으면 해당 데이터의 포인터 주소 반환, 같은 name을 가진 데이터가 없으면 NULL 반환
	*/
	T* GetPointer(T& fdata);

	/**
	*	@brief	다음 데이터 포인터 반환
	*	@detail	fdata의 name과 데이터의 name이 같은지 판단하여 같으면 포인터 주소 반환
	*	@pre	iterator가 원하는 위치에 있음
	*	@post	none.
	*	@return	다음 포인터 반환, 끝자락에 도달시 NULL 반환
	*/
	T* GetNextPointer();

	/**
	*	@brief	keyword를 가진 데이터 정보 출력
	*	@detail	keyword를 가진 데이터를 모두 찾아 정보 출력, 없으면 keyword를 가진 데이터가 없다고 알려줌
	*	@pre	iterator 초기화
	*	@post	none.
	*	@param	data	찾고자 하는 데이터의 keyword을 가짐
	*	@return	keyword를 가진 데이터를 하나라도 찾으면 return 1, 아니면 return 0
	*/
	int PrintKeywordData(T& data);

private:
	NodeType<T>* m_pList;	///< Pointer for pointing a first node.
	NodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
	int m_nLength;	///< Number of node in the list.
};


// Class constructor
template <typename T>
SortedLinkedList<T>::SortedLinkedList()
{
	m_nLength = 0;
	m_pList = NULL;
	m_pCurPointer = NULL;
}


// Class destructor
template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	//리스트내의 모든 node 제거
	MakeEmpty();
}


// list가 비어있는지 확인
template <class T>
bool SortedLinkedList<T>::IsEmpty()
{
	if (m_nLength == 0)
		return 1;
	else
		return 0;
}

// Initialize list to empty state.
template <typename T>
void SortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T>* tempPtr;

	while (m_pList != NULL)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}

	m_nLength = 0;
}


// Get number of elements in the list.
template <typename T>
int SortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}


// Add item into this list.
template <typename T>
int SortedLinkedList<T>::Add(T item)
{
	// 리스트 초기화
	ResetList();

	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	T dummy;
	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;

	// list 에 node 가 존재하지 않는 경우
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list 에 primary key가 일치하는 데이터가 있을 경우
	else if (Get(item)==1)
	{
		return 0;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = m_pCurPointer;

			// iteration 을 이용해 node 포인터 갱신.
			GetNextItem(dummy);

			if (node->data<dummy)  //값이 node의 데이터가 더 작아지는 순간; 즉 순서에 맞는 순간
			{
				if (pre == NULL)	//맨처음으로 값이 들어가야되는 경우, node의 data값이 가장 작을때
				{
					node->next = m_pCurPointer;
					m_pList = node;		//맨처음으로 바꿈;
					break;
				}
				else		//중간에 값이 들어가는 순간
				{
					pre->next = node;
					node->next = m_pCurPointer;
					break;
				}
			}


			// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
			if (m_pCurPointer->next == NULL)
			{
				// 마지막 node 와 새로운 node 연결
				m_pCurPointer->next = node;
				break;
			}
		}
	}

	m_nLength++;

	return 1;
}


// Retrieve list element whose key matches item's key (if present).
template <typename T>
int SortedLinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;

	location = m_pList;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (item==location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}


// Initializes current pointer for an iteration through the list.
template <typename T>
void SortedLinkedList<T>::ResetList()
{
	// current pointer 초기화
	if (m_pCurPointer != NULL)
		m_pCurPointer = NULL;
	
}


// Gets the next element in list.
template <typename T>
void SortedLinkedList<T>::GetNextItem(T& item)
{
	// current pointer 이 NULL이라면 처음 node를 가리킴.
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
	}
	else
		//current position 을 다음 노드로 이동
		m_pCurPointer = m_pCurPointer->next;

	//item 에 current position 의 info 를 삽입
	if (m_pCurPointer==NULL)
		item = NULL;
	else
		item = m_pCurPointer->data;
}

// item과 일치하는 name을 가진 데이터를 제거.
template <typename T>
int SortedLinkedList<T>::Delete(T item)
{
	NodeType<T> *pre;
	NodeType<T> *toDel;
	ResetList();
	T tmp;
	bool found = false;

	if (Get(item) == 0)	//해당하는 값이 없으면, 0보내고 종료
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)		//id값이 일치
		{
			if (pre == NULL) //삭제해야할 노드가 맨처음일때
			{
				toDel = m_pList;	//잠시 옮겨두고 삭제
				m_pList = m_pList->next;	//맨처음을 두번째로바꿈
				delete toDel;
				found = true;
				break;
			}
			else
			{
				toDel = m_pCurPointer;
				pre->next = m_pCurPointer->next;	//전 포인터와 다음포인터를 연결
				delete toDel;
				found = true;
				break;
			}
		}
		if (m_pCurPointer->next == NULL)	//맨마지막, 루프를 다돌았을때
			break;


	}
	if (found)
	{
		m_nLength--;
		return 1;
	}
	else
		return 0;

}

// item과 일치하는 name을 가진 데이터를 갱신.
template <typename T>
int SortedLinkedList<T>::Replace(T item)
{
	NodeType<T> *pre;
	ResetList();
	T isthere = item;
	T tmp;
	bool found = false;
	//Get(T& item)이 pass by reference임으로 데이터왜곡발생
	if (Get(isthere) == 0)	//해당하는 값이 없으면, 0보내고 종료
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)			//'=='연산자를 id값에 대해 오버로딩했음. 	
		{
			m_pCurPointer->data = item;	//id값이 같으면 데이터를 대체
			found = true;
			break;
		}
		if (m_pCurPointer->next == NULL)	//맨마지막
		{
			found = true;
			break;
		}

	}
	if (found)
		return 1;
	else
		return 0;

}

// item과 일치하는 name을 가진 데이터의 순서를 재배치
template <class T>
int SortedLinkedList<T>::ChangeSequence(T item)
{
	if (m_nLength==1)
	{
		return 1;
	}
	NodeType<T> *pre;
	NodeType<T> *toDel;
	ResetList();
	T tmp;
	bool found = false;

	if (Get(item) == 0)	//해당하는 값이 없으면, 0보내고 종료
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)		//id값이 일치
		{
			if (pre == NULL) //삭제해야할 노드가 맨처음일때
			{
				toDel = m_pList;	//잠시 옮겨두고 삭제
				m_pList = m_pList->next;	//맨처음을 두번째로바꿈
				found = true;
				break;
			}
			else
			{
				toDel = m_pCurPointer;
				pre->next = m_pCurPointer->next;	//전 포인터와 다음포인터를 연결
				found = true;
				break;
			}
		}
		if (m_pCurPointer->next == NULL)	//맨마지막, 루프를 다돌았을때
			break;


	}
	if (found)
	{
		// 리스트 초기화
		ResetList();

		T dummy;
		// todel 객체의 next값 초기화
		toDel->next = NULL;

		// list 에 node가 존재하지 않는 경우
		if (!m_nLength)
		{
			m_pList = toDel;
		}
		// list 에 node 가 하나 이상 존재하는 경우
		else
		{
			// 가장 마지막 node 로 이동 후 삽입
			while (1)
			{
				// 이전 노드를 가리키는 포인터 갱신
				pre = m_pCurPointer;

				// iteration 을 이용해 node 포인터 갱신.
				GetNextItem(dummy);

				if (toDel->data<dummy)  //값이 node의 데이터가 더 작아지는 순간; 즉 순서에 맞는 순간
				{
					if (pre == NULL)	//맨처음으로 값이 들어가야되는 경우, node의 data값이 가장 작을때
					{
						toDel->next = m_pCurPointer;
						m_pList = toDel;		//맨처음으로 바꿈;
						break;
					}
					else		//중간에 값이 들어가는 순간
					{
						pre->next = toDel;
						toDel->next = m_pCurPointer;
						break;
					}
				}


				// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
				if (m_pCurPointer->next == NULL)
				{
					// 마지막 node 와 새로운 node 연결
					m_pCurPointer->next = toDel;
					break;
				}
			}
		}
		return 1;
	}
	else
		return 0;
}


//리스트의 이름을 출력
template <class T>
void SortedLinkedList<T>::DisplayAllName()
{
	if (m_nLength == 0)
	{
		cout << "\tData doesn't exist." << endl;
	}
	else
	{
		ResetList();
		T folder;
		GetNextItem(folder);

		int i = 0;
		while (1)
		{
			cout << "\t" << i + 1 << ". " << folder << endl;
			if (m_pCurPointer->next==NULL)
			{
				break;
			}
			else
			{
				GetNextItem(folder);
				i++;
			}
		}
	}
}

//data의 name과 서브 폴더의 name이 같은지 판단
template <class T>
T* SortedLinkedList<T>::GetPointer(T& fdata)
{
	ResetList();	//iterator 초기화
	T one;

	if (m_nLength==0)
	{
		return NULL;
	}

	do
	{
		GetNextItem(one);
		if (one==fdata)
		{
			return &(m_pCurPointer->data);//포인터를 리턴
		}
		else if (one>fdata)
		{
			return NULL;	//실패(0)을 리턴
		}
	} while (m_pCurPointer->next!=NULL);
	
	return NULL;
}

// 다음 데이터 포인터 반환
template <class T>
T* SortedLinkedList<T>::GetNextPointer()
{
	if (m_pCurPointer==NULL)
		m_pCurPointer = m_pList;
	else
		m_pCurPointer = m_pCurPointer->next;

	return &m_pCurPointer->data;
}


//keyword를 가진 폴더 정보 출력
template <class T>
int SortedLinkedList<T>::PrintKeywordData(T& data)
{

	ResetList();	//iterator 초기화
	T dummy;
	bool exist = false;

	if (m_nLength==0)
	{
		cout<< "\tThere is no folder to search to." <<endl;
		return 0;
	}

	while (1)
	{
		GetNextItem(dummy);
		if (dummy.SearchKeyword(data))
		{
			dummy.DisplayRecordOnScreen();
			cout << endl;
			exist = true;
		}
		if (m_pCurPointer->next == NULL)
		{
			cout << endl;
			break;
		}
	}
	if (!exist)
	{
		return 0;
	}
	return 1;
}

#endif	// LINKED_LIST