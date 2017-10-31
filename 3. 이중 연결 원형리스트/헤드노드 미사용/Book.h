#ifndef __BOOK_H__
#define __BOOK_H__
#include "CommonHeader.h"

class Book
{
	friend class BookList;
	friend ostream& operator << (ostream& os, const Book& b);

private:
	string code;
	string name;
	Book* nextBook;
	Book* prevBook;

public:
	Book() { nextBook = prevBook = NULL; }
};

#endif