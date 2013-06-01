#ifndef GLOBALS_H
#define GLOBALS_H

namespace BookLibrary
{

// Forward declaration required for typedef 
// of notification function pointer.
class Book;

// Notification function pointer typedef.
typedef void (*notifyUserFunc)(std::tr1::shared_ptr<Book>);

// Note for enum BookType: 
//		Numbers cannot be assigned to any of the enums.
//		All new enums should be added after NONE and before N_BOOK_TYPES.
//		NONE - for books whose type has not yet been identified.
//		N_BOOK_TYPES - give the total number of enums present here.

enum BookType { NONE, SCIENCE, LITERATURE, MEDICINE, N_BOOK_TYPES };

// Used to display string instead of enum integer.
// Used while displaying Book's type.
std::ostream& operator<<(std::ostream& out, const BookType& t)
{
	switch(t)
	{
	case NONE:
		out << "None";
		break;

	case SCIENCE:
		out << "Science";
		break;

	case LITERATURE:
		out << "Literature";
		break;

	case MEDICINE:
		out << "Medicine";
		break;

	default:
		out << "*** ERROR: New enum Type value found! ***";
		break;
	}

	return out;
}

// Total number of books in library.
const unsigned long MAX_BOOKS = 100000;

// Total books stored under each hash code.
const unsigned int MAX_BOOKS_PER_HASH = 1000;

// Total possible hash keys for book id.
const unsigned int MAX_BOOK_ID_HASHKEY = MAX_BOOKS / MAX_BOOKS_PER_HASH;
unsigned int hashBookId(unsigned long id)
{
	return id / MAX_BOOKS_PER_HASH;
}

// Total possible hash keys for book author.
// Total number of alphabets in English language.
const unsigned int MAX_BOOK_AUTHOR_HASHKEY = 26;
unsigned int hashBookAuthor(std::string author)
{
	return toupper(author[0]) - 'A';
}

// Total possible hash keys for book type. This is equal
// to the total number of BookType enums defined.
const unsigned int MAX_BOOK_TYPE_HASHKEY = N_BOOK_TYPES;
unsigned int hashBookType(BookType type)
{
	return type;
}

}
#endif