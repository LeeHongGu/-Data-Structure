#include "BookList.h"

BookList::BookList(char* source) : SEPARATOR(' ')
{
	ifstream ifs(source);
	path = source;

	head.nextBook = &head;
	head.prevBook = &head;

	while(ifs.fail())
	{
		cout << "입력받은 파일이 없습니다. 재입력 : ";
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
	cout << "(1) 새 도서 입력\n";
	cout << "(2) 도서 삭제\n";
	cout << "(3) 도서명 순으로 전체 출력\n";
	cout << "(4) 도서명 역순으로 전체 출력\n";
	cout << "(5) 특정 도서명부터 전체 출력\n";
	cout << "(6) 특정 도서명부터 첫도서명까지 역순 출력\n";
	cout << "(7) 파일에 저장하고 종료\n";
	cout << "==========================================\n";

	while (type != EXIT)
	{
		cout << "원하는 기능을 선택하세요 : ";
		cin >> type;

		switch (type)
		{
		case APPEND: appendBook(); break;
		case DELETE: deleteBook(); break;
		case PRT_ALL: print(); break;
		case PRT_ALL_REV: printRev(); break;

		case PRT_PART_ALL: 
			cout << "도서명을 입력하세요 : ";
			cin.ignore();
			getline(cin, name);
			print(name);
			break;

		case PRT_PART_REV:
			cout << "도서명을 입력하세요 : ";
			cin.ignore();
			getline(cin, name);
			printRev(name);
			break;

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
			cout << "\n올바르지 않은 형식의 입력입니다." << endl;
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

	cout << "도서번호를 입력하세요 : ";
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

	cout << "일치하는 도서가 존재하지 않습니다." << endl;
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
		cout << "일치하는 도서가 존재하지 않습니다." << endl;
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
		cout << "일치하는 도서가 존재하지 않습니다." << endl;
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