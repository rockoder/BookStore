#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <memory>

namespace BookLibrary
{

// HashTable<T, Y> represent the hash table with each row pointing 
// to a List<T> of elements having same hash code. It takes hash
// function from the user. <Y> denote the type of the data which
// is to be converted into hash code using the hash function.

template <class T, class Y>
class HashTable
{
public:

	typedef unsigned int (*HashFunction)(const Y);
	typedef Y (T::*getKeyForHashing)() const;

	HashTable(std::size_t size, HashFunction hf, getKeyForHashing mf);
	~HashTable();

	bool put(std::tr1::shared_ptr<T> data);

	T* remove(T* data);

	T* get(T* data) const;

	// Display based on the element criteria.
	void display(T* data) const;

	// Function definition within class definition necessary to avoid linker error.
	friend std::ostream& operator<<(std::ostream& out, const HashTable<T, Y>& h)
	{
		for (size_t i = 0; i < h._size; ++i)
		{
			out << "******** LIST " << i << "********" << std::endl;
			out << *h._table[i];
			out << std::endl;
		}

		return out;
	}

private:

	List<T>** _table;			// Hash Table - each row for each hash code.
	const std::size_t _size;	// Total number of rows in the Hash Table i.e. total unique hash codes.

	HashFunction _hf;			// Hash function to be used to calculate hash code.
	getKeyForHashing _kf;		// Function to get the data key from which hash code will be calculated.
};

template <typename T, class Y>
HashTable<T, Y>::HashTable(std::size_t size, HashFunction hf, getKeyForHashing mf)
:_size(size), _hf(hf), _kf(mf)
{
	// Note - shared_ptr cannot be used for storing _table 
	// since shared_ptr cannot identify array pointer and 
	// hence cannot release array memory correctly.
	_table = new List<T>*[_size];

	for (size_t i = 0; i < _size; ++i)
	{
		_table[i] = new List<T>();
	}
}

template <typename T, class Y>
HashTable<T, Y>::~HashTable()
{
	for (size_t i = 0; i < _size; ++i)
	{
		delete _table[i];
	}

	delete _table;
}

template <typename T, class Y>
bool HashTable<T, Y>::put(std::tr1::shared_ptr<T> data)
{
	std::size_t hashVal = _hf((data.get()->*_kf)());

	if (hashVal < _size)
	{
		_table[hashVal]->push_back(data);
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T, class Y>
T* HashTable<T, Y>::remove(T* data)
{
	std::size_t hashVal = _hf((data->*_kf)());

	if (hashVal < _size)
	{
		return _table[hashVal]->remove(*data);
	}

	return 0;
}

template <typename T, class Y>
T* HashTable<T, Y>::get(T* data) const
{
	std::size_t hashVal = _hf((data->*_kf)());

	if (hashVal < _size)
	{
		std::tr1::shared_ptr<Node<T>> temp = _table[hashVal]->begin();

		while (temp)
		{
			if ((temp->getData().get()->*_kf)() == (data->*_kf)())
			{
				return temp->getData().get();
			}

			temp = temp->getNext();
		}
	}

	return 0;
}

template <typename T, class Y>
void HashTable<T, Y>::display(T* data) const
{
	std::size_t hashVal = _hf((data->*_kf)());

	if (hashVal < _size)
	{
		std::tr1::shared_ptr<Node<T>> temp = _table[hashVal]->begin();

		while (temp)
		{
			if ((temp->getData().get()->*_kf)() == (data->*_kf)())
			{
				std::cout << *temp << std::endl;
			}

			temp = temp->getNext();
		}
	}
}

}

#endif