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
	*	@brief	queue에 data 삽입
	*	@detail	queue에 data 삽입, 큐가 차있으면 제일 처음 들어왔던 데이터 내보낸 후 삽입
	*	@pre	none.
	*	@post	rear가 1 증가함
	*	@param	data	queue에 넣을 FolderType 객체
	*	@return	return 1
	*/
	int Enqueue(V data);

	/**
	*	@brief	제일 처음 들어온 데이터 삭제
	*	@detail	큐에서 제일 오래된 데이터를 삭제함
	*	@pre	큐가 다 차있어야 함
	*	@post	front가 1 증가함
	*/
	void Dequeue();

	/**
	*	@brief	rear 1 증가
	*	@detail	rear가 1 증가, rear가 10이면 0이 됨
	*	@pre	none.
	*	@post	rear가 1 증가함
	*/
	void PlusRear();

	/**
	*	@brief	front 1 증가
	*	@detail	front가 1 증가, front가 10이면 0이 됨
	*	@pre	none.
	*	@post	front가 1 증가함
	*/
	void PlusFront();

	/**
	*	@brief	큐에 있는 데이터들의 name을 모두 출력
	*	@detail	큐에 있는 데이터들의 name을 오래된 순으로 모두 출력
	*	@pre	none.
	*	@post	none.
	*	@return	큐에 아무 데이터도 없으면 return 0, 있으면 return 1
	*/
	int Display();

	/**
	*	@brief	큐가 차있는지 확인
	*	@detail	rear가 front의 바로 전 index인지 확인
	*	@pre	none.
	*	@post	none.
	*	@return	큐가 차있으면 return 1, 아니면 return 0
	*/
	int IsFull();

private:
	int front;
	int rear;
	V* queue;
};

// queue에 data 삽입
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

// 제일 처음 들어온 데이터 삭제
template <class V>
void Queue<V>::Dequeue()
{
	PlusFront();
}

// rear 1 증가
template <class V>
void Queue<V>::PlusRear()
{
	rear = (rear + 1) % SIZE;
}

// front 1 증가
template <class V>
void Queue<V>::PlusFront()
{
	front = (front + 1) % SIZE;
}

// 큐에 있는 데이터들의 name을 모두 출력
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

// 큐가 차있는지 확인
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