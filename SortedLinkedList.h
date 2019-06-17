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


	//���������
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

	// ���� ������
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
	*	@brief	list�� ����ִ��� Ȯ��.
	*	@detail	list�� ����ִ��� Ȯ��.
	*	@pre	none.
	*	@post	none.
	*	@return	list�� ��������� return 1, �ƴϸ� return 0.
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
	*	@brief	item�� ��ġ�ϴ� name�� ���� �����͸� ����.
	*	@pre	�ش��ϴ� name�� ���� �����Ͱ� �־����
	*	@post	�ش� �����Ͱ� ���ŵ�.
	*	@return	�����Ͱ� ���ŵǸ� return 1, �ƴϸ� return 0
	*/
	int Delete(T item);

	/**
	*	@brief	item�� ��ġ�ϴ� name�� ���� �����͸� ����.
	*	@pre	�ش��ϴ� name�� ���� �����Ͱ� �־����
	*	@post	�ش� �����Ͱ� item�� �������� ���ŵ�.
	*	@param	itme	�����ϰ��� �ϴ� ������
	*	@return	�����Ͱ� ���ŵǸ� return 1, �ƴϸ� return 0
	*/
	int Replace(T item);

	/**
	*	@brief	item�� ��ġ�ϴ� name�� ���� �������� ������ ���ġ
	*	@pre	�������� name�� ����Ǿ���
	*	@post	�ش� �������� ������ �ٽ� ������
	*	@param	item	������ �ٲ� ������
	*	@return	�ش� �����͸� ã�� ������ �ٽ� �����־����� return 1, �ƴϸ� return 0
	*/
	int ChangeSequence(T item);

	/**
	*	@brief	��� �������� �̸��� ���
	*	@detail	��� �������� �̸��� ����ϸ� �����Ͱ� ������ �����Ͱ� �������� ������ �˷���
	*	@pre	iterator �ʱ�ȭ
	*	@post	none.
	*/
	void DisplayAllName();

	/**
	*	@brief	fdata�� name�� �������� name�� ������ �Ǵ�
	*	@detail	fdata�� name�� �������� name�� ������ �Ǵ��Ͽ� ������ ������ �ּ� ��ȯ
	*	@pre	iterator �ʱ�ȭ
	*	@post	none.
	*	@param	fdata	��ȯ�ϰ��� �ϴ� �������� name�� ����
	*	@return	fdata�� name�� �������� name�� ������ �ش� �������� ������ �ּ� ��ȯ, ���� name�� ���� �����Ͱ� ������ NULL ��ȯ
	*/
	T* GetPointer(T& fdata);

	/**
	*	@brief	���� ������ ������ ��ȯ
	*	@detail	fdata�� name�� �������� name�� ������ �Ǵ��Ͽ� ������ ������ �ּ� ��ȯ
	*	@pre	iterator�� ���ϴ� ��ġ�� ����
	*	@post	none.
	*	@return	���� ������ ��ȯ, ���ڶ��� ���޽� NULL ��ȯ
	*/
	T* GetNextPointer();

	/**
	*	@brief	keyword�� ���� ������ ���� ���
	*	@detail	keyword�� ���� �����͸� ��� ã�� ���� ���, ������ keyword�� ���� �����Ͱ� ���ٰ� �˷���
	*	@pre	iterator �ʱ�ȭ
	*	@post	none.
	*	@param	data	ã���� �ϴ� �������� keyword�� ����
	*	@return	keyword�� ���� �����͸� �ϳ��� ã���� return 1, �ƴϸ� return 0
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
	//����Ʈ���� ��� node ����
	MakeEmpty();
}


// list�� ����ִ��� Ȯ��
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
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
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
	// ����Ʈ �ʱ�ȭ
	ResetList();

	// ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	T dummy;
	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = NULL;

	// list �� node �� �������� �ʴ� ���
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list �� primary key�� ��ġ�ϴ� �����Ͱ� ���� ���
	else if (Get(item)==1)
	{
		return 0;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else
	{
		// ���� ������ node �� �̵� �� ����
		while (1)
		{
			// ���� ��带 ����Ű�� ������ ����
			pre = m_pCurPointer;

			// iteration �� �̿��� node ������ ����.
			GetNextItem(dummy);

			if (node->data<dummy)  //���� node�� �����Ͱ� �� �۾����� ����; �� ������ �´� ����
			{
				if (pre == NULL)	//��ó������ ���� ���ߵǴ� ���, node�� data���� ���� ������
				{
					node->next = m_pCurPointer;
					m_pList = node;		//��ó������ �ٲ�;
					break;
				}
				else		//�߰��� ���� ���� ����
				{
					pre->next = node;
					node->next = m_pCurPointer;
					break;
				}
			}


			// node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
			if (m_pCurPointer->next == NULL)
			{
				// ������ node �� ���ο� node ����
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
	// current pointer �ʱ�ȭ
	if (m_pCurPointer != NULL)
		m_pCurPointer = NULL;
	
}


// Gets the next element in list.
template <typename T>
void SortedLinkedList<T>::GetNextItem(T& item)
{
	// current pointer �� NULL�̶�� ó�� node�� ����Ŵ.
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
	}
	else
		//current position �� ���� ���� �̵�
		m_pCurPointer = m_pCurPointer->next;

	//item �� current position �� info �� ����
	if (m_pCurPointer==NULL)
		item = NULL;
	else
		item = m_pCurPointer->data;
}

// item�� ��ġ�ϴ� name�� ���� �����͸� ����.
template <typename T>
int SortedLinkedList<T>::Delete(T item)
{
	NodeType<T> *pre;
	NodeType<T> *toDel;
	ResetList();
	T tmp;
	bool found = false;

	if (Get(item) == 0)	//�ش��ϴ� ���� ������, 0������ ����
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)		//id���� ��ġ
		{
			if (pre == NULL) //�����ؾ��� ��尡 ��ó���϶�
			{
				toDel = m_pList;	//��� �Űܵΰ� ����
				m_pList = m_pList->next;	//��ó���� �ι�°�ιٲ�
				delete toDel;
				found = true;
				break;
			}
			else
			{
				toDel = m_pCurPointer;
				pre->next = m_pCurPointer->next;	//�� �����Ϳ� ���������͸� ����
				delete toDel;
				found = true;
				break;
			}
		}
		if (m_pCurPointer->next == NULL)	//�Ǹ�����, ������ �ٵ�������
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

// item�� ��ġ�ϴ� name�� ���� �����͸� ����.
template <typename T>
int SortedLinkedList<T>::Replace(T item)
{
	NodeType<T> *pre;
	ResetList();
	T isthere = item;
	T tmp;
	bool found = false;
	//Get(T& item)�� pass by reference������ �����Ϳְ�߻�
	if (Get(isthere) == 0)	//�ش��ϴ� ���� ������, 0������ ����
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)			//'=='�����ڸ� id���� ���� �����ε�����. 	
		{
			m_pCurPointer->data = item;	//id���� ������ �����͸� ��ü
			found = true;
			break;
		}
		if (m_pCurPointer->next == NULL)	//�Ǹ�����
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

// item�� ��ġ�ϴ� name�� ���� �������� ������ ���ġ
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

	if (Get(item) == 0)	//�ش��ϴ� ���� ������, 0������ ����
		return 0;

	while (1)
	{
		pre = m_pCurPointer;
		GetNextItem(tmp);
		if (tmp==item)		//id���� ��ġ
		{
			if (pre == NULL) //�����ؾ��� ��尡 ��ó���϶�
			{
				toDel = m_pList;	//��� �Űܵΰ� ����
				m_pList = m_pList->next;	//��ó���� �ι�°�ιٲ�
				found = true;
				break;
			}
			else
			{
				toDel = m_pCurPointer;
				pre->next = m_pCurPointer->next;	//�� �����Ϳ� ���������͸� ����
				found = true;
				break;
			}
		}
		if (m_pCurPointer->next == NULL)	//�Ǹ�����, ������ �ٵ�������
			break;


	}
	if (found)
	{
		// ����Ʈ �ʱ�ȭ
		ResetList();

		T dummy;
		// todel ��ü�� next�� �ʱ�ȭ
		toDel->next = NULL;

		// list �� node�� �������� �ʴ� ���
		if (!m_nLength)
		{
			m_pList = toDel;
		}
		// list �� node �� �ϳ� �̻� �����ϴ� ���
		else
		{
			// ���� ������ node �� �̵� �� ����
			while (1)
			{
				// ���� ��带 ����Ű�� ������ ����
				pre = m_pCurPointer;

				// iteration �� �̿��� node ������ ����.
				GetNextItem(dummy);

				if (toDel->data<dummy)  //���� node�� �����Ͱ� �� �۾����� ����; �� ������ �´� ����
				{
					if (pre == NULL)	//��ó������ ���� ���ߵǴ� ���, node�� data���� ���� ������
					{
						toDel->next = m_pCurPointer;
						m_pList = toDel;		//��ó������ �ٲ�;
						break;
					}
					else		//�߰��� ���� ���� ����
					{
						pre->next = toDel;
						toDel->next = m_pCurPointer;
						break;
					}
				}


				// node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
				if (m_pCurPointer->next == NULL)
				{
					// ������ node �� ���ο� node ����
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


//����Ʈ�� �̸��� ���
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

//data�� name�� ���� ������ name�� ������ �Ǵ�
template <class T>
T* SortedLinkedList<T>::GetPointer(T& fdata)
{
	ResetList();	//iterator �ʱ�ȭ
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
			return &(m_pCurPointer->data);//�����͸� ����
		}
		else if (one>fdata)
		{
			return NULL;	//����(0)�� ����
		}
	} while (m_pCurPointer->next!=NULL);
	
	return NULL;
}

// ���� ������ ������ ��ȯ
template <class T>
T* SortedLinkedList<T>::GetNextPointer()
{
	if (m_pCurPointer==NULL)
		m_pCurPointer = m_pList;
	else
		m_pCurPointer = m_pCurPointer->next;

	return &m_pCurPointer->data;
}


//keyword�� ���� ���� ���� ���
template <class T>
int SortedLinkedList<T>::PrintKeywordData(T& data)
{

	ResetList();	//iterator �ʱ�ȭ
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