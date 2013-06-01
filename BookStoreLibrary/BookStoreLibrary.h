#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Node.h"
#include "List.h"
#include "HashTable.h"
#include "Lock.h"
#include "Book.h"
#include "BookNotifier.h"

// __declspec(dllexport) modifier enable the method to be exported
// by the DLL so they can be used by other applications.

#ifdef BOOKSTORELIBRARY_EXPORTS
#define BOOKSTORELIBRARY_API __declspec(dllexport) 
#else
#define BOOKSTORELIBRARY_API __declspec(dllimport) 
#endif

// Instantiate various template classes. This does not create an object. 
// It only forces the generation of all of the members of classes. It 
// exports them from the DLL.

template class BOOKSTORELIBRARY_API BookLibrary::Node<BookLibrary::Book>;
template class BOOKSTORELIBRARY_API BookLibrary::Node<BookLibrary::BookNotifier>;
template class BOOKSTORELIBRARY_API BookLibrary::List<BookLibrary::Book>;
template class BOOKSTORELIBRARY_API BookLibrary::List<BookLibrary::BookNotifier>;
template class BOOKSTORELIBRARY_API BookLibrary::HashTable<BookLibrary::Book, unsigned long>;
template class BOOKSTORELIBRARY_API BookLibrary::HashTable<BookLibrary::Book, std::string>;
template class BOOKSTORELIBRARY_API BookLibrary::HashTable<BookLibrary::Book, BookLibrary::BookType>;
template class BOOKSTORELIBRARY_API BookLibrary::HashTable<BookLibrary::BookNotifier, unsigned long>;

namespace BookLibrary
{

// BookStoreLibrary class exposes the main APIs to the user, through the DLL. 
// It uses HashTable<T, Y> to maintain the Book inventory. Additional 
// HashTables are used for faster retrival of information.

class BOOKSTORELIBRARY_API BookStoreLibrary
{
public:

	BookStoreLibrary();
	~BookStoreLibrary();

	// Add Book to the inventory
	void add(std::tr1::shared_ptr<Book> book);

	// Remove Book from the inventory
	void remove(unsigned long id);

	// Display all the books of a particular author.
	void display(std::string authorName) const;

	// Display all the books of a particular type.
	void display(BookType bookType) const;

	// Get a book issued from the library.
	bool get(unsigned long id);

	// Return back the book to the library.
	bool collect_book(unsigned long id);

	// Is book available.
	bool isAvailable(unsigned long id) const;

	// Allows user to set a notifier whenever a book is available.
	void notify_me(unsigned long id, notifyUserFunc nf);

	// Remove notifier.
	void remove_notification(unsigned long id);

	// overloaded operator<< for easy display of complete library
	// along with all the other data structures used.
	friend std::ostream& operator<<(std::ostream& out, const BookStoreLibrary& bs);

private:

	// Set book availability.
	void setAvailable(unsigned long id, bool isAvailable);

private:
	
	HashTable<Book, unsigned long> _bookIdHashTable;	// Storing books based on id.
	HashTable<Book, std::string> _bookAuthorHashTable;	// Storing books based on author name.
	HashTable<Book, BookType> _bookTypeHashTable;		// Storing books based on type.

	HashTable<BookNotifier, unsigned long> _bookNotifierHashTable;	// Storing book notifications

	mutable CRITICAL_SECTION _criticalSection;	// Critical section object of thread synchronization.
												// It is required to be mutable.
};

BookStoreLibrary::BookStoreLibrary()
	:_bookIdHashTable(MAX_BOOK_ID_HASHKEY, hashBookId, &Book::getId),
	 _bookAuthorHashTable(MAX_BOOK_AUTHOR_HASHKEY, hashBookAuthor, &Book::getAuthorName),
	 _bookTypeHashTable(MAX_BOOK_TYPE_HASHKEY, hashBookType, &Book::getBookType),
	 _bookNotifierHashTable(MAX_BOOK_ID_HASHKEY, hashBookId, &BookNotifier::getId)
{
	// Initialize the critical section object using Windows API
	InitializeCriticalSection(&_criticalSection);
}

BookStoreLibrary::~BookStoreLibrary()
{
	// Delete the critical section object using Windows API
	DeleteCriticalSection(&_criticalSection);
}

void BookStoreLibrary::add(std::tr1::shared_ptr<Book> book)
{
	Lock lock(_criticalSection);

	_bookIdHashTable.put(book);
	_bookAuthorHashTable.put(book);
	_bookTypeHashTable.put(book);
}

void BookStoreLibrary::remove(unsigned long id)
{
	Book b1;
	b1.setId(id);

	Lock lock(_criticalSection);

	Book* b2 = _bookIdHashTable.remove(&b1);
	_bookAuthorHashTable.remove(b2);
	_bookTypeHashTable.remove(b2);
}

void BookStoreLibrary::display(std::string authorName) const
{
	Book b;
	b.setAuthorName(authorName);

	_bookAuthorHashTable.display(&b);
}

void BookStoreLibrary::display(BookType bookType) const
{
	Book b;
	b.setBookType(bookType);

	_bookTypeHashTable.display(&b);
}

bool BookStoreLibrary::isAvailable(unsigned long id) const
{
	Book b1;
	b1.setId(id);

	Book* b2 = _bookIdHashTable.get(&b1);

	if (b2)
	{
		return b2->isAvailable();
	}
	else
	{
		return false;
	}
}

bool BookStoreLibrary::get(unsigned long id)
{
	if (isAvailable(id))
	{
		setAvailable(id, false);

		return true;
	}

	return false;	// book not available
}

bool BookStoreLibrary::collect_book(unsigned long id)
{
	if (!isAvailable(id))
	{
		setAvailable(id, true);

		return true;
	}

	return false;	// book already returned and available

}

void BookStoreLibrary::notify_me(unsigned long id, notifyUserFunc nf)
{
	std::tr1::shared_ptr<BookNotifier> bn(new BookNotifier(id, nf));
	_bookNotifierHashTable.put(bn);
}

void BookStoreLibrary::remove_notification(unsigned long id)
{
	BookNotifier bn;
	bn.setId(id);

	BookNotifier* temp = _bookNotifierHashTable.remove(&bn);
}

std::ostream& operator<<(std::ostream& out, const BookStoreLibrary& bs)
{
	Lock lock(bs._criticalSection);

	out << bs._bookIdHashTable;
	out << bs._bookAuthorHashTable;
	out << bs._bookTypeHashTable;

	return out;
}

void BookStoreLibrary::setAvailable(unsigned long id, bool isAvailable)
{
	Book b;
	b.setId(id);

	Book* b1 = _bookIdHashTable.get(&b);

	Lock lock(_criticalSection);

	b1->setIsAvailable(isAvailable);	// Book is now available to issue.
	b1->setDate(time(0));				// Note the current date on which the book is available.

	Book* b2 = new Book(*b1);
	std::tr1::shared_ptr<Book> p(b2);

	BookNotifier bn;
	bn.setId(id);

	BookNotifier* bn1 = _bookNotifierHashTable.get(&bn);

	if (bn1 && isAvailable)
	{
		(bn1->getFP())(p);
	}
}

}

#endif
