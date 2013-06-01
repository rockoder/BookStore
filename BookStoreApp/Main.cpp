#include <iostream>

#include "BookStoreLibrary.h"

const int MAX_THREADS = 5;

// Single BookStoreLibrary object shared across threads.
BookLibrary::BookStoreLibrary b;

// Sample notifier function to notify user
// about availability of a book.
void notifyFunction(std::tr1::shared_ptr<BookLibrary::Book> b)
{
	std::cout << "Notification - Following book is now available:" 
			  << std::endl << *b << std::endl;
}

// Function to be called at the start of the thread.
DWORD WINAPI threadFunction(LPVOID param)
{
	// Convert thread parameter from void to int.
	int *id = (int*)param;

	std::tr1::shared_ptr<BookLibrary::Book> 
		b1(new BookLibrary::Book(*id, "A", time(0), BookLibrary::SCIENCE, 
								 199, "Some more information"));

	std::tr1::shared_ptr<BookLibrary::Book> 
		b2(new BookLibrary::Book(*id*10, "B", time(0), BookLibrary::LITERATURE, 
								 199, "Some more information"));
	
	std::tr1::shared_ptr<BookLibrary::Book> 
		b3(new BookLibrary::Book(*id*10, "C", time(0), BookLibrary::MEDICINE, 
								 199, "Some more information"));

	b.add(b1);
	b.add(b2);
	b.add(b3);

	return 0;
}

int main()
{
	DWORD   threadIdArray[MAX_THREADS];
	HANDLE  threadArray[MAX_THREADS]; 

	int threadDataArray[] = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threadArray[i] = CreateThread( 
							NULL,					// default security attributes
							0,						// use default stack size  
							threadFunction,			// thread function name
							&threadDataArray[i],	// argument to thread function 
							0,                      // use default creation flags 
							&threadIdArray[i]);		// returns the thread identifier 

		if (threadArray[i] == NULL) 
		{
			ExitProcess(3);
		}
	}

	WaitForMultipleObjects(MAX_THREADS, threadArray, TRUE, INFINITE);

	// Display all books of type Science.
	b.display(BookLibrary::SCIENCE);

	// Remove one book.
	b.remove(1);

	std::cout << std::endl << std::endl;
	
	// Again display all books of type Science.
	b.display(BookLibrary::SCIENCE);

	// Get the book.
	b.get(10);

	std::cout << std::endl;

	// Should display book not available.
	if (b.isAvailable(10))
	{
		std::cout << "Book is available." << std::endl;
	}
	else
	{
		std::cout << "Book is not available." << std::endl;
	}
	
	// Setting notification for book id 10.
	b.notify_me(10, &notifyFunction);

	std::cout << std::endl << std::endl;
	
	// Should get notification after book is collected.
	b.collect_book(10);

	std::cout << std::endl << std::endl;

	// Display all books of author C.
	b.display("C");

    // Close all thread handles.
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        CloseHandle(threadArray[i]);
    }

	return 0;
}