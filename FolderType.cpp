#include "FolderType.h"

//fdName을 정함
void FolderType::SetName(string name)
{
	fdName = name;
}

//키보드로부터 name을 입력받음
void FolderType::SetNameFromKB() {
	string name;
	cout << "\tName : ";
	getline(cin, name);
	fdName = name;
}

//fdPath을 정함
void FolderType::SetPath(string path) {
	fdPath = path;
}

//키보드로부터 path를 입력받음
void FolderType::SetPathFromKB()
{
	cout << "\tPath : ";
	string path;
	cin >> path;
	fdPath = path;
}

//fdName을 return
string FolderType::GetName() const {
	return fdName;
}

string FolderType::GetPath() {
	return fdPath;
}

//fdCreatTime을 return
string FolderType::GetfdCreatTime()
{
	return fdCreatTime;
}

//fdSubFolderNum을 return
int FolderType::GetSubFolderNum()
{
	return fdSubFolderNum;
}

//FileNum을 return
int FolderType::GetFileNum()
{
	return FileNum;
}

//visit을 return
int FolderType::GetVisit()
{
	return visit;
}

//visit 1 증가
void FolderType::IncreaseVisit()
{
	visit++;
}

// 키보드로부터 전체 정보를 입력
void FolderType::SetRecordFromKB() {
	SetNameFromKB();
	SetPathFromKB();
}

//폴더 이름을 출력
void FolderType::DisplayName() {
	cout << "\t" << fdName << endl;
}


//복사생성자
FolderType::FolderType(FolderType& data)
{
	this->fdName = data.fdName;
	this->fdPath = data.fdPath;
	this->fdCreatTime = data.fdCreatTime;
	this->fdSubFolderNum = data.fdSubFolderNum;
	this->FileNum = data.FileNum;
	if (data.FolderTree != NULL)
		this->FolderTree = new BinarySearchTree<FolderType>(*data.FolderTree);
	else
		this->FolderTree = NULL;

	if (data.FileTree != NULL)
		this->FileTree = new BinarySearchTree<FileType>(*data.FileTree);
	else
		this->FileTree = NULL;
}

//대입연산자
FolderType& FolderType::operator= (const FolderType& data) {
	
	this->fdName = data.fdName;
	this->fdPath = data.fdPath;
	this->fdCreatTime=data.fdCreatTime;
	this->fdSubFolderNum = data.fdSubFolderNum;
	this->FileNum = data.FileNum;
	if (data.FolderTree != NULL)
		this->FolderTree = new BinarySearchTree<FolderType>(*data.FolderTree);
	else
		this->FolderTree = NULL;

	if (data.FileTree != NULL)
		this->FileTree = new BinarySearchTree<FileType>(*data.FileTree);
	else
		this->FileTree = NULL;

	return (*this);
}

//비교연산자
bool FolderType::operator ==(const FolderType& item) const
{
	return (this->fdName == item.fdName);
}

bool FolderType::operator > (const FolderType& item) const
{
	if (this->fdName > item.fdName)
		return 1;
	else
		return 0;
}

bool FolderType::operator < (const FolderType& item) const
{
	if (this->fdName < item.fdName)
		return 1;
	else
		return 0;
}

ostream& operator << (ostream& os, const FolderType& folder)
{
	os << folder.GetName();
	return os;
}


// generate the name of a photo file based on the current time.
// It generates 14 digit file name yyyymmddhhmmss
void FolderType::GenCreateTime()
{
	// Declaring argument for time() 
	time_t tt;

	// Declaring variable to store return value of 
	// localtime() 
	struct tm * ti;

	// Applying time() 
	time(&tt);

	// Using localtime() 
	ti = localtime(&tt);

	// stream output
	stringstream ss;
	ss << setw(4) << ti->tm_year + 1900 << setfill('0') << setw(2)
		<< ti->tm_mon + 1 << setfill('0') << setw(2) << ti->tm_mday << setfill('0') << setw(2) << ti->tm_hour << setfill('0') << setw(2)
		<< ti->tm_min << setfill('0') << setw(2) << ti->tm_sec << "\0";
	fdCreatTime = ss.str();  // copy the stream buffer to name 
}


// 새폴더 정보를 키보드로부터 읽어서 폴더리스트에 추가, 
//처음 폴더이면 sortedList를 동적으로 할당하여 초기화 하고 추가
int FolderType::AddFolder()
{
	if (fdSubFolderNum == 0)
		FolderTree = new BinarySearchTree<FolderType>;

	FolderType data;
	data.SetNameFromKB();
	data.SetPath(fdPath + "/" + data.GetName()); // 서브폴더 패스 설정
	data.GenCreateTime();
	//data folder 기탄 변수를 키보드로부터 읽어 들인다. 
	if (FolderTree->Add(data))
	{
		fdSubFolderNum++;
		return 1;
	}
	return 0;
}

//data에 있는 새폴더 정보를 읽어서 폴더리스트에 추가
int FolderType::AddFolder(FolderType& data)
{
	if (fdSubFolderNum == 0)
		FolderTree = new BinarySearchTree<FolderType>;

	//data folder 기탄 변수를 키보드로부터 읽어 들인다. 
	if (FolderTree->Add(data))
	{
		fdSubFolderNum++;
		return 1;
	}
	return 0;
}

// 새파일 정보를 키보드로부터 읽어서 파일리스트에 추가, 
//처음 파일이면 sortedList를 동적으로 할당하여 초기화 하고 추가
int FolderType::AddFile()
{
	if (FileNum == 0)
		FileTree = new BinarySearchTree<FileType>;

	FileType data;
	data.SetNameFromKB();
	data.SetPath(fdPath + "/" + data.GetName()); // 서브폴더 패스 설정
	data.GenCreateTime();

	//data folder 기탄 변수를 키보드로부터 읽어 들인다. 
	if (FileTree->Add(data))
	{
		FileNum++;
		//FileType객체 내 파일 생성
		FileType* pointer = GetFilePointer(data);
		pointer->CreateFile();
		return 1;
	}
	return 0;
}

// data에 있는 새 파일 정보를 읽어서 파일리스트에 추가
int FolderType::AddFile(FileType& data)
{
	if (FileNum == 0)
		FileTree = new BinarySearchTree<FileType>;

	//data folder 기탄 변수를 키보드로부터 읽어 들인다. 
	if (FileTree->Add(data))
	{
		FileNum++;
		//FileType객체 내 파일 생성
		FileType* pointer = GetFilePointer(data);
		pointer->CreateFile();
		return 1;
	}
	return 0;
}

// 삭제할 폴더 정보를 읽어서 해당 폴더를 찾아서 삭제
int FolderType::DeleteFolder(FolderType folder) {

	if (fdSubFolderNum==0)
	{
		return 0;
	}
	if (FolderTree->DeleteItem(folder)) {
		fdSubFolderNum--;
		if (FolderTree->IsEmpty()) {
			delete FolderTree;
			FolderTree = NULL;
		}
		return 1;
	}
	return 0;
}

// 삭제할 파일 정보를 읽어서 해당 파일을 찾아서 삭제
int FolderType::DeleteFile(FileType file) {

	if (FileNum == 0)
	{
		return 0;
	}
	if (FileTree->DeleteItem(file)) {
		FileNum--;
		if (FileTree->IsEmpty()) {
			delete FileTree;
			FileTree = NULL;
		}
		return 1;
	}
	return 0;
}

//이름에 keyword가 있는지 확인
int FolderType::SearchKeyword(const FolderType& data) {
	if (fdName.find(data.GetName())!=string::npos)
		return 1;
	else
		return 0;
}

//폴더의 정보를 출력
void FolderType::DisplayRecordOnScreen()
{
	cout << "\tName : " << fdName << endl;
	cout << "\tPath : " << fdPath << endl;
	cout << "\tTime : " << fdCreatTime.substr(0,4) << "." << fdCreatTime.substr(4,2) << "." << fdCreatTime.substr(6,2) << " / " << fdCreatTime.substr(8,2) << ":" << fdCreatTime.substr(10,2) << endl;
}

// 검색할 폴더정보를 받아 검색하여 해당 폴더를 저장
void FolderType::RetrieveFolderByKeyword(string keyword, DoublySortedLinkedList<FolderType>* FolderResult)
{
	if (FolderTree != NULL)
	{
		FolderType** FolderList = new FolderType*[fdSubFolderNum];
		FolderTree->StoreData(FolderList);
		for (int i = 0; i < fdSubFolderNum; i++)
		{
			FolderList[i]->RetrieveFolderByKeyword(keyword, FolderResult);
		}
		delete[] FolderList;
	}
	if (this->fdName.find(keyword) != string::npos)
	{
		FolderResult->Add(*this);
	}
}


// 검색할 파일정보를 받아 검색하여 해당 파일을 저장
void FolderType::RetrieveFileByKeyword(string keyword, DoublySortedLinkedList<FileType>* FileResult)
{
	if (FolderTree != NULL)
	{
		FolderType** FolderList = new FolderType*[fdSubFolderNum];
		FolderTree->StoreData(FolderList);
		for (int i = 0; i < fdSubFolderNum; i++)
		{
			FolderList[i]->RetrieveFileByKeyword(keyword, FileResult);
		}
		delete[] FolderList;
	}
	if (FileTree != NULL)
	{
		FileType** FileList = new FileType*[FileNum];
		FileTree->StoreData(FileList);
		for (int i = 0; i < FileNum; i++)
		{
			if ((FileList[i]->GetName()).find(keyword) != string::npos)
			{
				FileResult->Add(*FileList[i]);
			}
		}
		delete[] FileList;
	}
}

// 폴더정보 화면출력
// 폴더 멤벼변수 일출력 함수들 정의 
void FolderType::DisplayAllFolderName() {
	cout << "\t----SubFolder List----" << endl;

	if (FolderTree==NULL || fdSubFolderNum==0)
	{
		cout << "\tSub Folder doesn't exist." << endl;
	}
	else
	{
		FolderTree->PrintTree(cout);
	}
	cout << endl;
}

// 파일정보 화면출력
// 파일 멤벼변수 일출력 함수들 정의 
void FolderType::DisplayAllFileName() {
	cout << "\t-----File List-----" << endl;
	if (FileTree == NULL || FileNum == 0)
	{
		cout << "\tFile doesn't exist." << endl;
	}
	else
	{
		FileTree->PrintTree(cout);
	}
	cout << endl;
}

//fdFolderList의 GetPointer함수 실행
FolderType* FolderType::GetFolderPointer(FolderType& data)
{
	return FolderTree->GetPointer(data);
}

//FileList의 GetPointer함수 실행
FileType* FolderType::GetFilePointer(FileType& data)
{
	return FileTree->GetPointer(data);
}


// 모든 하위 폴더의 경로를 다시 설정
void FolderType::ChangeUnderPath(string path)
{
	if (FolderTree!=NULL)
	{
		FolderType** FolderList = new FolderType*[fdSubFolderNum];
		FolderTree->StoreData(FolderList);
		string newpath;
		for (int i = 0; i < fdSubFolderNum; i++)
		{
			newpath = path + "/" + FolderList[i]->GetName();
			FolderList[i]->ChangeUnderPath(newpath);
			FolderList[i]->SetPath(newpath);
		}
	}
	if (FileTree!=NULL)
	{
		FileType** FileList = new FileType*[FileNum];
		FileTree->StoreData(FileList);
		string newpath2;
		for (int i = 0; i < FileNum; i++)
		{
			newpath2 = path + "/" + FileList[i]->GetName();
			FileList[i]->SetPath(newpath2);
		}
	}
}
