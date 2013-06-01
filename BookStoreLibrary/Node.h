#ifndef NODE_H
#define NODE_H

#include <ostream>
#include <memory>

namespace BookLibrary
{

// Node<T> stores the T type of object within itself.
// Additionally is provides a Node<T> pointer which 
// can be used to attach a Node to larger data structures
// like List etc.

template<class T>
class Node
{
public:

	Node(std::tr1::shared_ptr<T> d);

	std::tr1::shared_ptr<Node> getNext() const;
	void setNext(std::tr1::shared_ptr<Node> node);

	std::tr1::shared_ptr<T> getData();

	// Function definition within class definition necessary to avoid linker error.
	friend std::ostream& operator<<(std::ostream& out, const Node<T>& node)
	{		
		T* temp = node._data.get();
		out << *temp;	
		return out;
	}

private:

	std::tr1::shared_ptr<T> _data;		// Data to be stored in the node.
	std::tr1::shared_ptr<Node> _next;	// Pointer to the next node.
};

template<class T>
Node<T>::Node(std::tr1::shared_ptr<T> d)
:_data(d), 
 _next(0)
{	}

template<class T>
inline std::tr1::shared_ptr<Node<T>> Node<T>::getNext() const
{
	return _next;
}

template<class T>
inline void Node<T>::setNext(std::tr1::shared_ptr<Node> node)
{
	_next = node;
}

template<class T>
inline std::tr1::shared_ptr<T> Node<T>::getData()
{
	return _data;
}

}

#endif
