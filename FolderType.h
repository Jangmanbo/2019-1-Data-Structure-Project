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
	*	@brief	fdName을 정함
	*	@detail	파라미터로 받은 name을 fdName으로 저장
	*	@pre	none.
	*	@post	fdName값이 설정됨
	*	@param	name	fdName으로 설정할 값
	*/
	void SetName(string name);

	/**
	*	@brief	키보드로부터 name을 입력받음
	*	@detail	키보드로부터 name을 입력받고 fdName에 대입
	*	@pre	none.
	*	@post	fdName값이 설정됨
	*/
	void SetNameFromKB();

	/**
	*	@brief	fdPath을 정함
	*	@detail	파라미터로 받은 path을 fdPath으로 저장
	*	@pre	none.
	*	@post	fdPath값이 설정됨
	*	@param	path	fdPath로 설정할 값
	*/
	void SetPath(string path);

	/**
	*	@brief	키보드로부터 path를 입력받음
	*	@detail	키보드로부터 path를 입력받고 fdPath에 저장
	*	@pre	none.
	*	@post	fdPath값이 설정됨
	*/
	void SetPathFromKB();

	/**
	*	@brief	fdName을 return
	*	@detail	fdName을 return
	*	@pre	fdName이 설정되어있음
	*	@post	none.
	*	@return	fdName
	*/
	string GetName() const;

	/**
	*	@brief	fdPath를 return
	*	@detail	fdPath를 return
	*	@pre	fdPath가 설정되어있음
	*	@post	none.
	*	@return	fdPath
	*/
	string GetPath();

	/**
	*	@brief	fdCreatTime을 return
	*	@detail	fdCreatTime을 return
	*	@pre	fdCreatTime이 설정되어있음
	*	@post	none.
	*	@return	fdCreatTime
	*/
	string GetfdCreatTime();

	/**
	*	@brief	fdSubFolderNum을 return
	*	@detail	fdSubFolderNum을 return
	*	@pre	fdSubFolderNum이 설정되어있음
	*	@post	none.
	*	@return	fdSubFolderNum
	*/
	int GetSubFolderNum();

	/**
	*	@brief	FileNum을 return
	*	@detail	FileNum을 return
	*	@pre	FileNum이 설정되어있음
	*	@post	none.
	*	@return	FileNum
	*/
	int GetFileNum();

	/**
	*	@brief	visit을 return
	*	@detail	visit을 return
	*	@pre	visit이 설정되어있음
	*	@post	none.
	*	@return	visit
	*/
	int GetVisit();

	/**
	*	@brief	visit 1 증가
	*	@detail	visit 1 증가
	*	@pre	visit이 설정되어있음
	*	@post	none.
	*/
	void IncreaseVisit();

	/**
	*	@brief	키보드로부터 전체 정보를 입력받음
	*	@detail	키보드로부터 name, path를 입력받음
	*	@pre	none.
	*	@post	name, path가 설정됨
	*/
	void SetRecordFromKB();

	/**
	*	@brief	폴더 이름을 출력
	*	@detail	화면에 폴더 이름을 출력
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayName();

	/**
	*	@brief	이름에 keyword가 있는지 확인
	*	@detail	이름에 keyword가 있는지 알려줌
	*	@pre	이 함수를 실행하는 폴더가 어떤 폴더의 하위폴더임
	*	@post	none.
	*	@param	data	keyword를 가지고 있는 FolderType 객체
	*	@return	이름에 keyword가 있으면 return 1, 아니면 return 0
	*/
	int SearchKeyword(const FolderType& data);


	//복사생성자
	FolderType(FolderType& data);

	//대입연산자
	FolderType& operator= (const FolderType& data);

	//비교연산자
	bool operator ==(const FolderType& item) const;

	bool operator > (const FolderType& item) const;

	bool operator < (const FolderType& item) const;

	friend ostream& operator << (ostream& os, const FolderType& folder);

	/**
	*	@brief	폴더가 만들어진 시간을 Set
	*	@detail	폴더가 만들어진 시간을 string 타입으로 fdCreatTime에 저장
	*	@pre	none.
	*	@post	none.
	*/
	void GenCreateTime();

	/**
	*	@brief	새폴더 정보를 키보드로부터 읽어서 폴더리스트에 추가
	*	@detail 처음 폴더이면 sortedList를 동적으로 할당하여 초기화 하고 추가, 동일한 이름을 가진 폴더가 있으면 추가X 
	*	@pre	서브폴더리스트 길이가 MAXSIZE 미만이어야 함
	*	@post	폴더 리스트에 폴더가 추가되고 fdFolderNum이 1증가
	*	@return	폴더 추가에 성공하면 return 1, 아니면 return 0
	*/
	int AddFolder();

	/**
	*	@brief	data에 있는 새폴더 정보를 읽어서 폴더리스트에 추가
	*	@detail 처음 폴더이면 sortedList를 동적으로 할당하여 초기화 하고 추가, 동일한 이름을 가진 폴더가 있으면 추가X
	*	@pre	none.
	*	@post	폴더 리스트에 폴더가 추가되고 fdFolderNum이 1증가
	*	@param	data	추가할 폴더 FolderType객체
	*	@return	폴더 추가에 성공하면 return 1, 아니면 return 0
	*/
	int AddFolder(FolderType& data);
	
	/**
	*	@brief	새파일 정보를 키보드로부터 읽어서 파일리스트에 추가
	*	@detail 처음 파일이면 sortedList를 동적으로 할당하여 초기화 하고 추가, 동일한 이름을 가진 파일이 있으면 추가X
	*	@pre	none.
	*	@post	파일 리스트에 파일이 추가되고 FileNum이 1증가
	*	@return	파일 추가에 성공하면 return 1, 아니면 return 0
	*/
	int AddFile();

	/**
	*	@brief	data에 있는 새 파일 정보를 읽어서 파일리스트에 추가
	*	@detail 처음 파일이면 sortedList를 동적으로 할당하여 초기화 하고 추가, 동일한 이름을 가진 파일이 있으면 추가X
	*	@pre	none.
	*	@post	파일 리스트에 파일이 추가되고 FileNum이 1증가
	*	@return	파일 추가에 성공하면 return 1, 아니면 return 0
	*/
	int AddFile(FileType& data);

	/**
	*	@brief	삭제할 폴더 정보를 받아 해당 폴더를 찾아서 삭제
	*	@detail 삭제할 폴더 이름을 파라미터로 받고 해당 폴더가 있으면 삭제
	*	@pre	서브 폴더가 1개 이상
	*	@post	폴더가 삭제되고, 삭제 후 서브 폴더가 0개면 fdFolderList=NULL;
	*	@return	폴더 삭제에 성공하면 return 1, 아니면 return 0
	*/
	int DeleteFolder(FolderType folder);

	/**
	*	@brief	삭제할 파일 정보를 받아 해당 파일을 찾아서 삭제
	*	@detail 삭제할 파일 이름을 파라미터로 받고 해당 파일이 있으면 삭제
	*	@pre	파일이 1개 이상
	*	@post	파일이 삭제되고, 삭제 후 파일이 0개면 FileList=NULL;
	*	@param	file	삭제하고자 하는 파일의 이름이 설정되어있는 FileType객체
	*	@return	파일 삭제에 성공하면 return 1, 아니면 return 0
	*/
	int DeleteFile(FileType file);

	/**
	*	@brief	폴더의 정보를 출력
	*	@detail	폴더의 이름, 위치, 생성시간을 화면에 출력
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecordOnScreen();


	/**
	*	@brief	검색할 폴더정보를 받아 검색하여 해당 폴더를 저장
	*	@detail	keyword를 가진 폴더를 searchFolderResult에 담음
	*	@pre	none.
	*	@post	none.
	*	@param	keyword	검색할 keyword
	*/
	void RetrieveFolderByKeyword(string keyword, DoublySortedLinkedList<FolderType>* FolderResult);

	/**
	*	@brief	검색할 파일정보를 받아 검색하여 해당 파일을 저장
	*	@detail	keyword를 가진 파일을 searchFileResult에 담음
	*	@pre	none.
	*	@post	none.
	*	@param	keyword	검색할 keyword
	*/
	void RetrieveFileByKeyword(string keyword, DoublySortedLinkedList<FileType>* FileResult);

	/**
	*	@brief	모든 서브폴더의 이름을 출력
	*	@detail	서브폴더가 없으면 가진 서브폴더가 없음을 알림, 있으면 모든 서브 폴더의 이름을 출력
	*	@pre	서브폴더가 1개 이상 있어야함
	*	@post	none.
	*/
	void DisplayAllFolderName();

	/**
	*	@brief	모든 파일의 이름을 출력
	*	@detail	파일이 없으면 가진 서브폴더가 없음을 알림, 있으면 모든 파일의 이름을 출력
	*	@pre	파일 1개 이상 있어야함
	*	@post	none.
	*/
	void DisplayAllFileName();

	/**
	*	@brief	fdFolderList의 GetPointer함수 실행
	*	@detail	fdFolderList의 GetPointer함수 실행하고 함수의 리턴값을 리턴
	*	@pre	none.
	*	@post	data에 포인터 주소값이 들어감
	*	@param	data	포인터를 반환할 폴더의 이름을 가진 FolderType 객체
	*	@return	fdFolderList의 GetPointer의 리턴값을 리턴
	*/
	FolderType* GetFolderPointer(FolderType& data);

	/**
	*	@brief	FileList의 GetPointer함수 실행
	*	@detail	FileList의 GetPointer함수 실행하고 함수의 리턴값을 리턴
	*	@pre	none.
	*	@post	data에 포인터 주소값이 들어감
	*	@param	data	포인터를 반환할 파일의 이름을 가진 FileType 객체
	*	@return	FileList의 GetPointer의 리턴값을 리턴
	*/
	FileType* GetFilePointer(FileType& data);


	/**
	*	@brief	모든 하위 폴더의 경로를 다시 설정
	*	@detail	모든 하위 폴더의 경로가 현재 폴더의 바뀐 이름을 반영하여 바뀜
	*	@pre	폴더의 이름이 바뀜
	*	@post	하위 폴더의 경로 재설정
	*	@param	path	이 폴더의 경로
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