#include "Book.h"

Book::Book()
{
	nextBook = NULL;
}

ostream & operator<<(ostream & os, const Book & b)
{
	os << b.name << " [" << b.code << "]\n";

	return os;
}
