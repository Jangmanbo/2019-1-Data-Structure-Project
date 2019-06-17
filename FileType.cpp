#include "FileType.h"

//fdName�� ����
void FileType::SetName(string name)
{
	fName = name;
}

//Ű����κ��� name�� �Է¹���
void FileType::SetNameFromKB() {
	string name;
	cout << "\tName : ";
	getline(cin, name);
	fName = name;
}

//fdPath�� ����
void FileType::SetPath(string path) {
	fPath = path;
}

//Ű����κ��� path�� �Է¹���
void FileType::SetPathFromKB()
{
	cout << "\tPath : ";
	string path;
	cin >> path;
	fPath = path;
}

//fdName�� return
string FileType::GetName() const {
	return fName;
}

string FileType::GetPath() {
	return fPath;
}

//fdCreatTime�� return
string FileType::GetfdCreatTime()
{
	return fCreatTime;
}


// Ű����κ��� ��ü ������ �Է�
void FileType::SetRecordFromKB() {
	SetNameFromKB();
	SetPathFromKB();
}

// txt���� ����
int FileType::CreateFile()
{
	ofstream fout(fName + ".txt");
	if (!fout)
		return 0;
	fout.close();
	return 1;
}

//���� �̸��� ���
void FileType::DisplayName() {
	cout << "Name : " << fName << endl;
}


//���������
FileType::FileType(FileType& data)
{
	this->fName = data.fName;
	this->fPath = data.fPath;
	this->fCreatTime = data.fCreatTime;
}

//���Կ�����
FileType& FileType::operator= (const FileType& data) {

	this->fName = data.fName;
	this->fPath = data.fPath;
	this->fCreatTime = data.fCreatTime;
	return (*this);
}

//�񱳿�����
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



//�̸��� keyword�� �ִ��� Ȯ��
int FileType::SearchKeyword(const FileType& data) {
	if (fName.find(data.GetName()) != string::npos)
		return 1;
	else
		return 0;
}

//������ ������ ���
void FileType::DisplayRecordOnScreen()
{
	cout << "\tName : " << fName << endl;
	cout << "\tPath : " << fPath << endl;
	cout << "\tTime : " << fCreatTime.substr(0, 4) << "." << fCreatTime.substr(4, 2) << "." << fCreatTime.substr(6, 2) << " / " << fCreatTime.substr(8, 2) << ":" << fCreatTime.substr(10, 2) << endl;
}

// txt������ ���� ���� �ۼ�
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