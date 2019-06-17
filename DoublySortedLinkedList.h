#pragma once
#ifndef _DOUBLYSORTEDLINKEDLIST_H
#define _DOUBLYSORTEDLINKEDLIST_H

#include "DoublyIterator.h"
#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

template<typename T>
class DoublyIterator;

/**
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNodeType
{
	T data; ///< �� ����� ������.
	DoublyNodeType *prev; ///< ����� ���� ����Ű�� ������.
	DoublyNodeType *next; ///< ����� ������ ����Ű�� ������.
};

/**
*	���ĵ� �����Ḯ��Ʈ Ŭ����
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>; ///< DoublyIterator�� ģ�� Ŭ����.
public:
	/**
	*	����Ʈ ������.
	*/
	DoublySortedLinkedList();

	/**
	*	�Ҹ���.
	*/
	~DoublySortedLinkedList();

	//���������
	DoublySortedLinkedList(DoublySortedLinkedList<T>& item)
	{
		m_nLength = item.m_nLength;
		DoublyIterator<T> item_itor(item);

		m_pFirst = new DoublyNodeType<T>;
		m_pFirst->data = T(""); // �ּڰ�.
		m_pFirst->prev = NULL; // ó��.

		item_itor.Next();
		DoublyNodeType<T>* pre = m_pFirst;
		DoublyNodeType<T>* node;

		while (item_itor.NextNotNull())
		{
			node = new DoublyNodeType<T>;
			node->data = item_itor.m_pCurPointer->data;
			pre->next = node;
			node->prev = pre;

			item_itor.Next();
		}

		//this�� m_pLast
		node = new DoublyNodeType<T>;
		node->data = item_itor.m_pCurPointer->data;
		pre->next = node;
		node->prev = pre;
		node->next = NULL;
		m_pLast = node;

		m_pCurPointer = m_pFirst;
	}

	//���Կ�����
	DoublySortedLinkedList<T>& operator=(DoublySortedLinkedList<T>& item)
	{
		m_nLength = item.m_nLength;
		DoublyIterator<T> item_itor(*item);

		m_pFirst = new DoublyNodeType<T>;
		m_pFirst->data = T(""); // �ּڰ�.
		m_pFirst->prev = NULL; // ó��.

		item_itor.Next();
		DoublyNodeType<T>* pre = m_pFirst;
		DoublyNodeType<T>* node;

		while (item_itor.NextNotNull())
		{
			node = new DoublyNodeType<T>;
			node->data = item_itor.m_pCurPointer->data;
			pre->next = node;
			node->prev = pre;

			item_itor.Next();
		}

		//this�� m_pLast
		node = new DoublyNodeType<T>;
		node->data = item_itor.m_pCurPointer->data;
		pre->next = node;
		node->prev = pre;
		node->next = NULL;
		m_pLast = node;
		
		m_pCurPointer = m_pFirst;

		return (*this);
	}

	/**
	*	@brief	����Ʈ�� ������� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	������� �ƴ����� �˷��ش�.
	*	@return	��������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsEmpty();

	/**
	*	@brief	����Ʈ�� ���� á���� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	���� á���� �ƴ����� �˷��ش�.
	*	@return	���� �������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsFull();

	/**
	*	@brief	����Ʈ�� ����.
	*	@pre	����.
	*	@post	m_pFirst�� m_pLast�� ������ ��� �����͸� �����.
	*/
	void MakeEmpty();

	/**
	*	@brief	����Ʈ�� ���̸� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	����Ʈ�� ���̸� ��ȯ.
	*	@return	m_nLength ����Ʈ�� ���� ��ȯ.
	*/
	int GetLength() const;

	/**
	*	@brief	���ο� �������� ����Ʈ�� �߰��Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�������� ����Ʈ�� �߰��Ѵ�.
	*	@param	item	�߰��� ������
	*	@return	���� �������� ������ 0�� ��ȯ�ϰ�, �Է¿� �����ϸ� 1�� ��ȯ.
	*/
	int Add(T item);

	/**
	*	@brief	�Է¹��� �������� ����Ʈ���� �����Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�Է¹��� �������� ����Ʈ���� ã�� �����Ѵ�.
	*	@param	item	������ ������
	*	@return	�����ϸ� 1�� ��ȯ�ϰ�, �ش��ϴ� �������� ������ 0�� ��ȯ.
	*/
	int Delete(T item);

	/**
	*	@brief	�Է¹��� ���������� ������ �ٲ۴�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	���ο� ������ ��ü�ȴ�.
	*	@param	item	��ü�� ������ ��� ������
	*/
	void Replace(T item);

	/**
	*	@brief	�Է¹��� �������� ������ ���Ͽ� ���� ����Ʈ�� �������� �����´�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�˻��� �����͸� �����ۿ� �ִ´�.
	*	@param	item	ã�� �����͸� ���� ��ü
	*	@return	��ġ�ϴ� �����͸� ã���� 1, �׷��� ������ 0�� ��ȯ.
	*/
	int Get(T &item);

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
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllName();

	/**
	*	@brief	fdata�� name�� �������� name�� ������ �Ǵ�
	*	@detail	fdata�� name�� �������� name�� ������ �Ǵ��Ͽ� ������ ������ �ּ� ��ȯ
	*	@pre	none.
	*	@post	none.
	*	@param	fdata	��ȯ�ϰ��� �ϴ� �������� name�� ����
	*	@return	fdata�� name�� �������� name�� ������ �ش� �������� ������ �ּ� ��ȯ, ���� name�� ���� �����Ͱ� ������ NULL ��ȯ
	*/
	T* GetPointer(T& fdata);

	/**
	*	@brief	���� ������ ������ ��ȯ
	*	@detail	���� ����Ű�� �������� ���� �����͸� ����Ű�� ������ ��ȯ
	*	@pre	none.
	*	@post	������ ��ġ�� ����
	*	@return	���� ������ ��ȯ, ���ڶ��� ���޽� NULL ��ȯ
	*/
	T* GetNextPointer();

private:
	DoublyNodeType<T>* m_pFirst;		///< �ּҰ��� ������ ����Ʈ�� �� ó��.
	DoublyNodeType<T>* m_pLast;			///< �ִ��� ������ ����Ʈ�� �� ��.
	int m_nLength;						///< ����Ʈ�� ����.
	DoublyNodeType<T>* m_pCurPointer;	///< GetNextPointer()���� �̿�
};

// ����Ʈ�� �� ó���� ���� ���θ� ����Ű�� �����ϰ� ����Ʈ�� ���̸� 0���� �ʱ�ȭ���ѳ��´�.
template <typename T>
DoublySortedLinkedList<T> ::DoublySortedLinkedList()
{
	m_pFirst = new DoublyNodeType<T>;
	m_pLast = new DoublyNodeType<T>;

	m_pFirst->data.SetName(""); // �ּڰ�.
	m_pFirst->next = m_pLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	m_pFirst->prev = NULL; // ó��.

	m_pLast->data.SetName("~"); //  �ִ�.
	m_pLast->next = NULL; // ��.
	m_pLast->prev = m_pFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	m_nLength = 0; // ���̴� 0.

	m_pCurPointer = m_pFirst;
}

// �Ҹ���.
template <typename T>
DoublySortedLinkedList<T>::~DoublySortedLinkedList()
{
	delete m_pFirst;
	delete m_pLast;
}

// ����Ʈ�� ������� �˻��Ѵ�.
template <typename T>
bool DoublySortedLinkedList<T>::IsEmpty()
{
	if (m_nLength == 0)
		return true;
	else
		return false;
}

// ����Ʈ�� �� ���ִ��� �˻��Ѵ�.
template <typename T>
bool DoublySortedLinkedList<T>::IsFull()
{
	if (m_nLength == 10)
		return true;
	else
		return false;
}

// ����Ʈ�� ����.
template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
{
	DoublyNodeType<T> *pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.NextNotNull())
	{
		pItem = itor.m_pCurPointer;
		itor.Next(); // ���� �����͸� �������� �̵�.
		delete pItem;
	}

	m_pFirst->next = m_pLast;
	m_pFirst->prev = NULL;
	m_pLast->prev = m_pFirst;
	m_pLast->next = NULL;
	return;
}

// ����Ʈ�� ���̸� ��ȯ�Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}

// �������� �Է¹޾� ����Ʈ�� �´� �ڸ��� ã�� �����Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::Add(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	if (IsEmpty()) // ó�� ������ ��
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
		pItem->data = item;
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;
		pItem->next = m_pLast;
		m_pLast->prev = pItem; // ó���� �� ���̿� ����.
		m_nLength++;
		return 1;
	}
	else // ó���� �ƴ� ��
	{
		while (1)
		{
			if (item < itor.m_pCurPointer->data) // �´� �ڸ��� ã�´�.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // �������� ����.
				m_nLength++;

				return 1;
			}
			else if (item == itor.m_pCurPointer->data) // ���� ������ �������� ������
				return 0; // 0�� ��ȯ.
			else
				itor.Next(); // �������� �̵�.
		}
	}
}

// �Է¹��� �������� �����Ϳ��� ã�Ƴ��� �����Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::Delete(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item) // ��ġ�ϴ� �����͸� ã�´�.
		{
			DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
			pItem = itor.m_pCurPointer;
			itor.Next();
			pItem->prev->next = itor.m_pCurPointer;
			itor.m_pCurPointer->prev = pItem->prev; // �����ϴ� ����� �հ� �ڸ� ���� �̾��ش�.
			delete pItem; // ����.
			m_nLength--; // ���� ����.
			return 1;
		}
		else
			itor.Next();
	}
	return 0;
}

// �Է¹��� �������� ������ ��ü�Ѵ�.
template <typename T>
void DoublySortedLinkedList<T>::Replace(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item)
		{
			itor.m_pCurPointer->data = item; // ������ ��ü.
			return;
		}
		else
			itor.Next();
	}

	return;
}

// �Է¹��� �����۰� ��ġ�ϴ� �������� ����Ʈ���� ã�� �����´�.
template <typename T>
int DoublySortedLinkedList<T>::Get(T &item)
{
	DoublyIterator<T> itor(*this);
	itor.Next();

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item)
		{
			item = itor.m_pCurPointer->data;
			return 1; // ��ġ�ϸ� 1�� ��ȯ.
		}
		else
			itor.Next(); // �������� �̵�.
	}

	return 0; // ��ġ���� ������ 0�� ��ȯ.
}

// item�� ��ġ�ϴ� name�� ���� �������� ������ ���ġ
template <typename T>
int DoublySortedLinkedList<T>::ChangeSequence(T item)
{
	DoublyIterator<T> itor(*this);
	DoublyNodeType<T> *pItem;
	itor.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item) // ��ġ�ϴ� �����͸� ã�´�.
		{
			pItem = itor.m_pCurPointer;
			itor.Next();
			pItem->prev->next = itor.m_pCurPointer;
			itor.m_pCurPointer->prev = pItem->prev; // �����ϴ� ����� �հ� �ڸ� ���� �̾��ش�.
		}
		else
			itor.Next();
	}


	DoublyIterator<T> itor2(*this);
	itor2.Next(); // �������� �̵�.

	if (IsEmpty()) // ó�� ������ ��
	{
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;
		pItem->next = m_pLast;
		m_pLast->prev = pItem; // ó���� �� ���̿� ����.
		return 1;
	}
	else // ó���� �ƴ� ��
	{
		while (1)
		{
			if (pItem->data < itor2.m_pCurPointer->data) // �´� �ڸ��� ã�´�.
			{
				pItem->prev = itor2.m_pCurPointer->prev;
				pItem->next = itor2.m_pCurPointer;
				itor2.m_pCurPointer->prev->next = pItem;
				itor2.m_pCurPointer->prev = pItem; // �������� ����.
				return 1;
			}
			else if (pItem->data == itor2.m_pCurPointer->data) // ���� ������ �������� ������
				return 0; // 0�� ��ȯ.
			else
				itor2.Next(); // �������� �̵�.
		}
	}
}

// ��� �������� �̸��� ���
template <typename T>
void DoublySortedLinkedList<T>::DisplayAllName()
{
	if (IsEmpty())
	{
		cout << "\tData doesn't exist." << endl;
	}
	else
	{
		DoublyIterator<T> itor(*this);
		itor.Next();
		for (int i = 0; itor.NextNotNull(); i++)
		{
			cout << "\t" << i + 1 << ". " << itor.m_pCurPointer->data << endl;
			itor.Next();
		}
	}
}

// fdata�� name�� �������� name�� ������ �Ǵ��Ͽ� ������ ������ �ּ� ��ȯ
template <typename T>
T* DoublySortedLinkedList<T>::GetPointer(T& fdata)
{
	if (IsEmpty())
	{
		return NULL;
	}

	DoublyIterator<T> itor(*this);

	itor.Next();
	while (itor.NextNotNull())
	{
		if (itor.m_pCurPointer->data == fdata)
		{
			return &(itor.m_pCurPointer->data);
		}
		else if (itor.m_pCurPointer->data > fdata)
		{
			return NULL;
		}
		else
		{
			itor.Next();
		}
	}
	
	return NULL;
}

// ���� ������ ������ ��ȯ
template <typename T>
T* DoublySortedLinkedList<T>::GetNextPointer()
{
	m_pCurPointer = m_pCurPointer->next;
	if (m_pCurPointer!=NULL)
	{
		return &m_pCurPointer->data;
	}
	else
	{
		m_pCurPointer = m_pFirst;
	}
	return NULL;
}

#endif _DOUBLYSORTEDLINKEDLIST_H