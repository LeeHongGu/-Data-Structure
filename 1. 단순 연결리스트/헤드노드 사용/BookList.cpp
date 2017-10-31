#include "BookList.h"

BookList::BookList(char* source) : SEPARATOR(' ')
{
	ifstream ifs(source);
	path = source;

	while (ifs.fail())
	{
		cout << "! �Է¹��� ������ �����ϴ�. ���Է� : ";
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

	while (curBook)
	{
		nextTemp = curBook->nextBook;

		delete curBook;

		curBook = nextTemp;
	}
}

void BookList::showMenu()
{
	enum MENU { APPEND = '1', DELETE, PRINT, EXIT };
	char type = 0;

	cout << "==========================================\n";
	cout << "(1) �� ���� �Է�\n";
	cout << "(2) ���� ����\n";
	cout << "(3) ������ ������ ��ü ���\n";
	cout << "(4) ���Ͽ� �����ϰ� ����\n";
	cout << "==========================================\n";

	while (type != EXIT)
	{
		cout << "���ϴ� ����� �����ϼ��� : ";
		cin >> type;

		switch (type)
		{
		case APPEND: appendBook(); break;
		case DELETE: deleteBook(); break;
		case PRINT: print(); break;
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
	newBook->name = buffer.substr(buffer.find_first_of(SEPARATOR)+1, buffer.length());

	return newBook;
}

void BookList::appendBook(Book* newBook)
{
	Book* curBook = head.nextBook;
	Book* preBook = &head;

	if (!newBook)
	{
		newBook = setNewBook();

		if (!newBook)
		{
			cout << "\n�ùٸ��� ���� ������ �Է��Դϴ�." << endl;
			return;
		}
	}

	while (curBook)
	{
		if (newBook->name < curBook->name)
			break;

		preBook = curBook;
		curBook = curBook->nextBook;
	}

	preBook->nextBook = newBook;
	newBook->nextBook = curBook;
}

void BookList::deleteBook()
{
	Book* curBook = head.nextBook;
	Book* preBook = &head;
	string target;

	cout << "������ȣ�� �Է��ϼ��� : ";
	cin >> target;

	while (curBook)
	{
		if (curBook->code == target)
		{
			preBook->nextBook = curBook->nextBook;
			delete curBook;

			return;
		}

		preBook = curBook;
		curBook = curBook->nextBook;
	}

	cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::print()
{
	Book* curBook = head.nextBook;

	while (curBook)
	{
		cout << *curBook;
		curBook = curBook->nextBook;
	}
}

void BookList::save()
{
	ofstream ofs;
	ofs.open(path);

	Book* curBook = head.nextBook;
	while (curBook)
	{
		ofs << curBook->code << SEPARATOR << curBook->name << endl;
		curBook = curBook->nextBook;
	}

	ofs.close();
}