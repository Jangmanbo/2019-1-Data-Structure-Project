#pragma once

#include <iostream>
#include <string>

using namespace std;


/**
*	Structure for StackNodeType to use in Linked structure.
*/
template <typename V>
struct StackNodeType
{
	V* data;				///< �� ����� ������.
	StackNodeType *prev;	///< ����� ���� ����Ű�� ������.
	StackNodeType *next;	///< ����� ������ ����Ű�� ������.
};


/**
*	Stack class transformed into DoublyLinkedList.
*/
template <class V>
class Stack
{
public:
	/**
	*	default constructor.
	*/
	Stack();

	/**
	*	destructor.
	*/
	~Stack();

	/**
	*	@brief	���� ����� ������ ��ȯ
	*	@pre	none.
	*	@post	none.
	*	@return	m_pCurPointer->data
	*/
	V* GetStackPointer();

	/**
	*	@brief	stack�� data ����
	*	@detail	���� ����� ������ data ����
	*	@pre	none.
	*	@post	data �߰�, m_pCurPointer�� ���� ���� ���� �̵�
	*	@param	data	������ ������
	*	@return	1
	*/
	int Push(V* data);

	/**
	*	@brief	���� ���� �̵�
	*	@detail	���� ���� ��尡 ���ٸ� �̵����� ����
	*	@pre	���� ��尡 �־�� ��
	*	@post	m_pCurPointer�� ���� ��带 ����Ŵ
	*	@return	�̵��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int Pop();

	/**
	*	@brief	���� ���� �̵�
	*	@detail	���� ��尡 ���ٸ� �̵����� ����
	*	@pre	���� ����� ���� ��尡 �־�� ��
	*	@post	m_pCurPointer�� ���� ��带 ����Ŵ
	*	@return	�̵��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int DepthIncrease();

private:
	StackNodeType<V>* m_pCurPointer;	///<���� ��带 ����Ű�� ������
};

// default constructor.
template <class V>
Stack<V>::Stack()
{
	m_pCurPointer = NULL;
}

// destructor
template <class V>
Stack<V>::~Stack()
{
	StackNodeType<V>* node;
	while (m_pCurPointer != NULL)
	{
		node = m_pCurPointer;
		m_pCurPointer = m_pCurPointer->next;
		delete node;
	}
}

// ���� ����� ������ ��ȯ
template <class V>
V* Stack<V>::GetStackPointer()
{
	return m_pCurPointer->data;
}

// stack�� data ����
template <class V>
int Stack<V>::Push(V* data)
{
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = new StackNodeType<V>;
		m_pCurPointer->data = data;
		m_pCurPointer->next = NULL;
		m_pCurPointer->prev = NULL;
		return 1;
	}
	else
	{
		StackNodeType<V>* temp = new StackNodeType<V>;
		temp->data = data;
		temp->prev = m_pCurPointer;
		temp->next = NULL;
		if (m_pCurPointer->next != NULL)
		{
			StackNodeType<V>* NextNode = m_pCurPointer->next;
			StackNodeType<V>* CurNode;
			while (NextNode != NULL)
			{
				CurNode = NextNode;
				NextNode = NextNode->next;
				delete CurNode;
			}
		}
		m_pCurPointer->next = temp;

		m_pCurPointer = m_pCurPointer->next;

		return 1;
	}
}

// ���� ���� �̵�
template <class V>
int Stack<V>::Pop()
{
	if (m_pCurPointer->prev == NULL)
	{
		return 0;
	}
	else
	{
		m_pCurPointer = m_pCurPointer->prev;
		return 1;
	}
}

// ���� ���� �̵�
template <class V>
int Stack<V>::DepthIncrease()
{
	if (m_pCurPointer->next != NULL)
	{
		m_pCurPointer = m_pCurPointer->next;
		return 1;
	}
	else
	{
		return 0;
	}
}