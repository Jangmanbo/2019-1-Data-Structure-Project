#include "Application.h"
#include "FolderType.h"

// Program driver.
void Application::Run()
{
	while(1)
	{
		m_Command = GetCommand();

		switch(m_Command)
		{
		case 1:		// 새 폴더 생성
			NewFolder();
			break;
		case 2:		// 새 파일 생성
			NewFile();
			break;
		case 3:		// 서브 폴더 삭제
			DeleteFolder();
			break;
		case 4:		// 파일 삭제
			DeleteFile();
			break;
		case 5:		// 폴더 이름 바꾸기
			ChangeFolderName();
			break;
		case 6:		// 파일 이름 바꾸기
			ChangeFileName();
			break;
		case 7:		// 서브 폴더로 이동
			MoveToFolder();
			break;
		case 8:		// 파일 열기
			OpenFile();
			break;
		case 9:		// 모든 폴더, 파일 검색
			RetriveAllByName();
			break;
		case 10:	// 경로 탐색
			MoveToFolderByPath();
			break;
		case 11:	// 최근 열어본 폴더,파일 출력
			DisplayRecent();
			break;
		case 12:	// 자주 열어본 폴더 출력
			PopularFolderPrint();
			break;
		case 13:	// 현재 폴더의 속성을 출력
			DisplayProperty();
			break;
		case 14:	// 뒤로 가기
			MoveBack();
			break;
		case 15:	// 앞으로 가기
			MoveFront();
			break;
		case 16:	// 잘라내기
			Cut();
			break;
		case 17:	// 복사
			Copy();
			break;
		case 18:	// 붙여넣기
			Paste();
			break;
		case 19:	// 바로가기 목록
			MoveToFolderQuickly();
			break;
		case 20:	// 바로가기 목록에 폴더 추가
			AddFolderToList();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\tCurrent Path : "<< m_CurPointer.GetStackPointer()->GetPath()<<endl;
	DisplayAllItem();
	cout << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : 새 폴더 생성" << endl;
	cout << "\t   2 : 새 파일 생성" << endl;
	cout << "\t   3 : 서브 폴더 삭제" << endl;
	cout << "\t   4 : 파일 삭제" << endl;
	cout << "\t   5 : 서브 폴더 이름 바꾸기" << endl;
	cout << "\t   6 : 파일 이름 바꾸기" << endl;
	cout << "\t   7 : 서브 폴더 이동" << endl;
	cout << "\t   8 : 파일 열기" << endl;
	cout << "\t   9 : 폴더, 파일 키워드 검색" << endl;
	cout << "\t   10 : 입력한 경로의 폴더로 이동" << endl;
	cout << "\t   11 : 최근 열어본 폴더, 파일" << endl;
	cout << "\t   12 : 자주 열어본 폴더" << endl;
	cout << "\t   13 : 현재 폴더 속성" << endl;
	cout << "\t   14 : 뒤로 가기" << endl;
	cout << "\t   15 : 앞으로 가기" << endl;
	cout << "\t   16 : 잘라내기" << endl;
	cout << "\t   17 : 복사" << endl;
	cout << "\t   18 : 붙여넣기" << endl;
	cout << "\t   19 : 바로가기 목록" << endl;
	cout << "\t   20 : 바로가기 목록에 폴더 추가" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	cin.ignore();

	return command;
}


// Add new record into list.
int Application::NewFolder()
{
	cout << "\tEnter the name to add." << endl;

	m_CurPointer.GetStackPointer()->AddFolder();

	return 1;
}


// Add new record into list.
int Application::NewFile()
{
	cout << "\tEnter the name to add." << endl;

	m_CurPointer.GetStackPointer()->AddFile();

	return 1;
}


// 현재 폴더 내에서 해당 keyword를 가진 데이터를 찾아 출력한다.
int Application::RetriveAllByName()
{
	bool exist = false;
	cout << "\tEnter the keyword." << endl;

	string keyword;
	cout << "\tKeyword : ";
	cin >> keyword;
	cout << endl;

	DoublySortedLinkedList<FolderType>* FolderList = new DoublySortedLinkedList<FolderType>;
	DoublySortedLinkedList<FileType>* FileList = new DoublySortedLinkedList<FileType>;

	m_CurPointer.GetStackPointer()->RetrieveFolderByKeyword(keyword, FolderList);
	m_CurPointer.GetStackPointer()->RetrieveFileByKeyword(keyword, FileList);

	cout << "\t-------FolderList-------" << endl;
	FolderList->DisplayAllName();

	cout << "\t--------FileList--------" << endl;
	FileList->DisplayAllName();

	return 1;
}

// 리스트에서 해당 name을 가진 folder을 찾아 제거한다.
int Application::DeleteFolder()
{
	int pre = m_CurPointer.GetStackPointer()->GetSubFolderNum();//이전 item개수를 받아온다.

	cout << "\tEnter the name to delete." << endl;

	FolderType folder;
	folder.SetNameFromKB();

	if (m_CurPointer.GetStackPointer()->DeleteFolder(folder) && pre == m_CurPointer.GetStackPointer()->GetSubFolderNum())
	{
		cout << endl;
		cout << "\tDELETE FAIL !" << endl;
		return 0;
	}

	else if (pre> m_CurPointer.GetStackPointer()->GetSubFolderNum()) //이전 item개수보다 현재 item개수가 많아지면 제거성공
	{
		cout << endl;
		cout<<"\tDELETE SUCCESS !"<<endl;
		return 1;
	}
	cout << endl;
	cout<<"\tDELETE FAIL !"<<endl;
	return 0;
}

// 리스트에서 해당 name을 가진 file을 찾아 제거한다.
int Application::DeleteFile()
{
	int pre = m_CurPointer.GetStackPointer()->GetFileNum();//이전 item개수를 받아온다.

	cout << "\tEnter the name to delete." << endl;
	FileType file;
	file.SetNameFromKB();

	if (m_CurPointer.GetStackPointer()->DeleteFile(file) && pre == m_CurPointer.GetStackPointer()->GetFileNum())
	{
		cout << endl;
		cout << "\tDELETE FAIL !" << endl;
		return 0;
	}

	else if (pre> m_CurPointer.GetStackPointer()->GetFileNum()) //이전 item개수보다 현재 item개수가 많아지면 제거성공
	{
		cout << endl;
		cout << "\tDELETE SUCCESS !" << endl;

		//txt파일 삭제
		string strname = file.GetName() + ".txt";
		char name[100];
		strcpy(name, strname.c_str());
		if (remove(name) == 0) {}

		return 1;
	}
	cout << endl;
	cout << "\tDELETE FAIL !" << endl;
	return 0;
}

// 최근 열어본 폴더 리스트를 출력
void Application::DisplayRecent()
{
	cout << "\t---Recent Folders---" << endl;
	if (!m_RecentlyFolder.Display())
	{
		cout << "\tNo folders have been opened recently." << endl;
	}

	cout << "\t----Recent Files----" << endl;
	if (!m_RecentlyFile.Display())
	{
		cout << "\tNo files have been opened recently." << endl;
	}
}

// 현재 폴더의 속성을 출력
void Application::DisplayProperty()
{
	m_CurPointer.GetStackPointer()->DisplayRecordOnScreen();
}

// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	m_CurPointer.GetStackPointer()->DisplayAllFolderName();
	m_CurPointer.GetStackPointer()->DisplayAllFileName();
}


// 서브 폴더로 이동
int Application::MoveToFolder()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //서브 폴더가 없으면 return 0
	{
		cout << "\tThere are no folders to move." << endl;
		return 0;
	}

	cout << "\tEnter the name to move." << endl;
	data.SetNameFromKB(); //이동할 폴더의 이름 받음

	FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

	if (pointer==NULL)
	{
		cout << endl;
		cout << "\tFolder with name doesn't exist." << endl;
		return 0;
	}
	else
	{
		m_CurPointer.Push(pointer);
		cout << endl;
		cout << "\tMOVE TO SUBFOLDER SUCCESS !" << endl;
		//최근 열어본 폴더 목록에 추가
		data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//자주 열어본 폴더 목록에 추가
		m_visit.visit(pointer);
		return 1;
	}
}

// 뒤로 가기
int Application::MoveBack()
{
	if (!m_CurPointer.Pop())
	{
		cout << "\tThere is no parent folder to return to." << endl;
		return 0;
	}
	cout << "\tMOVE BACK SUCCESSFUL !" << endl;

	FolderType data;
	//자주 열어본 폴더 목록에 추가
	m_visit.visit(m_CurPointer.GetStackPointer());
	//최근 열어본 폴더 목록에 추가
	data = *(m_CurPointer.GetStackPointer());
	m_RecentlyFolder.Enqueue(data);
	return 1;
}

// 앞으로 가기
int Application::MoveFront()
{
	if (!m_CurPointer.DepthIncrease())
	{
		cout << "\tFAIL TO MOVE FRONT !" << endl;
		return 0;
	}
	cout << "\tMOVE FRONT SUCCESSFUL !" << endl;

	FolderType data;
	//자주 열어본 폴더 목록에 추가
	m_visit.visit(m_CurPointer.GetStackPointer());
	//최근 열어본 폴더 목록에 추가
	data = *(m_CurPointer.GetStackPointer());
	m_RecentlyFolder.Enqueue(data);
	return 1;
}


// 폴더 이름 바꾸기
int Application::ChangeFolderName()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //서브 폴더가 없으면 return 0
	{
		cout << "\tThere are no folders to change name." << endl;
		return 0;
	}

	cout << "\tEnter the name of the folder you want to rename." << endl;
	data.SetNameFromKB(); //이름을 바꿀 폴더의 이름 받음

	FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

	cout << endl;

	if (pointer == NULL)
	{
		cout << "\tFolder with name doesn't exist." << endl;
		return 0;
	}
	else
	{
		cout << "\tWhat name are you going to change?" << endl;
		//바꿀 이름이 기존 폴더의 이름에 있는지 확인
		FolderType data2;
		data2.SetNameFromKB();
		FolderType* pointer2 = m_CurPointer.GetStackPointer()->GetFolderPointer(data2);
		if (pointer2 != NULL)// 기존 폴더에 이미 바꿀 이름이 있으면
		{
			cout << "\tFolder with that name exists." << endl;
			return 0;
		}
		cout << endl;

		// 순서 바꾸는 함수 실행
		FolderType buf = *pointer;
		m_CurPointer.GetStackPointer()->DeleteFolder(*pointer);
		buf.SetName(data2.GetName());
		m_CurPointer.GetStackPointer()->AddFolder(buf);
		pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(buf);

		// 경로 바꾸는 함수 실행
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + buf.GetName());
		pointer->ChangeUnderPath(buf.GetPath());
		cout << "\tCHANGE SUCCESS !" << endl;
		return 1;
	}
}

// 파일 이름 바꾸기
int Application::ChangeFileName()
{
	FileType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //파일이 없으면 return 0
	{
		cout << "\tThere are no files to change name." << endl;
		return 0;
	}

	cout << "\tEnter the name of the file you want to rename." << endl;
	data.SetNameFromKB(); //이름을 바꿀 파일의 이름 받음

	FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

	cout << endl;

	if (pointer == NULL)// 기존 파일에 이미 바꿀 이름이 있으면
	{
		cout << "\tFile with name doesn't exist." << endl;
		return 0;
	}
	else
	{
		cout << "\tWhat name are you going to change?" << endl;
		//바꿀 이름이 기존 파일의 이름에 있는지 확인
		FileType data2;
		data2.SetNameFromKB();
		FileType* pointer2 = m_CurPointer.GetStackPointer()->GetFilePointer(data2);
		if (pointer2!=NULL)
		{
			cout<< "\tFile with that name exists." <<endl;
			return 0;
		}
		cout << endl;

		//txt파일 이름 변경
		string oldstr = (data.GetName() + ".txt");
		string newstr = (data2.GetName() + ".txt");
		const char* oldchar = oldstr.c_str();
		const char* newchar = newstr.c_str();

		if (rename(oldchar, newchar) == 0) {}

		// 순서 바꾸는 함수 실행
		FileType buf = *pointer;
		m_CurPointer.GetStackPointer()->DeleteFile(data);
		buf.SetName(data2.GetName());
		m_CurPointer.GetStackPointer()->AddFile(buf);
		pointer = m_CurPointer.GetStackPointer()->GetFilePointer(buf);;

		//파일 경로 재설정
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + pointer->GetName());
		cout << "\tCHANGE SUCCESS !" << endl;
		return 1;
	}
}

// 원하는 파일을 열어 내용 작성
int Application::OpenFile()
{
	FileType file;
	cout << "\tEnter the name to open." << endl;
	file.SetNameFromKB(); //열 파일의 이름 받음

	if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //파일이 없으면 return 0
	{
		cout << "\tThere are no files to open." << endl;
		return 0;
	}


	FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(file);

	if (pointer == NULL)
	{
		cout << endl;
		cout << "\tFile with name doesn't exist." << endl;
		return 0;
	}

	if (!pointer->OpenThis())
		return 0;

	//최근 열어본 파일 리스트에 추가
	m_RecentlyFile.Enqueue(*pointer);
	return 1;
}

// 폴더나 파일 잘라내기
int Application::Cut()
{
	string str;
	cout << "\tWhat are you going to cut ? (Enter 'folder' or 'file') : ";
	cin >> str;

	if (str=="folder")
	{
		FolderType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //서브 폴더가 없으면 return 0
		{
			cout << "\tThere are no folders to cut." << endl;
			return 0;
		}

		cout << "\tEnter the name to cut." << endl;
		cin.ignore();
		data.SetNameFromKB(); //삭제할 폴더의 이름 받음

		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

		if (pointer == NULL)//해당 폴더가 없으면
		{
			cout << endl;
			cout << "\tFolder with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder에 현재 폴더의 포인터 복사
			clipboard.iscut = 1;
			clipboard.clipFile = NULL;
			clipboard.clipFolder = pointer;
			cout << "\tCUT SUCCESS !" << endl;
			return 1;
		}
	}
	
	if (str == "file")
	{
		FileType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //파일이 없으면 return 0
		{
			cout << "\tThere are no files to cut." << endl;
			return 0;
		}

		cout << "\tEnter the name to cut." << endl;
		cin.ignore();
		data.SetNameFromKB(); //잘라낼 파일의 이름 받음

		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

		if (pointer == NULL)//해당 파일이 없으면
		{
			cout << endl;
			cout << "\tFile with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder에 현재 폴더의 포인터 복사
			clipboard.iscut = 1;
			clipboard.clipFolder = NULL;
			clipboard.clipFile = pointer;
			cout << "\tCUT SUCCESS !" << endl;

			return 1;
		}
	}
	else
	{
		cout << "\tYou didn't enter 'folder' or 'file' !" << endl;
		return 0;
	}
}

// 폴더나 파일 복사
int Application::Copy()
{
	string str;
	cout << "\tWhat are you going to copy ? (Enter 'folder' or 'file') : ";
	cin >> str;

	if (str == "folder")
	{
		FolderType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //서브 폴더가 없으면 return 0
		{
			cout << "\tThere are no folders to copy." << endl;
			return 0;
		}

		cout << "\tEnter the name to copy." << endl;
		cin.ignore();
		data.SetNameFromKB(); //복사할 폴더의 이름 받음

		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

		if (pointer == NULL)//해당 폴더가 없으면
		{
			cout << endl;
			cout << "\tFolder with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder에 현재 폴더의 포인터 복사
			clipboard.iscut = 0;
			clipboard.clipFile = NULL;
			clipboard.clipFolder = pointer;
			cout << "\tCOPY SUCCESS !" << endl;
			return 1;
		}
	}

	if (str == "file")
	{
		FileType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //파일이 없으면 return 0
		{
			cout << "\tThere are no files to copy." << endl;
			return 0;
		}

		cout << "\tEnter the name to copy." << endl;
		cin.ignore();
		data.SetNameFromKB(); //삭제할 파일의 이름 받음

		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

		if (pointer == NULL)//해당 파일이 없으면
		{
			cout << endl;
			cout << "\tFile with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder에 현재 폴더의 포인터 복사
			clipboard.iscut = 0;
			clipboard.clipFolder = NULL;
			clipboard.clipFile = pointer;
			cout << "\tCOPY SUCCESS !" << endl;

			return 1;
		}
	}
	else
	{
		cout << "\tYou didn't enter 'folder' or 'file' !" << endl;
		return 0;
	}
}

// 폴더나 파일 붙여넣기
int Application::Paste()
{
	if (clipboard.clipFile==NULL && clipboard.clipFolder==NULL) //데이터가 없으면
	{
		cout<<"\tYou can't paste !"<<endl;
		return 0;
	}
	else if (clipboard.clipFile!=NULL) //clipFile데이터가 있으면
	{
		string name = clipboard.clipFile->GetName();
		FileType*f = new FileType(*clipboard.clipFile);
		for (int i = 0; !m_CurPointer.GetStackPointer()->AddFile(*f); i++)
		{			
			//같은 이름 있으면 이름 바꿔 추가
			f->SetName(name + "(" + to_string(i + 2) + ")");//이름 바꿔 추가
		}
		// 파일 경로 바꾸기
		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(*f);
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + f->GetName());

		if (clipboard.iscut==1) //잘라내기한 데이터면
		{
			clipboard.parentFolder->DeleteFile(*clipboard.clipFile); //기존에 있던 폴더에서 delete
			clipboard.clipFile = NULL;
		}
	}
	else //clipFolder데이터가 있으면
	{

		string name = clipboard.clipFolder->GetName();
		FolderType*f = new FolderType(*clipboard.clipFolder);
		for (int i = 0; !m_CurPointer.GetStackPointer()->AddFolder(*f); i++)
		{
			//같은 이름 있으면 이름 바꿔 추가
			f->SetName(name + "(" + to_string(i + 2) + ")");
		}
		// 경로 바꾸기
		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(*f);
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + pointer->GetName());
		pointer->ChangeUnderPath(pointer->GetPath());

		if (clipboard.iscut==1) //잘라내기한 데이터면
		{
			clipboard.parentFolder->DeleteFolder(*clipboard.clipFolder); //기존에 있던 폴더에서 delete
			clipboard.clipFolder = NULL;
		}
	}
	return 1;
}

// 자주 열어본 폴더 출력하기
void Application::PopularFolderPrint() {
	int count;

	if (this->m_visit.m_Length < 5)
		count = this->m_visit.m_Length;
	else
		count = 5;

	for (int i = 0; i < count; i++)
	{
		cout <<"\t"<< i + 1 << "위 : ";
		this->m_visit.m_arr[i].ptr->DisplayName();
		cout << "\t조회수 : " << this->m_visit.m_arr[i].visit << endl << endl;
	}
}

// 입력한 경로의 폴더로 이동
void Application::MoveToFolderByPath()
{
	string path;
	string name;
	cout << "\t Enter the path to move : ";
	cin >> path;
	FolderType* pointer = &m_RootFolder;
	FolderType folder;

	if (path.substr(0,5)!="/Root")// 처음 경로가 root폴더가 아닐 경우
	{
		cout << "\tInvalid Path" << endl;
		return;
	}
	else if (path=="/Root") //경로가 root폴더일 경우
	{
		m_CurPointer.Push(pointer);
		cout << endl;
		cout << "\tMOVE TO SUBFOLDER SUCCESS !" << endl;
		//최근 열어본 폴더 목록에 추가
		FolderType data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//자주 열어본 폴더 목록에 추가
		m_visit.visit(pointer);

		return;
	}

	path = path.substr(5, path.size() - 5);

	while (pointer!=NULL)
	{
		path = path.substr(1, path.size() - 1);
		if (path.find("/")!=string::npos) // "/"가 있으면
		{
			name = path.substr(0, path.find("/"));
			path = path.substr(path.find("/"), path.size() - path.find("/"));
			folder.SetName(name);
			pointer = pointer->GetFolderPointer(folder);
		}
		else
		{
			folder.SetName(path);
			pointer = pointer->GetFolderPointer(folder);
			break;
		}
	}

	if (pointer!=NULL) //해당 경로를 가진 폴더가 있을 경우
	{
		m_CurPointer.Push(pointer);
		cout << endl;
		cout << "\tMOVE TO FOLDER SUCCESS !" << endl;
		//최근 열어본 폴더 목록에 추가
		FolderType data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//자주 열어본 폴더 목록에 추가
		m_visit.visit(pointer);
	}

	else
	{
		cout << "\tInvalid Path" << endl;
	}
}

// 바로가기 목록 중 원하는 폴더로 이동
void Application::MoveToFolderQuickly()
{
	cout << endl;
	string name;
	FolderType* pointer;

	if (fdPointerList.IsEmpty())
	{
		cout << "\tThere is no folder." << endl;
		return;
	}

	fdPointerList.ResetList();
	fdPointerList.GetNextItem(pointer);

	for (int i = 1; pointer!=NULL; i++)
	{
		cout << "\t" << i << ". " << *pointer << endl;
		fdPointerList.GetNextItem(pointer);
	}
	cout << endl;

	cout << "\tEnter the folder name to move : ";
	cin >> name;

	fdPointerList.GetNextItem(pointer);
	while (pointer!=NULL)
	{
		if (pointer->GetName()==name)
		{
			m_CurPointer.Push(pointer);
			cout << endl;
			cout << "\tMOVE TO FOLDER SUCCESS !" << endl;

			//최근 열어본 폴더 목록에 추가
			FolderType data = *(m_CurPointer.GetStackPointer());
			m_RecentlyFolder.Enqueue(data);

			//자주 열어본 폴더 목록에 추가
			m_visit.visit(pointer);

			return;
		}

		fdPointerList.GetNextItem(pointer);
	}

	cout << "\tFolder with name doesn't exist." << endl;
	
}

// 원하는 폴더를 바로가기 목록에 추가
void Application::AddFolderToList()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //서브 폴더가 없으면 return 0
	{
		cout << "\tThere are no folders to add." << endl;
		return;
	}

	cout << "\tEnter the name to add." << endl;
	data.SetNameFromKB(); //추가할 폴더의 이름 받음

	FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

	if (pointer == NULL)
	{
		cout << endl;
		cout << "\tFolder with name doesn't exist." << endl;
	}
	else
	{
		fdPointerList.Add(pointer);
		cout << endl;
		cout << "\tAdd Folder To List !" << endl;
	}
}