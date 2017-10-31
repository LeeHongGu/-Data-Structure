#include "BookList.h"

BookList::BookList(char* source) :SEPARATOR(' ')
{
	ifstream ifs(source);
	path = source;
	head = NULL;

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
	if (head)
	{
		Book* curBook = head->nextBook;
		Book* nextTemp = NULL;

		while (curBook != head)
		{
			nextTemp = curBook->nextBook;

			delete curBook;

			curBook = nextTemp;
		}

		delete head;
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
	Book* curBook = head;

	if (!newBook)
	{
		newBook = setNewBook();

		if (!newBook)
		{
			cout << "\n�ùٸ��� ���� ������ �Է��Դϴ�." << endl;
			return;
		}
	}

	if (!head)
	{
		head = newBook;
		head->nextBook = head;
		head->prevBook = head;
		return;
	}

	// �ٽ� ���� ���ƿ� ������ �ݺ�
	while(true)
	{
		if (newBook->name < curBook->name)
			break;

		curBook = curBook->nextBook;

		if (curBook == head)
			break;
	}

	newBook->nextBook = curBook;
	newBook->prevBook = curBook->prevBook;

	curBook->prevBook->nextBook = newBook; 
	curBook->prevBook = newBook;

	if (curBook == head && newBook->name < curBook->name)
		head = newBook;
}

void BookList::deleteBook()
{
	if (!head)
	{
		cout << "���������� ������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	Book* curBook = head;
	string target;

	cout << "������ȣ�� �Է��ϼ��� : ";
	cin >> target;

	curBook = curBook->nextBook;
	while(true)
	{
		if (curBook->code == target)
		{
			if (curBook == head && head->nextBook == head)
			{
				delete head;
				head = NULL;
			}
			else if (curBook == head)
			{
				curBook->prevBook->nextBook = curBook->nextBook;
				curBook->nextBook->prevBook = curBook->prevBook;

				head = curBook->nextBook;
				delete curBook;
			}
			else
			{
				curBook->prevBook->nextBook = curBook->nextBook;
				curBook->nextBook->prevBook = curBook->prevBook;

				delete curBook;
			}
			return;
		}

		curBook = curBook->nextBook;

		if (curBook == head)
			break;
	}

	cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::print(string indexName)
{
	if (!head)
		return;

	bool print = false;
	if (indexName == "")
		print = true;

	Book* curBook = head;
	Book* lastBook = head;
	while(true)
	{
		if (curBook->name == indexName)
		{
			print = true;
			lastBook = curBook;
		}

		if (print)
			cout << *curBook;

		curBook = curBook->nextBook;

		if (curBook == lastBook)
			break;
	}

	if (!print)
		cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::printRev(string indexName)
{
	if (!head)
		return;

	bool print = false;
	if (indexName == "")
		print = true;

	Book* curBook = head->prevBook;
	while(true)
	{

		if (curBook->name == indexName)
			print = true;

		if (print)
			cout << *curBook;

		curBook = curBook->prevBook;

		if (curBook == head->prevBook)
			break;
	}

	if (!print)
		cout << "��ġ�ϴ� ������ �������� �ʽ��ϴ�." << endl;
}

void BookList::save()
{
	if (!head)
		return;

	ofstream ofs;
	ofs.open(path);

	Book* curBook = head;
	while (true)
	{
		ofs << curBook->code << SEPARATOR << curBook->name << endl;

		curBook = curBook->nextBook;

		if (curBook == head)
			break;
	}

	ofs.close();
}