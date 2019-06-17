#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

/**
*	queue information class.
*/
template <class V>
class Queue
{
public:

	/**
	*	default constructor.
	*/
	Queue()
	{
		queue = new V[SIZE];
		front = 0;
		rear = 0;
	}

	/**
	*	destructor.
	*/
	~Queue()
	{
		delete[] queue;
	}


	/**
	*	@brief	queue�� data ����
	*	@detail	queue�� data ����, ť�� �������� ���� ó�� ���Դ� ������ ������ �� ����
	*	@pre	none.
	*	@post	rear�� 1 ������
	*	@param	data	queue�� ���� FolderType ��ü
	*	@return	return 1
	*/
	int Enqueue(V data);

	/**
	*	@brief	���� ó�� ���� ������ ����
	*	@detail	ť���� ���� ������ �����͸� ������
	*	@pre	ť�� �� ���־�� ��
	*	@post	front�� 1 ������
	*/
	void Dequeue();

	/**
	*	@brief	rear 1 ����
	*	@detail	rear�� 1 ����, rear�� 10�̸� 0�� ��
	*	@pre	none.
	*	@post	rear�� 1 ������
	*/
	void PlusRear();

	/**
	*	@brief	front 1 ����
	*	@detail	front�� 1 ����, front�� 10�̸� 0�� ��
	*	@pre	none.
	*	@post	front�� 1 ������
	*/
	void PlusFront();

	/**
	*	@brief	ť�� �ִ� �����͵��� name�� ��� ���
	*	@detail	ť�� �ִ� �����͵��� name�� ������ ������ ��� ���
	*	@pre	none.
	*	@post	none.
	*	@return	ť�� �ƹ� �����͵� ������ return 0, ������ return 1
	*/
	int Display();

	/**
	*	@brief	ť�� ���ִ��� Ȯ��
	*	@detail	rear�� front�� �ٷ� �� index���� Ȯ��
	*	@pre	none.
	*	@post	none.
	*	@return	ť�� �������� return 1, �ƴϸ� return 0
	*/
	int IsFull();

private:
	int front;
	int rear;
	V* queue;
};

// queue�� data ����
template <class V>
int Queue<V>::Enqueue(V data)
{
	for (int i = front; i != rear; i = (i + 1) % SIZE)
	{
		if (data==queue[i])
		{
			for (int j = i; j != (rear+9)%10; j = (j + 1) % SIZE)
			{
				queue[j] = queue[(j + 1)%SIZE];
			}
			rear = (rear + 9) % 10;
			queue[rear] = data;
			PlusRear();
			return 1;
		}
	}
	if (IsFull())
	{
		Dequeue();
	}
	queue[rear] = data;
	PlusRear();
	return 1;
}

// ���� ó�� ���� ������ ����
template <class V>
void Queue<V>::Dequeue()
{
	PlusFront();
}

// rear 1 ����
template <class V>
void Queue<V>::PlusRear()
{
	rear = (rear + 1) % SIZE;
}

// front 1 ����
template <class V>
void Queue<V>::PlusFront()
{
	front = (front + 1) % SIZE;
}

// ť�� �ִ� �����͵��� name�� ��� ���
template <class V>
int Queue<V>::Display()
{
	if (rear==front)
	{
		return 0;
	}

	int num = 1;
	for (int i = front; i != rear; i=(i+1)%SIZE)
	{
		cout << "\t" << num << ". " << queue[i] << endl;
		num++;
	}
	return 1;
}

// ť�� ���ִ��� Ȯ��
template <class V>
int Queue<V>::IsFull()
{
	if ((rear+1)%SIZE==front)
	{
		return 1;
	}
	return 0;
}
#endif