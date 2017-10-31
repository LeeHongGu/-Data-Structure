#include "BookList.h"

BookList::BookList(char* source) : SEPARATOR(' ')
{
	ifstream ifs(source);
	path = source;

	head.nextBook = &head;
	head.prevBook = &head;

	while(ifs.fail())
	{
		cout << "�Է¹��� ������ �����ϴ�. ���Է� : ";
		cin >> path;

		ifs.open(path);
	}

	while (!ifs.eof()) 
	{
		string buffer;
		getline(ifs, buffer);

		if (buffer.find(SEPARATOR) == string::npos)
			continue;

		Book* newBook = new Book;
		newBook->code = buffer.substr(0, buffer.find_first_of(SEPARATOR));
		buffer = buffer.substr(buffer.find_first_of(SEPARATOR), buffer.length());
		newBook->name = buffer.substr(buffer.find_first_not_of(SEPARATOR), buffer.length());

		appendBook(newBook);
	}

	ifs.close();
}

BookList::~BookList()
{
	Book* curBook = head.nextBook;
	Book* nextTemp = NULL;

	while (curBook != &head)
	{
		nextTemp = curBook->nextBook;

		delete curBook;

		curBook = nextTemp;
	}
}

void BookList::showMenu()
{
	enum MENU { APPEND = '1', DELETE, PRT_ALL, PRT_ALL_REV, PRT_PART_ALL, PRT_PART_REV, EXIT };
	string name;
	char type = 0;

	cout << "==========================================\n";
	cout << "(1) �� ���� �Է�\n";
	cout << "(2) ���� ����\n";
	cout << "(3) ������ ������ ��ü ���\n";
	cout << "(4) ������ �������� ��ü ���\n";
	cout << "(5) Ư�� ��������� ��ü ���\n";
	cout << "(6) Ư�� ��������� ù��������� ���� ���\n";
	cout << "(7) ���Ͽ� �����ϰ� ����\n";
	cout << "==========================================\n";

	while (type != EXIT)
	{
		cout << "���ϴ� ����� �����ϼ��� : ";
		cin >> type;

		switch (type)
		{
		case APPEND: appendBook(); break;
		case DELETE: deleteBook(); break;
		case PRT_ALL: print(); break;
		case PRT_ALL_REV: printRev(); break;

		case PRT_PART_ALL: 
			cout << "�������� �Է��ϼ��� : ";
			cin.ignore();
			getline(cin, name);
			print(name);
			break;

		case PRT_PART_REV:
			cout << "�������� �Է��ϼ��� : ";
			cin.ignore();
			getline(cin, name);
			printRev(name);
			break;

		case EXIT: save(); break;
		default: break;
		}
	}
	cout << "�����մϴ�." << endl;
}

Book* BookList::setNewBook()
{
	Book* newBook;

	string buffer;
	newBook = new Book;

	cout << "������ȣ�� �������� �Է��ϼ��� : ";
	cin.ignore();
	getline(cin, buffer);

	if (buffer.find(SEPARATOR) == string::npos)
		return NULL;

	newBook->code = buffer.substr(0, buffer.find_first_of(SEPARATOR));
	newBook->name = buffer.substr(buffer.find_first_of(SEPARATOR) + 1, buffer.length());

	return newBook;
}

void BookList::appendBook(Book* newBook)
{
	Book* curBook = head.nextBook;

	if (!newBook)
	{
		newBook = setNewBook();

		if (!newBook)
		{
			cout << "\n�ùٸ��� ���� ������ �Է��Դϴ�." << endl;
			return;
		}
	}

	while(curBook != &head)
	{
		if (newBook->name < curBook->name)
			break;

		curBook = curBook->nextBook;
	}

	newBook->nextBook = curBook;
	newBook->prevBook = curBook->prevBook;

	curBook->prevBook->nextBook = newBook; 
	curBook->prevBook = newBook;
}

void BookList::deleteBook()
{
	Book* curBook = head.nextBook;
	string target;

	cout << "������ȣ�� �Է��ϼ��� : ";
	cin >> target;

	while(curBook != &head)
	{
		if (curBook->code == target)
		{
			curBook->prevBook->nextBook = curBook->nextBook;
			curBook->nextBook->prevBook = curBook->prevBook;

			delete curBook;
			return;
		}

		curBook = curBook->nextBook;
	}

	cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::print(string indexName)
{
	bool print = false;
	if (indexName == "")
		print = true;

	Book* curBook = head.nextBook;
	Book* last = &head;

	while(curBook != last)
	{
		if (curBook->name == indexName)
		{
			print = true;
			last = curBook;
		}

		if (print && curBook != &head)
			cout << *curBook;

		curBook = curBook->nextBook;
	}

	if (!print)
		cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::printRev(string indexName)
{
	bool print = false;
	if (indexName == "")
		print = true;

	Book* curBook = head.prevBook;
	while(curBook != &head)
	{
		if (curBook->name == indexName)
			print = true;

		if (print)
			cout << *curBook;

		curBook = curBook->prevBook;
	}

	if (!print)
		cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::save()
{
	ofstream ofs;
	ofs.open(path);

	Book* curBook = head.nextBook;
	while (curBook != &head)
	{
		ofs << curBook->code << SEPARATOR << curBook->name << endl;

		curBook = curBook->nextBook;
	}

	ofs.close();
}