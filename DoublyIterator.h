#pragma once
#ifndef _DOUBLYITERATOR_H
#define _DOUBLYITERATOR_H

#include "DoublySortedLinkedList.h"
#include <iostream>
#include <fstream>	
#include <string>
using namespace std;


template<typename T>
struct DoublyNodeType;

template<typename T>
class DoublySortedLinkedList;

/**
*	연결리스트에서 쓰이는 Iterator의 클래스.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyIterator(const DoublySortedLinkedList<T> &list) : m_List(list), m_pCurPointer(list.m_pFirst)
	{}; ///< DoublySortedLinkedList와 친구 클래스.

	/**
	*	@brief	현재 포인터가 NULL인지 판단
	*	@detail	m_pCurPointer가 NULL인지 판단
	*	@pre	none.
	*	@post	none.
	*	@return	현재 포인터가 NULL이 아니면 return 1, 맞으면 return 0
	*/
	bool NotNull();

	/**
	*	@brief	다음 데이터가 NULL인지 판단
	*	@detail	현재 포인터가 가리키는 데이터의 다음 데이터가 NULL인지 판단
	*	@pre	none.
	*	@post	none.
	*	@return	현재 포인터의 다음 데이터가 NULL이 아니면 return 1, 맞으면 return 0
	*/
	bool NextNotNull();

	/**
	*	@brief	리스트의 처음 데이터를 반환
	*	@pre	none.
	*	@post	none.
	*	@return	리스트의 제일 처음 데이터
	*/
	T First();

	/**
	*	@brief	리스트의 다음 데이터를 반환
	*	@pre	none.
	*	@post	포인터가 다음 데이터를 가리킴
	*	@return	현재 가리키는 데이터의 다음 데이터
	*/
	T Next();

	/**
	*	@brief	iterator 초기화
	*	@pre	none.
	*	@post	iterator 초기화
	*/
	void Reset();

	/**
	*	@brief	현재 가리키는 데이터 반환
	*	@pre	none.
	*	@post	none.
	*	@return	현재 가리키는 데이터
	*/
	DoublyNodeType<T> GetCurrentNode();
private:
	const DoublySortedLinkedList<T> &m_List;
	DoublyNodeType<T>* m_pCurPointer;
};

// 현재 포인터가 NULL인지 판단
template <typename T>
bool DoublyIterator<T> ::NotNull()
{
	if (m_pCurPointer == NULL)
		return false;
	else
		return true;
}


// 다음 데이터가 NULL인지 판단
template <typename T>
bool DoublyIterator<T> ::NextNotNull()
{
	if (m_pCurPointer->next == NULL)
		return false;
	else
		return true;
}

// 리스트의 처음 데이터를 반환
template <typename T>
T DoublyIterator<T> ::First()
{
	return m_List.m_pFirst->data;
}


// 리스트의 다음 데이터를 반환
template <typename T>
T DoublyIterator<T> ::Next()
{
	m_pCurPointer = m_pCurPointer->next;
	return m_pCurPointer->data;
}

// iterator 초기화
template <typename T>
void DoublyIterator<T>::Reset()
{
	m_pCurPointer = m_List.m_pFirst;
}

// 현재 가리키는 데이터 반환
template <typename T>
DoublyNodeType<T> DoublyIterator<T> ::GetCurrentNode()
{
	return *m_pCurPointer;
}

#endif _DOUBLYITERATOR_H