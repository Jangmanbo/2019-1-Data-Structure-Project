#pragma once
#include "FolderType.h"

/**
*	VisitList class
*/

struct Visit {
	FolderType* ptr;
	int visit;
};

struct VisitList {

	/**
	*	default constructor.
	*/
	VisitList() {
		this->m_Length = 0;
	}

	/*
	*	@brief	��� ������ ����Ʈ�� ����
	*	@detail	�ش� ������ �̹� ������ visit�� 1 ����
	*	@pre	������ �̵��ؾ���
	*	@post	����Ʈ�� ������Ʈ(������ �߰��ϰų� visit�� 1 �����ϰų�)
	*/
	void visit(FolderType* ptr) {
		bool check = false;
		int i;


		// ����Ʈ�� ����� ��
		if (m_Length == 0) {
			m_arr[m_Length].ptr = ptr;
			m_arr[m_Length].visit = 1;
			m_Length++;

			return;
		}

		// m_arr Ž��
		for (i = 0; i < m_Length; i++)
		{
			if (m_arr[i].ptr == ptr) {
				check = true;
				m_arr[i].visit++;
				break;
			}
		}

		// ���� ���
		if (check) {
			for (; i > 0; i--) {
				if (m_arr[i - 1].visit < m_arr[i].visit) {
					Visit temp = m_arr[i - 1];
					m_arr[i - 1] = m_arr[i];
					m_arr[i] = temp;
				}
				else {
					break;
				}
			}
		}
		else {
			m_arr[m_Length].ptr = ptr;
			m_arr[m_Length].visit = 1;
			m_Length++;
		}
	}

	Visit m_arr[1024];
	int m_Length;
};