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
	*	@brief	열어본 폴더를 리스트에 저장
	*	@detail	해당 폴더가 이미 있으면 visit을 1 증가
	*	@pre	폴더를 이동해야함
	*	@post	리스트가 업데이트(폴더를 추가하거나 visit을 1 증가하거나)
	*/
	void visit(FolderType* ptr) {
		bool check = false;
		int i;


		// 리스트가 비었을 때
		if (m_Length == 0) {
			m_arr[m_Length].ptr = ptr;
			m_arr[m_Length].visit = 1;
			m_Length++;

			return;
		}

		// m_arr 탐색
		for (i = 0; i < m_Length; i++)
		{
			if (m_arr[i].ptr == ptr) {
				check = true;
				m_arr[i].visit++;
				break;
			}
		}

		// 있을 경우
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