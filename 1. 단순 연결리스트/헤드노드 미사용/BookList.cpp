#include "BookList.h"

BookList::BookList(char* source) : SEPARATOR(' ')
{
	ifstream ifs(source);
	path = source;
	head = NULL;

	while(ifs.fail())
	{
		cout << "! 입력받은 파일이 없습니다. 재입력 :";
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
	Book* curBook = head;
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
	cout << "(1) 새 도서 입력\n";
	cout << "(2) 도서 삭제\n";
	cout << "(3) 도서명 순으로 전체 출력\n";
	cout << "(4) 파일에 저장하고 종료\n";
	cout << "==========================================\n";

	while (type != EXIT)
	{
		cout << "원하는 기능을 선택하세요 : ";
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
	cout << "종료합니다." << endl;
}

Book* BookList::setNewBook()
{
	Book* newBook;

	string buffer;
	newBook = new Book;

	cout << "도서번호와 도서명을 입력하세요 : ";
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
	Book* curBook = head;
	Book* preBook = NULL;

	if (!newBook)
	{
		newBook = setNewBook();

		if (!newBook)
		{
			cout << "\n올바르지 않은 형식의 입력입니다." << endl;
			return;
		}
	}

	if (!head)
	{
		head = newBook;
		return;
	}

	while (curBook)
	{
		if (newBook->name < curBook->name)
			break;

		preBook = curBook;
		curBook = curBook->nextBook;
	}

	if (curBook == head)
	{
		newBook->nextBook = head;
		head = newBook;
		return;
	}

	preBook->nextBook = newBook;
	newBook->nextBook = curBook;
}

void BookList::deleteBook()
{
	Book* curBook = head;
	Book* preBook = NULL;
	string target;

	cout << "도서번호를 입력하세요 : ";
	cin >> target;

	while (curBook)
	{
		if (curBook->code == target)
		{
			if (curBook == head)
			{
				head = curBook->nextBook;
				delete curBook;
			}
			else
			{
				preBook->nextBook = curBook->nextBook;
				delete curBook;
			}
			return;
		}

		preBook = curBook;
		curBook = curBook->nextBook;
	}

	cout << "일치하는 도서가 존재하지 않습니다." << endl;
}

void BookList::print()
{
	Book* curBook = head;

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

	Book* curBook = head;
	while (curBook)
	{
		ofs << curBook->code << SEPARATOR << curBook->name << endl;
		curBook = curBook->nextBook;
	}

	ofs.close();
}