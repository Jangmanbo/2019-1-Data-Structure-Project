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

	// 복사생성자
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
	*	@brief	fName을 정함
	*	@detail	파라미터로 받은 name을 fName으로 저장
	*	@pre	none.
	*	@post	fName값이 설정됨
	*	@param	name	fName으로 설정할 값
	*/
	void SetName(string name);

	/**
	*	@brief	키보드로부터 name을 입력받음
	*	@detail	키보드로부터 name을 입력받고 fName에 대입
	*	@pre	none.
	*	@post	fName값이 설정됨
	*/
	void SetNameFromKB();

	/**
	*	@brief	fPath을 정함
	*	@detail	파라미터로 받은 path을 fPath으로 저장
	*	@pre	none.
	*	@post	fPath값이 설정됨
	*	@param	path	fPath로 설정할 값
	*/
	void SetPath(string path);

	/**
	*	@brief	키보드로부터 path를 입력받음
	*	@detail	키보드로부터 path를 입력받고 fPath에 저장
	*	@pre	none.
	*	@post	fPath값이 설정됨
	*/
	void SetPathFromKB();

	/**
	*	@brief	fName을 return
	*	@detail	fName을 return
	*	@pre	fName이 설정되어있음
	*	@post	none.
	*	@return	fName
	*/
	string GetName() const;

	/**
	*	@brief	fPath를 return
	*	@detail	fPath를 return
	*	@pre	fPath가 설정되어있음
	*	@post	none.
	*	@return	fPath
	*/
	string GetPath();

	/**
	*	@brief	fCreatTime을 return
	*	@detail	fCreatTime을 return
	*	@pre	fCreatTime이 설정되어있음
	*	@post	none.
	*	@return	fCreatTime
	*/
	string GetfdCreatTime();


	/**
	*	@brief	키보드로부터 전체 정보를 입력받음
	*	@detail	키보드로부터 name, path를 입력받음
	*	@pre	none.
	*	@post	name, path가 설정됨
	*/
	void SetRecordFromKB();


	/**
	*	@brief	txt파일 생성
	*	@detail	파일 이름.txt파일을 생성
	*	@pre	none.
	*	@post	none.
	*	@return	파일 생성에 성공하면 return 1, 아니면 return 0
	*/
	int CreateFile();

	/**
	*	@brief	파일 이름을 출력
	*	@detail	화면에 파일 이름을 출력
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayName();

	/**
	*	@brief	이름에 keyword가 있는지 확인
	*	@detail	이름에 keyword가 있는지 알려줌
	*	@pre	이 함수를 실행하는 파일 어떤 파일의 하위파일임
	*	@post	none.
	*	@param	data	keyword를 가지고 있는 FileType 객체
	*	@return	이름에 keyword가 있으면 return 1, 아니면 return 0
	*/
	int SearchKeyword(const FileType& data);


	//복사생성자
	FileType(FileType& data);

	//대입연산자
	FileType& operator= (const FileType& data);

	//비교연산자
	bool operator == (const FileType& item) const;

	bool operator > (const FileType& item) const;

	bool operator < (const FileType& item) const;

	friend ostream& operator << (ostream& os, const FileType& file);

	/**
	*	@brief	파일이 만들어진 시간을 Set
	*	@detail	파일이 만들어진 시간을 string 타입으로 fCreatTime에 저장
	*	@pre	none.
	*	@post	none.
	*/
	void GenCreateTime();


	/**
	*	@brief	파일의 정보를 출력
	*	@detail	파일의 이름, 위치, 생성시간을 화면에 출력
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	txt파일을 열고 내용 작성
	*	@detail	txt파일을 열고 내용을 작성하며 file close 입력 시 파일 닫음
	*	@pre	none.
	*	@post	txt파일 내용이 업데이트됨
	*	@return	파일 열기에 성공하면 return 1, 아니면 return 0
	*/
	int OpenThis();

private:
	string fPath;
	string fName;
	string fCreatTime;
};
#endif