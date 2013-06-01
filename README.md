BookStore
=========

This was an offline assignment given as part of interview process in one of product development company. Below is the problem statement emailed to me by the HR person. I implemented based on this description. No more details were provided. I tired to strictly follow the interface and instructions mentioned although I believe those didn't fit in correctly. I was given four days to implement it. The assignment was given on Friday evening and I was suppose to email the code by Wednesday. In all I had two full days (Saturday/Sunday) and two less-than-half days (Monday/Tuesday) as I had busy days in my current full time job.

I learnt a lot while working on this assignment and it does demonstrate the kind of C++ code I could write. I don't intend to make any enhancements to this code since the fun part was the deadline. However will be creating a writeup on my design decisions and assumptions - which, unfortunately, I could not find time to include with the original 'drop' to the HR. Also I might fix any bug that I come across.


Problem Statement
-----------------

BookStore

Design and implement a book store library (bookstore.dll or bookstore.so) that will allow the users to

1) add(book);
2) remove(book_id);
3) is_available(book_id);
4) notify_me(book_id, fp); // notify the user when a book_id is available. fp is a pointer to the user function of type <void (*fp)(book)>
5) get(book_id); //return the book if it is currently available.
6) collect_book(book_id); //collect the book returned to the bookstore. book_id is available from now on
7) display(author_name); // display all the books written by this author
   display(type t); // display all the books of type 't'

A book has the following property

i. book_id // a book is uniquely identified by book_id
ii. author_name
iii. date (the latest date on which this book is available)
iv. type (For example, science, literature, medicine, etc)
v. price
vi. char xyz[1000];
Assume the size of a single book object is about 1KB.

Note:
1. Use return types of your choice that makes the most sense.
2. Do not use C++ STLs. Use your own data structures.
3. This program should be thread safe.
4. All the operations on the bookstore is optimal.
5. Bookstore's memory footprint is optimal.
6. Bookstore could contain at most 1,00,000 books.

At last, write a program (bookstore_tests.exe or bookstore_tests) that will exercise the APIs - covering various scenarios.
