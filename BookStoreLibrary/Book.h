#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ostream>
#include <cstring>
#include <ctime>

#include "Globals.h"

namespace BookLibrary
{

// Book object is used to store all the information about 
// a book, including availability of the book.

class Book
{
public:

	Book();
	Book(unsigned long bookId, const std::string& authorName, 
		 time_t date, BookType type, float price, const char* xyz);
	Book(const Book& rhs);

	unsigned long getId() const;
	void setId(unsigned long id);

	std::string getAuthorName() const;
	void setAuthorName(std::string authorName);

	BookType getBookType() const;
	void setBookType(BookType type);

	bool isAvailable() const;
	void setIsAvailable(bool isAvailable);

	void setDate(time_t date);

	bool operator==(const Book& rhs) const;

	friend std::ostream& operator<<(std::ostream& out, const Book& book);

private:

	unsigned long _bookId;		// Book id - unique identifier.
	std::string _authorName;	// Book author name.
	time_t _date;				// The latest date on which the book is available.
	BookType _type;				// Book type - Ex: Science, Literature etc.
	float _price;				// Book price.
	char _xyz[1000];			// Extra information.
	bool _isAvailable;			// Is book currently available.
};

Book::Book()
:_bookId(0), 
 _authorName(""), 
 _date(0), 	
 _type(NONE), 
 _price(0), 
 _isAvailable(false)
{
	strcpy(_xyz, "");
}

Book::Book(unsigned long bookId, const std::string& authorName, 
		   time_t date, BookType type, float price, const char* xyz)
:_bookId(bookId), 
 _authorName(authorName), 
 _date(date), 
 _type(type), 
 _price(price), 
 _isAvailable(true)
{
	strcpy(_xyz, xyz);
}

Book::Book(const Book& rhs)
:_bookId(rhs._bookId), 
 _authorName(rhs._authorName), 
 _date(rhs._date), 
 _type(rhs._type), 
 _price(rhs._price), 
 _isAvailable(rhs._isAvailable)
{
	strcpy(_xyz, rhs._xyz);
}

inline unsigned long Book::getId() const
{
	return _bookId;
}

inline void Book::setId(unsigned long id)
{
	_bookId = id;
}

inline std::string Book::getAuthorName() const
{
	return _authorName;
}
	
inline void Book::setAuthorName(std::string authorName)
{
	_authorName = authorName;
}

inline BookType Book::getBookType() const
{
	return _type;
}

inline void Book::setBookType(BookType type) 
{
	_type = type;
}

inline bool Book::isAvailable() const
{
	return _isAvailable;
}

inline void Book::setIsAvailable(bool isAvailable)
{
	_isAvailable = isAvailable;
}

inline void Book::setDate(time_t date)
{
	_date = date;
}

inline bool Book::operator==(const Book& rhs) const
{
	// Two Book objects are considered
	// same if their book ids are same.

	return _bookId == rhs._bookId;
}

std::ostream& operator<<(std::ostream& out, const Book& book)
{
	out << "*** Book Information ***" << std::endl;
	out << "Id:" << book._bookId << std::endl;
	out << "Author:" << book._authorName << std::endl;
	out << "Date:" << ctime(&book._date);
	out << "Type:" << book._type << std::endl;
	out << "Price:" << book._price << std::endl;
	out << "XYZ:" << book._xyz;

	return out;
}

}

#endif
