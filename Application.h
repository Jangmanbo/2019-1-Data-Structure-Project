#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "FolderType.h"
#include "Queue.h"
#include "Stack.h"
#include "VisitList.h"
#include "SortedLinkedList.h"

#define FILENAMESIZE 1024
#define STACKSIZE 16

struct ClipBoard
{
	FolderType* clipFolder;
	FileType* clipFile;
	FolderType* parentFolder;
	int iscut;	// �߶󳻱�� 1, ����� 0
	int isfile;	// FileType�̸� 1, FolderType�̸� 0
};


/**
*	application class for item management simply.
*/
class Application
{
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		m_RootFolder.SetName("Root");
		m_RootFolder.SetPath("/Root");
		m_RootFolder.GenCreateTime();
		m_CurPointer.Push(&m_RootFolder);
		m_RecentlyFolder.Enqueue(*(m_CurPointer.GetStackPointer()));
		clipboard.clipFolder = NULL;
		clipboard.clipFile = NULL;
		m_Command = 0;
	}
	
	/**
	*	destructor.
	*/
	~Application()	{}

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int NewFolder();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int NewFile();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllItem();


	/**
	*	@brief	���� ���� ������ �ش� keyword�� ���� �����͸� ã�� ����Ѵ�.
	*	@detail	ã�� ������ ������ ��µȴ�.
	*	@pre	none.
	*	@post	none.
	*	@return	������ 1�� ����, ���н� 0�� ����.
	*/
	int RetriveAllByName();

	/**
	*	@brief	����Ʈ���� �ش� name�� ���� folder�� ã�� �����Ѵ�.
	*	@detail	����Ʈ�� �ش� folder�� �����Ѵ�.
	*	@pre	�Է��ϴ� name�� ����Ʈ�� �����ؾ� �Ѵ�.
	*	@post	folder�� ���ŵ�
	*	@return	������ 1�� ����, ���н� 0�� ����.
	*/
	int DeleteFolder();

	/**
	*	@brief	����Ʈ���� �ش� name�� ���� file�� ã�� �����Ѵ�.
	*	@detail	����Ʈ�� �ش� file�� �����Ѵ�.
	*	@pre	�Է��ϴ� name�� ����Ʈ�� �����ؾ� �Ѵ�.
	*	@post	file�� ���ŵ�
	*	@return	������ 1�� ����, ���н� 0�� ����.
	*/
	int DeleteFile();
	
	/**
	*	@brief	�ֱ� ��� ���� ���
	*	@detail	�ֱ� ��� ������ �̸��� ���
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecent();

	/**
	*	@brief	���� ������ �Ӽ��� ���
	*	@detail	���� �̸�, ��ġ, �����ð��� ���
	*	@pre	������ �Ӽ����� ����Ǿ�����
	*	@post	none.
	*/
	void DisplayProperty();

	/**
	*	@brief	���� ������ �̵�
	*	@detail	�̵��� ���� �̸��� �Է¹��� �� �ش� ������ ������ �̵�
	*	@pre	���� ������ �ϳ� �̻� �־�� ��
	*	@post	depth�� 1������ stack[depth]�� �̵��� ���� ��ü ����
	*	@return	���� ������ �̵��ϸ� return 1, �̵����� ���ϸ� return 0
	*/
	int MoveToFolder();

	/**
	*	@brief	�ڷ� ����
	*	@detail	�� ���� ������ ���� ������ �̵�
	*	@pre	���� ������ ���� ������ �־�� ��
	*	@post	stack�� depth�� 1 ������
	*	@return	�ڷ� �̵��ϸ� return 1, �̵����� ���ϸ� return 0
	*/
	int MoveBack();

	/**
	*	@brief	������ ����
	*	@detail	������ ���� ���� ������ �̵�
	*	@pre	������ ���� ������ ����� ��
	*	@post	stack�� depth�� 1 ������
	*	@return	������ �̵��ϸ� return 1, �̵����� ���ϸ� return 0
	*/
	int MoveFront();

	/**
	*	@brief	���� �̸� �ٲٱ�
	*	@detail	���ϴ� ������ fdName �ٲٸ� ���� ����, ������ ��� �缳��
	*	@pre	���� ������ 1�� �̻� �־�� ��
	*	@post	���ϴ� ������ �̸��� �ٲ�
	*	@return	�̸� �ٲٱ� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int ChangeFolderName();
	
	/**
	*	@brief	���� �̸� �ٲٱ�
	*	@detail	���ϴ� ������ fName �ٲٱ�
	*	@pre	������ 1�� �̻� �־�� ��
	*	@post	���ϴ� ������ �̸��� �ٲ�
	*	@return	�̸� �ٲٱ� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int ChangeFileName();

	/**
	*	@brief	���ϴ� ������ ���� ���� �ۼ�
	*	@detail	���⸦ ���ϴ� ���� �̸��� �޾� ������ ���� ���� �ۼ�
	*	@pre	������ 1�� �̻�
	*	@post	txt������ ������ �ۼ���
	*	@return	���� ���⿡ ������ 1�� ����, ���н� 0�� ����.
	*/
	int OpenFile();

	/**
	*	@brief	������ ���� �߶󳻱�
	*	@detail	ClipBoard�� �߶� ������ ����
	*	@pre	������ ���� 1�� �̻�
	*	@post	ClipBoard�� �߶� �����Ͱ� �����
	*	@return	�߶󳻱� ������ 1�� ����, ���н� 0�� ����
	*/
	int Cut();

	/**
	*	@brief	������ ���� ����
	*	@detail	ClipBoard�� ������ ������ ����
	*	@pre	������ ���� 1�� �̻�
	*	@post	ClipBoard�� ������ �����Ͱ� �����
	*	@return	���� ������ 1�� ����, ���н� 0�� ����
	*/
	int Copy();

	/**
	*	@brief	������ ���� �ٿ��ֱ�
	*	@detail	ClipBoard�� ����� �����͸� �ٿ��ֱ�
	*	@pre	ClipBoard�� �����Ͱ� ����Ǿ� �־�� ��
	*	@post	������ ������ �߰�, �߶󳻱��� �����͸� ���� ��� ������ �ִ� �������� ������ ����
	*	@return	�ٿ��ֱ� ������ 1�� ����, ���н� 0�� ����
	*/
	int Paste();

	/*
	*	@brief	���� ��� ���� ����ϱ�
	*	@detail	���� ��� ���� �ִ� 5���� ����Ѵ�.
	*	@pre	FolderType�� ����Ǿ� �־����
	*	@post	none.
	*/
	void PopularFolderPrint();

	/**
	*	@brief	�Է��� ����� ������ �̵�
	*	@pre	none.
	*	@post	�Է��� ��θ� ���� ������ �ִٸ� �̵�, ������ ��ȭ����
	*/
	void MoveToFolderByPath();

	/**
	*	@brief	�ٷΰ��� ��� �� ���ϴ� ������ �̵�
	*	@detail	�ٷΰ��� ����� ������ �� ���ϴ� ������ �ٷ� �̵�
	*	@pre	�ٷΰ��� ��Ͽ� ������ 1�� �̻�
	*	@post	���ϴ� ������ �̵���
	*/
	void MoveToFolderQuickly();

	/**
	*	@brief	���ϴ� ������ �ٷΰ��� ��Ͽ� �߰�
	*	@detail	���� ������ ���� ���� �� ���ϴ� ������ �ٷΰ��� ��Ͽ� �߰�
	*	@pre	���� ������ ���� ������ ����
	*	@post	�Է��� �̸��� ���� ������ ������ �ش� ���� �ٷΰ��� ��Ͽ� �߰�
	*/
	void AddFolderToList();
private:
	ifstream m_InFile;					///< input file descriptor.
	ofstream m_OutFile;					///< output file descriptor.
	FolderType m_RootFolder;			///< Root folder
	Stack<FolderType> m_CurPointer;		///< folder pointer stack
	Queue<FolderType> m_RecentlyFolder;	///< recently folder
	Queue<FileType> m_RecentlyFile;		///< recently file
	ClipBoard clipboard;				///< clipboard
	int m_Command;						///< current command number.
	VisitList m_visit;					///< visit folder list
	SortedLinkedList<FolderType*> fdPointerList;		///< folder pointer list to move quickly.
};

#endif	// _APPLICATION_H