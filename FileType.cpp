#include "FileType.h"

//fdName을 정함
void FileType::SetName(string name)
{
	fName = name;
}

//키보드로부터 name을 입력받음
void FileType::SetNameFromKB() {
	string name;
	cout << "\tName : ";
	getline(cin, name);
	fName = name;
}

//fdPath을 정함
void FileType::SetPath(string path) {
	fPath = path;
}

//키보드로부터 path를 입력받음
void FileType::SetPathFromKB()
{
	cout << "\tPath : ";
	string path;
	cin >> path;
	fPath = path;
}

//fdName을 return
string FileType::GetName() const {
	return fName;
}

string FileType::GetPath() {
	return fPath;
}

//fdCreatTime을 return
string FileType::GetfdCreatTime()
{
	return fCreatTime;
}


// 키보드로부터 전체 정보를 입력
void FileType::SetRecordFromKB() {
	SetNameFromKB();
	SetPathFromKB();
}

// txt파일 생성
int FileType::CreateFile()
{
	ofstream fout(fName + ".txt");
	if (!fout)
		return 0;
	fout.close();
	return 1;
}

//파일 이름을 출력
void FileType::DisplayName() {
	cout << "Name : " << fName << endl;
}


//복사생성자
FileType::FileType(FileType& data)
{
	this->fName = data.fName;
	this->fPath = data.fPath;
	this->fCreatTime = data.fCreatTime;
}

//대입연산자
FileType& FileType::operator= (const FileType& data) {

	this->fName = data.fName;
	this->fPath = data.fPath;
	this->fCreatTime = data.fCreatTime;
	return (*this);
}

//비교연산자
bool FileType::operator == (const FileType& item) const
{
	return (this->fName == item.fName);
}

bool FileType::operator > (const FileType& item) const
{
	if (this->fName > item.fName)
		return 1;
	else
		return 0;
}

bool FileType::operator < (const FileType& item) const
{
	if (this->fName < item.fName)
		return 1;
	else
		return 0;
}

ostream& operator << (ostream& os, const FileType& file)
{
	os << file.GetName();
	return os;
}


// generate the name of a photo file based on the current time.
// It generates 14 digit file name yyyymmddhhmmss
void FileType::GenCreateTime()
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
	fCreatTime = ss.str();  // copy the stream buffer to name 
}



//이름에 keyword가 있는지 확인
int FileType::SearchKeyword(const FileType& data) {
	if (fName.find(data.GetName()) != string::npos)
		return 1;
	else
		return 0;
}

//파일의 정보를 출력
void FileType::DisplayRecordOnScreen()
{
	cout << "\tName : " << fName << endl;
	cout << "\tPath : " << fPath << endl;
	cout << "\tTime : " << fCreatTime.substr(0, 4) << "." << fCreatTime.substr(4, 2) << "." << fCreatTime.substr(6, 2) << " / " << fCreatTime.substr(8, 2) << ":" << fCreatTime.substr(10, 2) << endl;
}

// txt파일을 열고 내용 작성
int FileType::OpenThis()
{
	fstream fout;
	fout.open(fName + ".txt");
	if (!fout)
		return 0;

	cout<<"\tWrite text and enter \"file close\"to close file."<<endl;
	string buffer;

	while (getline(cin, buffer))
	{
		if (buffer=="file close")
		{
			cout << "\tFile Close." << endl;
			break;
		}
		fout << buffer << endl;
	}
	fout.close();
	return 1;
}