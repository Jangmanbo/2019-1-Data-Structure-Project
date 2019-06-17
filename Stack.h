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
	V* data;				///< 각 노드의 데이터.
	StackNodeType *prev;	///< 노드의 앞을 가리키는 포인터.
	StackNodeType *next;	///< 노드의 다음를 가리키는 포인터.
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
	*	@brief	현재 노드의 데이터 반환
	*	@pre	none.
	*	@post	none.
	*	@return	m_pCurPointer->data
	*/
	V* GetStackPointer();

	/**
	*	@brief	stack에 data 저장
	*	@detail	현재 노드의 다음에 data 저장
	*	@pre	none.
	*	@post	data 추가, m_pCurPointer가 새로 생긴 노드로 이동
	*	@param	data	저장할 데이터
	*	@return	1
	*/
	int Push(V* data);

	/**
	*	@brief	이전 노드로 이동
	*	@detail	만일 이전 노드가 없다면 이동하지 않음
	*	@pre	이전 노드가 있어야 함
	*	@post	m_pCurPointer가 이전 노드를 가리킴
	*	@return	이동에 성공하면 return 1, 아니면 return 0
	*/
	int Pop();

	/**
	*	@brief	다음 노드로 이동
	*	@detail	다음 노드가 없다면 이동하지 않음
	*	@pre	현재 노드의 다음 노드가 있어야 함
	*	@post	m_pCurPointer가 다음 노드를 가리킴
	*	@return	이동에 성공하면 return 1, 아니면 return 0
	*/
	int DepthIncrease();

private:
	StackNodeType<V>* m_pCurPointer;	///<현재 노드를 가리키는 포인터
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

// 현재 노드의 데이터 반환
template <class V>
V* Stack<V>::GetStackPointer()
{
	return m_pCurPointer->data;
}

// stack에 data 저장
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

// 이전 노드로 이동
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

// 다음 노드로 이동
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