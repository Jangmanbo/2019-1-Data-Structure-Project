#include "FolderType.h"

//fdName�� ����
void FolderType::SetName(string name)
{
	fdName = name;
}

//Ű����κ��� name�� �Է¹���
void FolderType::SetNameFromKB() {
	string name;
	cout << "\tName : ";
	getline(cin, name);
	fdName = name;
}

//fdPath�� ����
void FolderType::SetPath(string path) {
	fdPath = path;
}

//Ű����κ��� path�� �Է¹���
void FolderType::SetPathFromKB()
{
	cout << "\tPath : ";
	string path;
	cin >> path;
	fdPath = path;
}

//fdName�� return
string FolderType::GetName() const {
	return fdName;
}

string FolderType::GetPath() {
	return fdPath;
}

//fdCreatTime�� return
string FolderType::GetfdCreatTime()
{
	return fdCreatTime;
}

//fdSubFolderNum�� return
int FolderType::GetSubFolderNum()
{
	return fdSubFolderNum;
}

//FileNum�� return
int FolderType::GetFileNum()
{
	return FileNum;
}

//visit�� return
int FolderType::GetVisit()
{
	return visit;
}

//visit 1 ����
void FolderType::IncreaseVisit()
{
	visit++;
}

// Ű����κ��� ��ü ������ �Է�
void FolderType::SetRecordFromKB() {
	SetNameFromKB();
	SetPathFromKB();
}

//���� �̸��� ���
void FolderType::DisplayName() {
	cout << "\t" << fdName << endl;
}


//���������
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

//���Կ�����
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

//�񱳿�����
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


// ������ ������ Ű����κ��� �о ��������Ʈ�� �߰�, 
//ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�
int FolderType::AddFolder()
{
	if (fdSubFolderNum == 0)
		FolderTree = new BinarySearchTree<FolderType>;

	FolderType data;
	data.SetNameFromKB();
	data.SetPath(fdPath + "/" + data.GetName()); // �������� �н� ����
	data.GenCreateTime();
	//data folder ��ź ������ Ű����κ��� �о� ���δ�. 
	if (FolderTree->Add(data))
	{
		fdSubFolderNum++;
		return 1;
	}
	return 0;
}

//data�� �ִ� ������ ������ �о ��������Ʈ�� �߰�
int FolderType::AddFolder(FolderType& data)
{
	if (fdSubFolderNum == 0)
		FolderTree = new BinarySearchTree<FolderType>;

	//data folder ��ź ������ Ű����κ��� �о� ���δ�. 
	if (FolderTree->Add(data))
	{
		fdSubFolderNum++;
		return 1;
	}
	return 0;
}

// ������ ������ Ű����κ��� �о ���ϸ���Ʈ�� �߰�, 
//ó�� �����̸� sortedList�� �������� �Ҵ��Ͽ� �ʱ�ȭ �ϰ� �߰�
int FolderType::AddFile()
{
	if (FileNum == 0)
		FileTree = new BinarySearchTree<FileType>;

	FileType data;
	data.SetNameFromKB();
	data.SetPath(fdPath + "/" + data.GetName()); // �������� �н� ����
	data.GenCreateTime();

	//data folder ��ź ������ Ű����κ��� �о� ���δ�. 
	if (FileTree->Add(data))
	{
		FileNum++;
		//FileType��ü �� ���� ����
		FileType* pointer = GetFilePointer(data);
		pointer->CreateFile();
		return 1;
	}
	return 0;
}

// data�� �ִ� �� ���� ������ �о ���ϸ���Ʈ�� �߰�
int FolderType::AddFile(FileType& data)
{
	if (FileNum == 0)
		FileTree = new BinarySearchTree<FileType>;

	//data folder ��ź ������ Ű����κ��� �о� ���δ�. 
	if (FileTree->Add(data))
	{
		FileNum++;
		//FileType��ü �� ���� ����
		FileType* pointer = GetFilePointer(data);
		pointer->CreateFile();
		return 1;
	}
	return 0;
}

// ������ ���� ������ �о �ش� ������ ã�Ƽ� ����
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

// ������ ���� ������ �о �ش� ������ ã�Ƽ� ����
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

//�̸��� keyword�� �ִ��� Ȯ��
int FolderType::SearchKeyword(const FolderType& data) {
	if (fdName.find(data.GetName())!=string::npos)
		return 1;
	else
		return 0;
}

//������ ������ ���
void FolderType::DisplayRecordOnScreen()
{
	cout << "\tName : " << fdName << endl;
	cout << "\tPath : " << fdPath << endl;
	cout << "\tTime : " << fdCreatTime.substr(0,4) << "." << fdCreatTime.substr(4,2) << "." << fdCreatTime.substr(6,2) << " / " << fdCreatTime.substr(8,2) << ":" << fdCreatTime.substr(10,2) << endl;
}

// �˻��� ���������� �޾� �˻��Ͽ� �ش� ������ ����
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


// �˻��� ���������� �޾� �˻��Ͽ� �ش� ������ ����
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

// �������� ȭ�����
// ���� �⺭���� ����� �Լ��� ���� 
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

// �������� ȭ�����
// ���� �⺭���� ����� �Լ��� ���� 
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

//fdFolderList�� GetPointer�Լ� ����
FolderType* FolderType::GetFolderPointer(FolderType& data)
{
	return FolderTree->GetPointer(data);
}

//FileList�� GetPointer�Լ� ����
FileType* FolderType::GetFilePointer(FileType& data)
{
	return FileTree->GetPointer(data);
}


// ��� ���� ������ ��θ� �ٽ� ����
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
