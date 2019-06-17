#ifndef _FOLDERTYPE_H
#define _FOLDERTYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#include "BinarySearchTree.h"
#include "DoublySortedLinkedList.h"
#include "FileType.h"
#include "Stack.h"

using namespace std;



/**
*	folder information class.
*/
class FolderType
{
public:
	/**
	*	default constructor.
	*/
	FolderType() 
	{
		fdSubFolderNum = 0;
		FileNum = 0;
		fdPath = "";
		fdName = "";
		fdCreatTime = "";
		FolderTree = NULL;
		FileTree = NULL;
	}

	FolderType(string name)
	{
		fdName = name;
		fdSubFolderNum = 0;
		FileNum = 0;
		fdPath = "";
		fdCreatTime = "";
		FolderTree = NULL;
		FileTree = NULL;
	}


	/**
	*	destructor.
	*/
	~FolderType() 
	{
		if (FolderTree != NULL)
			delete FolderTree;
		if (FileTree != NULL)
			delete FileTree;
	}

	/**
	*	@brief	fdName�� ����
	*	@detail	�Ķ���ͷ� ���� name�� fdName���� ����
	*	@pre	none.
	*	@post	fdName���� ������
	*	@param	name	fdName���� ������ ��
	*/
	void SetName(string name);

	/**
	*	@brief	Ű����κ��� name�� �Է¹���
	*	@detail	Ű����κ��� name�� �Է¹ް� fdName�� ����
	*	@pre	none.
	*	@post	fdName���� ������
	*/
	void SetNameFromKB();

	/**
	*	@brief	fdPath�� ����
	*	@detail	�Ķ���ͷ� ���� path�� fdPath���� ����
	*	@pre	none.
	*	@post	fdPath���� ������
	*	@param	path	fdPath�� ������ ��
	*/
	void SetPath(string path);

	/**
	*	@brief	Ű����κ��� path�� �Է¹���
	*	@detail	Ű����κ��� path�� �Է¹ް� fdPath�� ����
	*	@pre	none.
	*	@post	fdPath���� ������
	*/
	void SetPathFromKB();

	/**
	*	@brief	fdName�� return
	*	@detail	fdName�� return
	*	@pre	fdName�� �����Ǿ�����
	*	@post	none.
	*	@return	fdName
	*/
	string GetName() const;

	/**
	*	@brief	fdPath�� return
	*	@detail	fdPath�� return
	*	@pre	fdPath�� �����Ǿ�����
	*	@post	none.
	*	@return	fdPath
	*/
	string GetPath();

	/**
	*	@brief	fdCreatTime�� return
	*	@detail	fdCreatTime�� return
	*	@pre	fdCreatTime�� �����Ǿ�����
	*	@post	none.
	*	@return	fdCreatTime
	*/
	string GetfdCreatTime();

	/**
	*	@brief	fdSubFolderNum�� return
	*	@detail	fdSubFolderNum�� return
	*	@pre	fdSubFolderNum�� �����Ǿ�����
	*	@post	none.
	*	@return	fdSubFolderNum
	*/
	int GetSubFolderNum();

	/**
	*	@brief	FileNum�� return
	*	@detail	FileNum�� return
	*	@pre	FileNum�� �����Ǿ�����
	*	@post	none.
	*	@return	FileNum
	*/
	int GetFileNum();

	/**
	*	@brief	visit�� return
	*	@detail	visit�� return
	*	@pre	visit�� �����Ǿ�����
	*	@post	none.
	*	@return	visit
	*/
	int GetVisit();

	/**
	*	@brief	visit 1 ����
	*	@detail	visit 1 ����
	*	@pre	visit�� �����Ǿ�����
	*	@post	none.
	*/
	void IncreaseVisit();

	/**
	*	@brief	Ű����κ��� ��ü ������ �Է¹���
	*	@detail	Ű����κ��� name, path�� �Է¹���
	*	@pre	none.
	*	@post	name, path�� ������
	*/
	void SetRecordFromKB();

	/**
	*	@brief	���� �̸��� ���
	*	@detail	ȭ�鿡 ���� �̸��� ���
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayName();

	/**
	*	@brief	�̸��� keyword�� �ִ��� Ȯ��
	*	@detail	�̸��� keyword�� �ִ��� �˷���
	*	@pre	�� �Լ��� �����ϴ� ������ � ������ ����������
	*	@post	none.
	*	@param	data	keyword�� ������ �ִ� FolderType ��ü
	*	@return	�̸��� keyword�� ������ return 1, �ƴϸ� return 0
	*/
	int SearchKeyword(const FolderType& data);


	//���������
	FolderType(FolderType& data);

	//���Կ�����
	FolderType& operator= (const FolderType& data);

	//�񱳿�����
	bool operator ==(const FolderType& item) const;

	bool operator > (const FolderType& item) const;

	bool operator < (const FolderType& item) const;

	friend ostream& operator << (ostream& os, const FolderType& folder);

	/**
	*	@brief	������ ������� �ð��� Set
	*	@detail	������ ������� �ð��� string Ÿ������ fdCreatTime�� ����
	*	@pre	none.
	*	@post	none.
	*/
	void GenCreateTime();

	/**
	*	@brief	������ ������ Ű����κ��� �о ��������Ʈ�� �߰�
	*	@detail ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�, ������ �̸��� ���� ������ ������ �߰�X 
	*	@pre	������������Ʈ ���̰� MAXSIZE �̸��̾�� ��
	*	@post	���� ����Ʈ�� ������ �߰��ǰ� fdFolderNum�� 1����
	*	@return	���� �߰��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int AddFolder();

	/**
	*	@brief	data�� �ִ� ������ ������ �о ��������Ʈ�� �߰�
	*	@detail ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�, ������ �̸��� ���� ������ ������ �߰�X
	*	@pre	none.
	*	@post	���� ����Ʈ�� ������ �߰��ǰ� fdFolderNum�� 1����
	*	@param	data	�߰��� ���� FolderType��ü
	*	@return	���� �߰��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int AddFolder(FolderType& data);
	
	/**
	*	@brief	������ ������ Ű����κ��� �о ���ϸ���Ʈ�� �߰�
	*	@detail ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�, ������ �̸��� ���� ������ ������ �߰�X
	*	@pre	none.
	*	@post	���� ����Ʈ�� ������ �߰��ǰ� FileNum�� 1����
	*	@return	���� �߰��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int AddFile();

	/**
	*	@brief	data�� �ִ� �� ���� ������ �о ���ϸ���Ʈ�� �߰�
	*	@detail ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�, ������ �̸��� ���� ������ ������ �߰�X
	*	@pre	none.
	*	@post	���� ����Ʈ�� ������ �߰��ǰ� FileNum�� 1����
	*	@return	���� �߰��� �����ϸ� return 1, �ƴϸ� return 0
	*/
	int AddFile(FileType& data);

	/**
	*	@brief	������ ���� ������ �޾� �ش� ������ ã�Ƽ� ����
	*	@detail ������ ���� �̸��� �Ķ���ͷ� �ް� �ش� ������ ������ ����
	*	@pre	���� ������ 1�� �̻�
	*	@post	������ �����ǰ�, ���� �� ���� ������ 0���� fdFolderList=NULL;
	*	@return	���� ������ �����ϸ� return 1, �ƴϸ� return 0
	*/
	int DeleteFolder(FolderType folder);

	/**
	*	@brief	������ ���� ������ �޾� �ش� ������ ã�Ƽ� ����
	*	@detail ������ ���� �̸��� �Ķ���ͷ� �ް� �ش� ������ ������ ����
	*	@pre	������ 1�� �̻�
	*	@post	������ �����ǰ�, ���� �� ������ 0���� FileList=NULL;
	*	@param	file	�����ϰ��� �ϴ� ������ �̸��� �����Ǿ��ִ� FileType��ü
	*	@return	���� ������ �����ϸ� return 1, �ƴϸ� return 0
	*/
	int DeleteFile(FileType file);

	/**
	*	@brief	������ ������ ���
	*	@detail	������ �̸�, ��ġ, �����ð��� ȭ�鿡 ���
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecordOnScreen();


	/**
	*	@brief	�˻��� ���������� �޾� �˻��Ͽ� �ش� ������ ����
	*	@detail	keyword�� ���� ������ searchFolderResult�� ����
	*	@pre	none.
	*	@post	none.
	*	@param	keyword	�˻��� keyword
	*/
	void RetrieveFolderByKeyword(string keyword, DoublySortedLinkedList<FolderType>* FolderResult);

	/**
	*	@brief	�˻��� ���������� �޾� �˻��Ͽ� �ش� ������ ����
	*	@detail	keyword�� ���� ������ searchFileResult�� ����
	*	@pre	none.
	*	@post	none.
	*	@param	keyword	�˻��� keyword
	*/
	void RetrieveFileByKeyword(string keyword, DoublySortedLinkedList<FileType>* FileResult);

	/**
	*	@brief	��� ���������� �̸��� ���
	*	@detail	���������� ������ ���� ���������� ������ �˸�, ������ ��� ���� ������ �̸��� ���
	*	@pre	���������� 1�� �̻� �־����
	*	@post	none.
	*/
	void DisplayAllFolderName();

	/**
	*	@brief	��� ������ �̸��� ���
	*	@detail	������ ������ ���� ���������� ������ �˸�, ������ ��� ������ �̸��� ���
	*	@pre	���� 1�� �̻� �־����
	*	@post	none.
	*/
	void DisplayAllFileName();

	/**
	*	@brief	fdFolderList�� GetPointer�Լ� ����
	*	@detail	fdFolderList�� GetPointer�Լ� �����ϰ� �Լ��� ���ϰ��� ����
	*	@pre	none.
	*	@post	data�� ������ �ּҰ��� ��
	*	@param	data	�����͸� ��ȯ�� ������ �̸��� ���� FolderType ��ü
	*	@return	fdFolderList�� GetPointer�� ���ϰ��� ����
	*/
	FolderType* GetFolderPointer(FolderType& data);

	/**
	*	@brief	FileList�� GetPointer�Լ� ����
	*	@detail	FileList�� GetPointer�Լ� �����ϰ� �Լ��� ���ϰ��� ����
	*	@pre	none.
	*	@post	data�� ������ �ּҰ��� ��
	*	@param	data	�����͸� ��ȯ�� ������ �̸��� ���� FileType ��ü
	*	@return	FileList�� GetPointer�� ���ϰ��� ����
	*/
	FileType* GetFilePointer(FileType& data);


	/**
	*	@brief	��� ���� ������ ��θ� �ٽ� ����
	*	@detail	��� ���� ������ ��ΰ� ���� ������ �ٲ� �̸��� �ݿ��Ͽ� �ٲ�
	*	@pre	������ �̸��� �ٲ�
	*	@post	���� ������ ��� �缳��
	*	@param	path	�� ������ ���
	*/
	void ChangeUnderPath(string path);

private:
	int fdSubFolderNum;
	int FileNum;
	string fdPath;
	string fdName;
	string fdCreatTime;
	BinarySearchTree<FolderType>* FolderTree;
	BinarySearchTree<FileType>* FileTree;
	int visit;
};
#endif