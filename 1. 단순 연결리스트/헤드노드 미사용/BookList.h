#ifndef __BOOK_LIST_H__
#define __BOOK_LIST_H__
#include "CommonHeader.h"
#include "Book.h"
#include <fstream>

class BookList
{
private:
	Book* head; 
	string path;
	const char SEPARATOR;

public:
	BookList(char* source);
	~BookList();

	void showMenu();
	Book* setNewBook();
	void appendBook(Book* newBook = NULL);
	void deleteBook();
	void print();
	void save();
};

#endif