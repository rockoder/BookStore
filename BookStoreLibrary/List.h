#ifndef LIST_H
#define LIST_H

#include <ostream>
#include <memory>

#include "Node.h"

namespace BookLibrary
{

// List<T> is singly linked list of Node<T> nodes. 
// It maintains front and rear Node<T> pointers.

template<class T>
class List
{
public:
	
	List();

	void push_back(std::tr1::shared_ptr<T> d);

	T* remove(const T& data);

	std::tr1::shared_ptr<Node<T>>& begin();

	// Function definition within class definition necessary to avoid linker error.
	friend std::ostream& operator<<(std::ostream& out, const List<T>& l)
	{	
		std::tr1::shared_ptr<Node<T>> temp = l._front;

		while (temp)
		{
			out << *temp;
			temp = temp->getNext();
		}

		return out;
	}

private:

	std::tr1::shared_ptr<Node<T>> _front;	// Pointer to first node in the list.
	std::tr1::shared_ptr<Node<T>> _rear;	// Pointer to last node in the list.
};

template<class T>
List<T>::List()
:_front(0),
 _rear(0)
{	}

template<class T>
void List<T>::push_back(std::tr1::shared_ptr<T> d)
{
	std::tr1::shared_ptr<Node<T>> node(new Node<T>(d));

	if (!_front)
	{
		_front = _rear = node;
	}
	else
	{	
		_rear->setNext(node);
		_rear = _rear->getNext();
	}
}

template<class T>
T* List<T>::remove(const T& data)
{
	std::tr1::shared_ptr<Node<T>> temp = _front;
	std::tr1::shared_ptr<Node<T>> prev = 0;

	while (temp)
	{
		if (data == *temp->getData().get())
		{
			if (prev == 0)	// front node is to be deleted.
			{
				_front = _rear = temp->getNext();
					
				return temp->getData().get();
			}
			else
			{
				prev->setNext(temp->getNext());

				if (temp->getNext() == 0)	// last node is to be deleted.
				{
					_rear = prev;
				}

				temp->setNext(0);
				return temp->getData().get();
			}
		}

		prev = temp;
		temp = temp->getNext();
	}

	return 0;
}

template<class T>
inline std::tr1::shared_ptr<Node<T>>& List<T>::begin()
{
	return _front;
}

}

#endif
