#ifndef BOOKNOTIFIER_H
#define BOOKNOTIFIER_H

#include "Globals.h"

namespace BookLibrary
{

// BookNotifier is used to store notification requests that
// came from the user. For each request it stores the book id 
// and corresponding notification function pointer.

class BookNotifier
{
public:

	BookNotifier();
	BookNotifier(unsigned long bookId, notifyUserFunc fp);

	unsigned long getId() const;
	void setId(unsigned long id);

	notifyUserFunc getFP() const;
	void setFP(notifyUserFunc fp);

	bool operator==(const BookNotifier& rhs) const;
	friend std::ostream& operator<<(std::ostream& out, const BookNotifier& rhs);

private:

	unsigned long _bookId;
	notifyUserFunc _fp;
};

BookNotifier::BookNotifier()
{	}

BookNotifier::BookNotifier(unsigned long bookId, notifyUserFunc fp)
:_bookId(bookId),
 _fp(fp)
{	}

inline unsigned long BookNotifier::getId() const
{
	return _bookId;
}

inline void BookNotifier::setId(unsigned long id)
{
	_bookId = id;
}

inline notifyUserFunc BookNotifier::getFP() const
{
	return _fp;
}

inline void BookNotifier::setFP(notifyUserFunc fp)
{
	_fp = fp;
}

inline bool BookNotifier::operator==(const BookNotifier& rhs) const
{
	// Two BookNotifier objects are considered
	// same if their book ids are same.

	return _bookId == rhs._bookId;
}

std::ostream& operator<<(std::ostream& out, const BookNotifier& rhs)
{
	out << "*** Book Notifier Information ***" << std::endl;
	out << "Id:" << rhs._bookId << std::endl;
	
	return out;
}

}

#endif