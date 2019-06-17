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
		case 1:		// �� ���� ����
			NewFolder();
			break;
		case 2:		// �� ���� ����
			NewFile();
			break;
		case 3:		// ���� ���� ����
			DeleteFolder();
			break;
		case 4:		// ���� ����
			DeleteFile();
			break;
		case 5:		// ���� �̸� �ٲٱ�
			ChangeFolderName();
			break;
		case 6:		// ���� �̸� �ٲٱ�
			ChangeFileName();
			break;
		case 7:		// ���� ������ �̵�
			MoveToFolder();
			break;
		case 8:		// ���� ����
			OpenFile();
			break;
		case 9:		// ��� ����, ���� �˻�
			RetriveAllByName();
			break;
		case 10:	// ��� Ž��
			MoveToFolderByPath();
			break;
		case 11:	// �ֱ� ��� ����,���� ���
			DisplayRecent();
			break;
		case 12:	// ���� ��� ���� ���
			PopularFolderPrint();
			break;
		case 13:	// ���� ������ �Ӽ��� ���
			DisplayProperty();
			break;
		case 14:	// �ڷ� ����
			MoveBack();
			break;
		case 15:	// ������ ����
			MoveFront();
			break;
		case 16:	// �߶󳻱�
			Cut();
			break;
		case 17:	// ����
			Copy();
			break;
		case 18:	// �ٿ��ֱ�
			Paste();
			break;
		case 19:	// �ٷΰ��� ���
			MoveToFolderQuickly();
			break;
		case 20:	// �ٷΰ��� ��Ͽ� ���� �߰�
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
	cout << "\t   1 : �� ���� ����" << endl;
	cout << "\t   2 : �� ���� ����" << endl;
	cout << "\t   3 : ���� ���� ����" << endl;
	cout << "\t   4 : ���� ����" << endl;
	cout << "\t   5 : ���� ���� �̸� �ٲٱ�" << endl;
	cout << "\t   6 : ���� �̸� �ٲٱ�" << endl;
	cout << "\t   7 : ���� ���� �̵�" << endl;
	cout << "\t   8 : ���� ����" << endl;
	cout << "\t   9 : ����, ���� Ű���� �˻�" << endl;
	cout << "\t   10 : �Է��� ����� ������ �̵�" << endl;
	cout << "\t   11 : �ֱ� ��� ����, ����" << endl;
	cout << "\t   12 : ���� ��� ����" << endl;
	cout << "\t   13 : ���� ���� �Ӽ�" << endl;
	cout << "\t   14 : �ڷ� ����" << endl;
	cout << "\t   15 : ������ ����" << endl;
	cout << "\t   16 : �߶󳻱�" << endl;
	cout << "\t   17 : ����" << endl;
	cout << "\t   18 : �ٿ��ֱ�" << endl;
	cout << "\t   19 : �ٷΰ��� ���" << endl;
	cout << "\t   20 : �ٷΰ��� ��Ͽ� ���� �߰�" << endl;
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


// ���� ���� ������ �ش� keyword�� ���� �����͸� ã�� ����Ѵ�.
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

// ����Ʈ���� �ش� name�� ���� folder�� ã�� �����Ѵ�.
int Application::DeleteFolder()
{
	int pre = m_CurPointer.GetStackPointer()->GetSubFolderNum();//���� item������ �޾ƿ´�.

	cout << "\tEnter the name to delete." << endl;

	FolderType folder;
	folder.SetNameFromKB();

	if (m_CurPointer.GetStackPointer()->DeleteFolder(folder) && pre == m_CurPointer.GetStackPointer()->GetSubFolderNum())
	{
		cout << endl;
		cout << "\tDELETE FAIL !" << endl;
		return 0;
	}

	else if (pre> m_CurPointer.GetStackPointer()->GetSubFolderNum()) //���� item�������� ���� item������ �������� ���ż���
	{
		cout << endl;
		cout<<"\tDELETE SUCCESS !"<<endl;
		return 1;
	}
	cout << endl;
	cout<<"\tDELETE FAIL !"<<endl;
	return 0;
}

// ����Ʈ���� �ش� name�� ���� file�� ã�� �����Ѵ�.
int Application::DeleteFile()
{
	int pre = m_CurPointer.GetStackPointer()->GetFileNum();//���� item������ �޾ƿ´�.

	cout << "\tEnter the name to delete." << endl;
	FileType file;
	file.SetNameFromKB();

	if (m_CurPointer.GetStackPointer()->DeleteFile(file) && pre == m_CurPointer.GetStackPointer()->GetFileNum())
	{
		cout << endl;
		cout << "\tDELETE FAIL !" << endl;
		return 0;
	}

	else if (pre> m_CurPointer.GetStackPointer()->GetFileNum()) //���� item�������� ���� item������ �������� ���ż���
	{
		cout << endl;
		cout << "\tDELETE SUCCESS !" << endl;

		//txt���� ����
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

// �ֱ� ��� ���� ����Ʈ�� ���
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

// ���� ������ �Ӽ��� ���
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


// ���� ������ �̵�
int Application::MoveToFolder()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //���� ������ ������ return 0
	{
		cout << "\tThere are no folders to move." << endl;
		return 0;
	}

	cout << "\tEnter the name to move." << endl;
	data.SetNameFromKB(); //�̵��� ������ �̸� ����

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
		//�ֱ� ��� ���� ��Ͽ� �߰�
		data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//���� ��� ���� ��Ͽ� �߰�
		m_visit.visit(pointer);
		return 1;
	}
}

// �ڷ� ����
int Application::MoveBack()
{
	if (!m_CurPointer.Pop())
	{
		cout << "\tThere is no parent folder to return to." << endl;
		return 0;
	}
	cout << "\tMOVE BACK SUCCESSFUL !" << endl;

	FolderType data;
	//���� ��� ���� ��Ͽ� �߰�
	m_visit.visit(m_CurPointer.GetStackPointer());
	//�ֱ� ��� ���� ��Ͽ� �߰�
	data = *(m_CurPointer.GetStackPointer());
	m_RecentlyFolder.Enqueue(data);
	return 1;
}

// ������ ����
int Application::MoveFront()
{
	if (!m_CurPointer.DepthIncrease())
	{
		cout << "\tFAIL TO MOVE FRONT !" << endl;
		return 0;
	}
	cout << "\tMOVE FRONT SUCCESSFUL !" << endl;

	FolderType data;
	//���� ��� ���� ��Ͽ� �߰�
	m_visit.visit(m_CurPointer.GetStackPointer());
	//�ֱ� ��� ���� ��Ͽ� �߰�
	data = *(m_CurPointer.GetStackPointer());
	m_RecentlyFolder.Enqueue(data);
	return 1;
}


// ���� �̸� �ٲٱ�
int Application::ChangeFolderName()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //���� ������ ������ return 0
	{
		cout << "\tThere are no folders to change name." << endl;
		return 0;
	}

	cout << "\tEnter the name of the folder you want to rename." << endl;
	data.SetNameFromKB(); //�̸��� �ٲ� ������ �̸� ����

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
		//�ٲ� �̸��� ���� ������ �̸��� �ִ��� Ȯ��
		FolderType data2;
		data2.SetNameFromKB();
		FolderType* pointer2 = m_CurPointer.GetStackPointer()->GetFolderPointer(data2);
		if (pointer2 != NULL)// ���� ������ �̹� �ٲ� �̸��� ������
		{
			cout << "\tFolder with that name exists." << endl;
			return 0;
		}
		cout << endl;

		// ���� �ٲٴ� �Լ� ����
		FolderType buf = *pointer;
		m_CurPointer.GetStackPointer()->DeleteFolder(*pointer);
		buf.SetName(data2.GetName());
		m_CurPointer.GetStackPointer()->AddFolder(buf);
		pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(buf);

		// ��� �ٲٴ� �Լ� ����
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + buf.GetName());
		pointer->ChangeUnderPath(buf.GetPath());
		cout << "\tCHANGE SUCCESS !" << endl;
		return 1;
	}
}

// ���� �̸� �ٲٱ�
int Application::ChangeFileName()
{
	FileType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //������ ������ return 0
	{
		cout << "\tThere are no files to change name." << endl;
		return 0;
	}

	cout << "\tEnter the name of the file you want to rename." << endl;
	data.SetNameFromKB(); //�̸��� �ٲ� ������ �̸� ����

	FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

	cout << endl;

	if (pointer == NULL)// ���� ���Ͽ� �̹� �ٲ� �̸��� ������
	{
		cout << "\tFile with name doesn't exist." << endl;
		return 0;
	}
	else
	{
		cout << "\tWhat name are you going to change?" << endl;
		//�ٲ� �̸��� ���� ������ �̸��� �ִ��� Ȯ��
		FileType data2;
		data2.SetNameFromKB();
		FileType* pointer2 = m_CurPointer.GetStackPointer()->GetFilePointer(data2);
		if (pointer2!=NULL)
		{
			cout<< "\tFile with that name exists." <<endl;
			return 0;
		}
		cout << endl;

		//txt���� �̸� ����
		string oldstr = (data.GetName() + ".txt");
		string newstr = (data2.GetName() + ".txt");
		const char* oldchar = oldstr.c_str();
		const char* newchar = newstr.c_str();

		if (rename(oldchar, newchar) == 0) {}

		// ���� �ٲٴ� �Լ� ����
		FileType buf = *pointer;
		m_CurPointer.GetStackPointer()->DeleteFile(data);
		buf.SetName(data2.GetName());
		m_CurPointer.GetStackPointer()->AddFile(buf);
		pointer = m_CurPointer.GetStackPointer()->GetFilePointer(buf);;

		//���� ��� �缳��
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + pointer->GetName());
		cout << "\tCHANGE SUCCESS !" << endl;
		return 1;
	}
}

// ���ϴ� ������ ���� ���� �ۼ�
int Application::OpenFile()
{
	FileType file;
	cout << "\tEnter the name to open." << endl;
	file.SetNameFromKB(); //�� ������ �̸� ����

	if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //������ ������ return 0
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

	//�ֱ� ��� ���� ����Ʈ�� �߰�
	m_RecentlyFile.Enqueue(*pointer);
	return 1;
}

// ������ ���� �߶󳻱�
int Application::Cut()
{
	string str;
	cout << "\tWhat are you going to cut ? (Enter 'folder' or 'file') : ";
	cin >> str;

	if (str=="folder")
	{
		FolderType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //���� ������ ������ return 0
		{
			cout << "\tThere are no folders to cut." << endl;
			return 0;
		}

		cout << "\tEnter the name to cut." << endl;
		cin.ignore();
		data.SetNameFromKB(); //������ ������ �̸� ����

		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

		if (pointer == NULL)//�ش� ������ ������
		{
			cout << endl;
			cout << "\tFolder with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder�� ���� ������ ������ ����
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

		if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //������ ������ return 0
		{
			cout << "\tThere are no files to cut." << endl;
			return 0;
		}

		cout << "\tEnter the name to cut." << endl;
		cin.ignore();
		data.SetNameFromKB(); //�߶� ������ �̸� ����

		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

		if (pointer == NULL)//�ش� ������ ������
		{
			cout << endl;
			cout << "\tFile with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder�� ���� ������ ������ ����
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

// ������ ���� ����
int Application::Copy()
{
	string str;
	cout << "\tWhat are you going to copy ? (Enter 'folder' or 'file') : ";
	cin >> str;

	if (str == "folder")
	{
		FolderType data;
		cout << endl;

		if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //���� ������ ������ return 0
		{
			cout << "\tThere are no folders to copy." << endl;
			return 0;
		}

		cout << "\tEnter the name to copy." << endl;
		cin.ignore();
		data.SetNameFromKB(); //������ ������ �̸� ����

		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(data);

		if (pointer == NULL)//�ش� ������ ������
		{
			cout << endl;
			cout << "\tFolder with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder�� ���� ������ ������ ����
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

		if (m_CurPointer.GetStackPointer()->GetFileNum() == 0) //������ ������ return 0
		{
			cout << "\tThere are no files to copy." << endl;
			return 0;
		}

		cout << "\tEnter the name to copy." << endl;
		cin.ignore();
		data.SetNameFromKB(); //������ ������ �̸� ����

		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(data);

		if (pointer == NULL)//�ش� ������ ������
		{
			cout << endl;
			cout << "\tFile with name doesn't exist." << endl;
			return 0;
		}
		else
		{
			cout << endl;
			clipboard.parentFolder = m_CurPointer.GetStackPointer();//parentFolder�� ���� ������ ������ ����
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

// ������ ���� �ٿ��ֱ�
int Application::Paste()
{
	if (clipboard.clipFile==NULL && clipboard.clipFolder==NULL) //�����Ͱ� ������
	{
		cout<<"\tYou can't paste !"<<endl;
		return 0;
	}
	else if (clipboard.clipFile!=NULL) //clipFile�����Ͱ� ������
	{
		string name = clipboard.clipFile->GetName();
		FileType*f = new FileType(*clipboard.clipFile);
		for (int i = 0; !m_CurPointer.GetStackPointer()->AddFile(*f); i++)
		{			
			//���� �̸� ������ �̸� �ٲ� �߰�
			f->SetName(name + "(" + to_string(i + 2) + ")");//�̸� �ٲ� �߰�
		}
		// ���� ��� �ٲٱ�
		FileType* pointer = m_CurPointer.GetStackPointer()->GetFilePointer(*f);
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + f->GetName());

		if (clipboard.iscut==1) //�߶󳻱��� �����͸�
		{
			clipboard.parentFolder->DeleteFile(*clipboard.clipFile); //������ �ִ� �������� delete
			clipboard.clipFile = NULL;
		}
	}
	else //clipFolder�����Ͱ� ������
	{

		string name = clipboard.clipFolder->GetName();
		FolderType*f = new FolderType(*clipboard.clipFolder);
		for (int i = 0; !m_CurPointer.GetStackPointer()->AddFolder(*f); i++)
		{
			//���� �̸� ������ �̸� �ٲ� �߰�
			f->SetName(name + "(" + to_string(i + 2) + ")");
		}
		// ��� �ٲٱ�
		FolderType* pointer = m_CurPointer.GetStackPointer()->GetFolderPointer(*f);
		pointer->SetPath(m_CurPointer.GetStackPointer()->GetPath() + "/" + pointer->GetName());
		pointer->ChangeUnderPath(pointer->GetPath());

		if (clipboard.iscut==1) //�߶󳻱��� �����͸�
		{
			clipboard.parentFolder->DeleteFolder(*clipboard.clipFolder); //������ �ִ� �������� delete
			clipboard.clipFolder = NULL;
		}
	}
	return 1;
}

// ���� ��� ���� ����ϱ�
void Application::PopularFolderPrint() {
	int count;

	if (this->m_visit.m_Length < 5)
		count = this->m_visit.m_Length;
	else
		count = 5;

	for (int i = 0; i < count; i++)
	{
		cout <<"\t"<< i + 1 << "�� : ";
		this->m_visit.m_arr[i].ptr->DisplayName();
		cout << "\t��ȸ�� : " << this->m_visit.m_arr[i].visit << endl << endl;
	}
}

// �Է��� ����� ������ �̵�
void Application::MoveToFolderByPath()
{
	string path;
	string name;
	cout << "\t Enter the path to move : ";
	cin >> path;
	FolderType* pointer = &m_RootFolder;
	FolderType folder;

	if (path.substr(0,5)!="/Root")// ó�� ��ΰ� root������ �ƴ� ���
	{
		cout << "\tInvalid Path" << endl;
		return;
	}
	else if (path=="/Root") //��ΰ� root������ ���
	{
		m_CurPointer.Push(pointer);
		cout << endl;
		cout << "\tMOVE TO SUBFOLDER SUCCESS !" << endl;
		//�ֱ� ��� ���� ��Ͽ� �߰�
		FolderType data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//���� ��� ���� ��Ͽ� �߰�
		m_visit.visit(pointer);

		return;
	}

	path = path.substr(5, path.size() - 5);

	while (pointer!=NULL)
	{
		path = path.substr(1, path.size() - 1);
		if (path.find("/")!=string::npos) // "/"�� ������
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

	if (pointer!=NULL) //�ش� ��θ� ���� ������ ���� ���
	{
		m_CurPointer.Push(pointer);
		cout << endl;
		cout << "\tMOVE TO FOLDER SUCCESS !" << endl;
		//�ֱ� ��� ���� ��Ͽ� �߰�
		FolderType data = *(m_CurPointer.GetStackPointer());
		m_RecentlyFolder.Enqueue(data);

		//���� ��� ���� ��Ͽ� �߰�
		m_visit.visit(pointer);
	}

	else
	{
		cout << "\tInvalid Path" << endl;
	}
}

// �ٷΰ��� ��� �� ���ϴ� ������ �̵�
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

			//�ֱ� ��� ���� ��Ͽ� �߰�
			FolderType data = *(m_CurPointer.GetStackPointer());
			m_RecentlyFolder.Enqueue(data);

			//���� ��� ���� ��Ͽ� �߰�
			m_visit.visit(pointer);

			return;
		}

		fdPointerList.GetNextItem(pointer);
	}

	cout << "\tFolder with name doesn't exist." << endl;
	
}

// ���ϴ� ������ �ٷΰ��� ��Ͽ� �߰�
void Application::AddFolderToList()
{
	FolderType data;
	cout << endl;

	if (m_CurPointer.GetStackPointer()->GetSubFolderNum() == 0) //���� ������ ������ return 0
	{
		cout << "\tThere are no folders to add." << endl;
		return;
	}

	cout << "\tEnter the name to add." << endl;
	data.SetNameFromKB(); //�߰��� ������ �̸� ����

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