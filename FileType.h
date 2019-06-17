#ifndef _FILETYPE_H
#define _FILETYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;



/**
*	file information class.
*/
class FileType
{
public:
	/**
	*	default constructor.
	*/
	FileType()
	{
		fPath = "";
		fName = "";
		fCreatTime = "";
	}

	// ���������
	FileType(string name)
	{
		fName = name;
		fPath = "";
		fCreatTime = "";
	}

	/**
	*	destructor.
	*/
	~FileType()
	{
		
	}

	/**
	*	@brief	fName�� ����
	*	@detail	�Ķ���ͷ� ���� name�� fName���� ����
	*	@pre	none.
	*	@post	fName���� ������
	*	@param	name	fName���� ������ ��
	*/
	void SetName(string name);

	/**
	*	@brief	Ű����κ��� name�� �Է¹���
	*	@detail	Ű����κ��� name�� �Է¹ް� fName�� ����
	*	@pre	none.
	*	@post	fName���� ������
	*/
	void SetNameFromKB();

	/**
	*	@brief	fPath�� ����
	*	@detail	�Ķ���ͷ� ���� path�� fPath���� ����
	*	@pre	none.
	*	@post	fPath���� ������
	*	@param	path	fPath�� ������ ��
	*/
	void SetPath(string path);

	/**
	*	@brief	Ű����κ��� path�� �Է¹���
	*	@detail	Ű����κ��� path�� �Է¹ް� fPath�� ����
	*	@pre	none.
	*	@post	fPath���� ������
	*/
	void SetPathFromKB();

	/**
	*	@brief	fName�� return
	*	@detail	fName�� return
	*	@pre	fName�� �����Ǿ�����
	*	@post	none.
	*	@return	fName
	*/
	string GetName() const;

	/**
	*	@brief	fPath�� return
	*	@detail	fPath�� return
	*	@pre	fPath�� �����Ǿ�����
	*	@post	none.
	*	@return	fPath
	*/
	string GetPath();

	/**
	*	@brief	fCreatTime�� return
	*	@detail	fCreatTime�� return
	*	@pre	fCreatTime�� �����Ǿ�����
	*	@post	none.
	*	@return	fCreatTime
	*/
	string GetfdCreatTime();


	/**
	*	@brief	Ű����κ��� ��ü ������ �Է¹���
	*	@detail	Ű����κ��� name, path�� �Է¹���
	*	@pre	none.
	*	@post	name, path�� ������
	*/
	void SetRecordFromKB();


	/**
	*	@brief	txt���� ����
	*	@detail	���� �̸�.txt������ ����
	*	@pre	none.
	*	@post	none.
	*	@return	���� ������ �����ϸ� return 1, �ƴϸ� return 0
	*/
	int CreateFile();

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
	*	@pre	�� �Լ��� �����ϴ� ���� � ������ ����������
	*	@post	none.
	*	@param	data	keyword�� ������ �ִ� FileType ��ü
	*	@return	�̸��� keyword�� ������ return 1, �ƴϸ� return 0
	*/
	int SearchKeyword(const FileType& data);


	//���������
	FileType(FileType& data);

	//���Կ�����
	FileType& operator= (const FileType& data);

	//�񱳿�����
	bool operator == (const FileType& item) const;

	bool operator > (const FileType& item) const;

	bool operator < (const FileType& item) const;

	friend ostream& operator << (ostream& os, const FileType& file);

	/**
	*	@brief	������ ������� �ð��� Set
	*	@detail	������ ������� �ð��� string Ÿ������ fCreatTime�� ����
	*	@pre	none.
	*	@post	none.
	*/
	void GenCreateTime();


	/**
	*	@brief	������ ������ ���
	*	@detail	������ �̸�, ��ġ, �����ð��� ȭ�鿡 ���
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	txt������ ���� ���� �ۼ�
	*	@detail	txt������ ���� ������ �ۼ��ϸ� file close �Է� �� ���� ����
	*	@pre	none.
	*	@post	txt���� ������ ������Ʈ��
	*	@return	���� ���⿡ �����ϸ� return 1, �ƴϸ� return 0
	*/
	int OpenThis();

private:
	string fPath;
	string fName;
	string fCreatTime;
};
#endif