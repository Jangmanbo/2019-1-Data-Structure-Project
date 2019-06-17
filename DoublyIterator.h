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
*	���Ḯ��Ʈ���� ���̴� Iterator�� Ŭ����.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	����Ʈ ������.
	*/
	DoublyIterator(const DoublySortedLinkedList<T> &list) : m_List(list), m_pCurPointer(list.m_pFirst)
	{}; ///< DoublySortedLinkedList�� ģ�� Ŭ����.

	/**
	*	@brief	���� �����Ͱ� NULL���� �Ǵ�
	*	@detail	m_pCurPointer�� NULL���� �Ǵ�
	*	@pre	none.
	*	@post	none.
	*	@return	���� �����Ͱ� NULL�� �ƴϸ� return 1, ������ return 0
	*/
	bool NotNull();

	/**
	*	@brief	���� �����Ͱ� NULL���� �Ǵ�
	*	@detail	���� �����Ͱ� ����Ű�� �������� ���� �����Ͱ� NULL���� �Ǵ�
	*	@pre	none.
	*	@post	none.
	*	@return	���� �������� ���� �����Ͱ� NULL�� �ƴϸ� return 1, ������ return 0
	*/
	bool NextNotNull();

	/**
	*	@brief	����Ʈ�� ó�� �����͸� ��ȯ
	*	@pre	none.
	*	@post	none.
	*	@return	����Ʈ�� ���� ó�� ������
	*/
	T First();

	/**
	*	@brief	����Ʈ�� ���� �����͸� ��ȯ
	*	@pre	none.
	*	@post	�����Ͱ� ���� �����͸� ����Ŵ
	*	@return	���� ����Ű�� �������� ���� ������
	*/
	T Next();

	/**
	*	@brief	iterator �ʱ�ȭ
	*	@pre	none.
	*	@post	iterator �ʱ�ȭ
	*/
	void Reset();

	/**
	*	@brief	���� ����Ű�� ������ ��ȯ
	*	@pre	none.
	*	@post	none.
	*	@return	���� ����Ű�� ������
	*/
	DoublyNodeType<T> GetCurrentNode();
private:
	const DoublySortedLinkedList<T> &m_List;
	DoublyNodeType<T>* m_pCurPointer;
};

// ���� �����Ͱ� NULL���� �Ǵ�
template <typename T>
bool DoublyIterator<T> ::NotNull()
{
	if (m_pCurPointer == NULL)
		return false;
	else
		return true;
}


// ���� �����Ͱ� NULL���� �Ǵ�
template <typename T>
bool DoublyIterator<T> ::NextNotNull()
{
	if (m_pCurPointer->next == NULL)
		return false;
	else
		return true;
}

// ����Ʈ�� ó�� �����͸� ��ȯ
template <typename T>
T DoublyIterator<T> ::First()
{
	return m_List.m_pFirst->data;
}


// ����Ʈ�� ���� �����͸� ��ȯ
template <typename T>
T DoublyIterator<T> ::Next()
{
	m_pCurPointer = m_pCurPointer->next;
	return m_pCurPointer->data;
}

// iterator �ʱ�ȭ
template <typename T>
void DoublyIterator<T>::Reset()
{
	m_pCurPointer = m_List.m_pFirst;
}

// ���� ����Ű�� ������ ��ȯ
template <typename T>
DoublyNodeType<T> DoublyIterator<T> ::GetCurrentNode()
{
	return *m_pCurPointer;
}

#endif _DOUBLYITERATOR_H