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
	int iscut;	// 잘라내기면 1, 복사면 0
	int isfile;	// FileType이면 1, FolderType이면 0
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
	*	@brief	현재 폴더 내에서 해당 keyword를 가진 데이터를 찾아 출력한다.
	*	@detail	찾은 데이터 정보가 출력된다.
	*	@pre	none.
	*	@post	none.
	*	@return	성공시 1을 리턴, 실패시 0을 리턴.
	*/
	int RetriveAllByName();

	/**
	*	@brief	리스트에서 해당 name을 가진 folder을 찾아 제거한다.
	*	@detail	리스트에 해당 folder을 제거한다.
	*	@pre	입력하는 name이 리스트에 존재해야 한다.
	*	@post	folder가 제거됨
	*	@return	성공시 1을 리턴, 실패시 0을 리턴.
	*/
	int DeleteFolder();

	/**
	*	@brief	리스트에서 해당 name을 가진 file을 찾아 제거한다.
	*	@detail	리스트에 해당 file을 제거한다.
	*	@pre	입력하는 name이 리스트에 존재해야 한다.
	*	@post	file이 제거됨
	*	@return	성공시 1을 리턴, 실패시 0을 리턴.
	*/
	int DeleteFile();
	
	/**
	*	@brief	최근 열어본 폴더 출력
	*	@detail	최근 열어본 폴더의 이름을 출력
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecent();

	/**
	*	@brief	현재 폴더의 속성을 출력
	*	@detail	폴더 이름, 위치, 생성시간을 출력
	*	@pre	폴더의 속성값이 저장되어있음
	*	@post	none.
	*/
	void DisplayProperty();

	/**
	*	@brief	서브 폴더로 이동
	*	@detail	이동할 폴더 이름을 입력받은 후 해당 폴더가 있으면 이동
	*	@pre	서브 폴더가 하나 이상 있어야 함
	*	@post	depth가 1증가함 stack[depth]에 이동한 폴더 객체 생성
	*	@return	서브 폴더로 이동하면 return 1, 이동하지 못하면 return 0
	*/
	int MoveToFolder();

	/**
	*	@brief	뒤로 가기
	*	@detail	즉 현재 폴더의 상위 폴더로 이동
	*	@pre	현재 폴더의 상위 폴더가 있어야 함
	*	@post	stack의 depth가 1 감소함
	*	@return	뒤로 이동하면 return 1, 이동하지 못하면 return 0
	*/
	int MoveBack();

	/**
	*	@brief	앞으로 가기
	*	@detail	이전에 갔던 하위 폴더로 이동
	*	@pre	이전에 하위 폴더를 갔어야 함
	*	@post	stack의 depth가 1 증가함
	*	@return	앞으로 이동하면 return 1, 이동하지 못하면 return 0
	*/
	int MoveFront();

	/**
	*	@brief	폴더 이름 바꾸기
	*	@detail	원하는 폴더의 fdName 바꾸며 하위 폴더, 파일의 경로 재설정
	*	@pre	서브 폴더가 1개 이상 있어야 함
	*	@post	원하는 폴더의 이름이 바뀜
	*	@return	이름 바꾸기 성공하면 return 1, 아니면 return 0
	*/
	int ChangeFolderName();
	
	/**
	*	@brief	파일 이름 바꾸기
	*	@detail	원하는 파일의 fName 바꾸기
	*	@pre	파일이 1개 이상 있어야 함
	*	@post	원하는 파일의 이름이 바뀜
	*	@return	이름 바꾸기 성공하면 return 1, 아니면 return 0
	*/
	int ChangeFileName();

	/**
	*	@brief	원하는 파일을 열어 내용 작성
	*	@detail	열기를 원하는 파일 이름을 받아 파일을 열고 내용 작성
	*	@pre	파일이 1개 이상
	*	@post	txt파일의 내용이 작성됨
	*	@return	파일 열기에 성공시 1을 리턴, 실패시 0을 리턴.
	*/
	int OpenFile();

	/**
	*	@brief	폴더나 파일 잘라내기
	*	@detail	ClipBoard에 잘라낸 데이터 저장
	*	@pre	폴더나 파일 1개 이상
	*	@post	ClipBoard에 잘라낸 데이터가 저장됨
	*	@return	잘라내기 성공시 1을 리턴, 실패시 0을 리턴
	*/
	int Cut();

	/**
	*	@brief	폴더나 파일 복사
	*	@detail	ClipBoard에 복사한 데이터 저장
	*	@pre	폴더나 파일 1개 이상
	*	@post	ClipBoard에 복사한 데이터가 저장됨
	*	@return	복사 성공시 1을 리턴, 실패시 0을 리턴
	*/
	int Copy();

	/**
	*	@brief	폴더나 파일 붙여넣기
	*	@detail	ClipBoard에 저장된 데이터를 붙여넣기
	*	@pre	ClipBoard에 데이터가 저장되어 있어야 함
	*	@post	폴더에 데이터 추가, 잘라내기한 데이터를 붙인 경우 기존에 있던 폴더에서 데이터 삭제
	*	@return	붙여넣기 성공시 1을 리턴, 실패시 0을 리턴
	*/
	int Paste();

	/*
	*	@brief	자주 열어본 폴더 출력하기
	*	@detail	자주 열어본 폴더 최대 5개를 출력한다.
	*	@pre	FolderType이 저장되어 있어야함
	*	@post	none.
	*/
	void PopularFolderPrint();

	/**
	*	@brief	입력한 경로의 폴더로 이동
	*	@pre	none.
	*	@post	입력한 경로를 가진 폴더가 있다면 이동, 없으면 변화없음
	*/
	void MoveToFolderByPath();

	/**
	*	@brief	바로가기 목록 중 원하는 폴더로 이동
	*	@detail	바로가기 목록을 보여준 후 원하는 폴더로 바로 이동
	*	@pre	바로가기 목록에 폴더가 1개 이상
	*	@post	원하는 폴더로 이동함
	*/
	void MoveToFolderQuickly();

	/**
	*	@brief	원하는 폴더를 바로가기 목록에 추가
	*	@detail	현재 폴더의 서브 폴더 중 원하는 폴더를 바로가기 목록에 추가
	*	@pre	현재 폴더에 서브 폴더가 있음
	*	@post	입력한 이름을 가진 폴더가 있으면 해당 폴더 바로가기 목록에 추가
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