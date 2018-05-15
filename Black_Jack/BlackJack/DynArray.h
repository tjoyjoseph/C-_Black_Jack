#include "Logger.h"

//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <Windows.h>
//#include <sstream>

//using namespace std;

#ifndef DYNARRAY_H
#define DYNARRAY_H

template <typename Type>
class DynArray
{
private:
	const int INITIAL_ARRAY_SIZE = 5;
	int _bufferCapacity;
	Type *_buffer;
	int lastIndex;
	Logger _logging;

	void expandBuffer();
	void reset(int ArraySize);
	void copy(const DynArray & tbc);
public:
	DynArray(char m, string FileName = "_log");
	DynArray(DynArray & tbc);
	~DynArray();

	////////////////////////////////////
	////////[PRO FUNCTIONALITY]/////////
	////////////////////////////////////
	int capacity() const;
	int size() const;
	bool empty();
	void push_back(Type Item);
	void pop_back();
	Type back();
	Type front();
	Type get(int index);
	void set(Type newItem, int index);
	void zap();
	
	/////////////////////////////////////////////////////////////////
	///////////////////[PREMIUM FUNCTIONALITY]///////////////////////
	/////////////////////////////////////////////////////////////////
	void remove(int rmvIndex);
	void insert(Type newItem, int index);
	DynArray operator=( const DynArray& tbc);
	bool operator==(const DynArray& compArray);
	void shrink();
	
	/////////////////////////////////////////////////////////////////
	//////////////////[ULTIMATE FUNCTIONALITIES]/////////////////////
	/////////////////////////////////////////////////////////////////
	Type &operator[](int Index);
	DynArray  operator+=(const DynArray& newArray);
	void insertFront(Type newItem);
	void removeFront();
	void showAll();
};

#endif // !DYNARRAY_H

///Constructor
template <class Type>
DynArray<Type>::DynArray(char logType, string fileName)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	if (fileName == "_log")
	{
		ostringstream cDay;
		cDay << time.wDay << "." << time.wMonth << "." << time.wYear;
		fileName = cDay.str() + fileName;
	}
	_logging.createFile(logType, fileName);
	_logging._sLog("Begin: DynArray<Type>::DynArray(char LogType, string FileName)");
	reset(INITIAL_ARRAY_SIZE);
	_logging._sLog("End: DynArray<Type>::DynArray(char LogType, string FileName)");
}

///Copy Constructor
template <class Type>
DynArray<Type>::DynArray(DynArray & tbc)
{
	_logging._sLog("Begin: DynArray<Type>::DynArray(DynArray & tbc)");
	copy(tbc);
	_logging._sLog("End: DynArray<Type>::DynArray(DynArray & tbc)");
}

///Destructor
template <class Type>
DynArray<Type>::~DynArray()
{
	_logging._sLog("Begin: DynArray<Type>::~DynArray()");
	delete[] _buffer;
	_logging._sLog("End: DynArray<Type>::~DynArray()");
}

///Rests array back to its initial state
template <class Type>
void DynArray<Type>::reset(int ArraySize)
{
	_logging._sLog("Begin: void DynArray<Type>::reset(int ArraySize)");
	_bufferCapacity = ArraySize;
	_buffer = new Type[ArraySize];
	_logging._info("New _buffer variable created");
	lastIndex = -1;
	_logging._sLog("Begin: void DynArray<Type>::reset(int ArraySize)");
}

///when the array is full, expands the capacity by the initial array size
template <class Type>
void DynArray<Type>::expandBuffer()
{
	///checks if array is full
	_logging._sLog("Begin: void DynArray<Type>::expandBuffer()");
	if (lastIndex == _bufferCapacity)
	{
		///creates a temporary buffer bigger than the current buffer
		///copies all files from cuurent cuffer to temporary buffer
		Type * Tempbuffer = new Type[_bufferCapacity + INITIAL_ARRAY_SIZE];
		_logging._info("Tempbuffer created of size _bufferCapacity + INITIAL_ARRAY_SIZE");
		for (int i = 0; i <= _bufferCapacity; i++)
		{
			Tempbuffer[i] = _buffer[i];
		}
		///ammends current buffer properties and resets current buffer with expanded size to match temp buffer
		///copies files from temp buffer to the resetted bufffer  then deletes temp buffer
		_bufferCapacity += INITIAL_ARRAY_SIZE;
		_buffer = new Type[_bufferCapacity];
		_logging._info("_buffer created of size _bufferCapacity");
		for (int i = 0; i <=lastIndex; i++)
		{
			_buffer[i] = Tempbuffer[i];
		}
		delete[] Tempbuffer;
		_logging._info("Tempbuffer deleted");
	}
	_logging._sLog("End: void DynArray<Type>::expandBuffer()");
}

///used to copy friles from an external dynamic array to the current one
///done by resetting the array, matching the properties and then copying the items
template <class Type>
void DynArray<Type>::copy(const DynArray & tbc)
{
	_logging._sLog("Begin: void DynArray<Type>::copy(const DynArray & tbc)");
	reset(tbc._bufferCapacity);
	_bufferCapacity = tbc._bufferCapacity;
	lastIndex = tbc.lastIndex;
	for (int i = 0; i <= lastIndex; ++i)
	{
		_buffer[i] = tbc._buffer[i];
	}
	_logging._info("tbc properties and values copied into current DynArray properties and values");
	_logging._sLog("End: void DynArray<Type>::copy(const DynArray & tbc)");
}

///////////////////////////////////////////////////////////////////////
////////////////////////[PRO FUNCTIONALITIES]//////////////////////////
///////////////////////////////////////////////////////////////////////

///returns buffer capacity
template <class Type>
int DynArray<Type>::capacity() const
{
	const_cast <DynArray*> (this)->_logging._sLog("Function: int DynArray<Type>::capacity() const");
	const_cast <DynArray*> (this)->_logging._info("Returns _bufferCapacity");
	return _bufferCapacity;
}

///returns buffer size
template <class Type>
int DynArray<Type>::size() const
{
	const_cast <DynArray*> (this)->_logging._sLog("Function: int DynArray<Type>::size() const");
	const_cast <DynArray*> (this)->_logging._info("Returns lastIndex+1");
	return lastIndex+1;
	
}

///returns true if buffer is empty, else false
template <class Type>
bool DynArray<Type>::empty()
{
	if (lastIndex == -1)
	{
		return true;
	}
	return false;
}

///adds one element to the buffer, expands buffer if need be
template <class Type>
void DynArray<Type>::push_back(Type Item)
{
	_logging._sLog("Begin: void DynArray<Type>::push_back(Type Item)");
	lastIndex += 1;
	_buffer[lastIndex] = Item;
	expandBuffer();
	_logging._sLog("End: void DynArray<Type>::push_back(Type Item)");
}

///deletes the last element from the buffer
template <class Type>
void DynArray<Type>::pop_back()
{
	_logging._sLog("Begin: void DynArray<Type>::pop_back()");
	lastIndex -= 1;
	_logging._sLog("End: void DynArray<Type>::pop_back()");
}

///returns the last element of the buffer
template <class Type>
Type DynArray<Type>::back()
{
	return _buffer[lastIndex];
}

///returns the first element of the buffer
template <class Type>
Type DynArray<Type>::front()
{
	return _buffer[0];
}

///returns the element in the index defined by the parameters
template <class Type>
Type DynArray<Type>::get(int index)
{
	_logging._sLog("Begin: Get(int index)");
	if (index > lastIndex)
	{
		_logging._err("Index Out Of Range");
		//throw out_of_range("The Index is out of range");
	}
	_logging._sLog("End: Get(int index)");
	return _buffer[index];
}

///replaces index element defined by the parameters with element defined by the parameters.
///Produces error if out of range
template <class Type>
void DynArray<Type>::set(Type newItem, int index)
{
	_logging._sLog("Begin: void DynArray<Type>::set(Type newItem, int index)");
	if ((index > lastIndex) || (index < 1))
	{
		_logging._err("Index Out Of Range");
		//throw out_of_range("The Index is out of range");
	}
	else
	{
		_buffer[index] = newItem;
		_logging._info("Item number 'index' has been changed to 'newItem'");
	}
	_logging._sLog("End: void DynArray<Type>::set(Type newItem, int index)");
}

///resets buffer to its original state
template <class Type>
void DynArray<Type>::zap()
{
	_logging._sLog("Begin: void DynArray<Type>::zap()");
	reset(INITIAL_ARRAY_SIZE);
	_logging._sLog("End: void DynArray<Type>::zap()");
}


///////////////////////////////////////////////////////////////////////////////
//////////////////////////[PRIMIUM FUNCTIONALITIES]////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///removes index element if it exists, else produces an error
template <class Type>
void DynArray<Type>::remove(int rmvIndex)
{
	_logging._sLog("Begin: DynArray<Type>::remove(int rmvIndex)");
	if ((rmvIndex < 0) || (rmvIndex > lastIndex))
	{
		_logging._err("Index Out Of Range");
	}
	else
	{
		///sets all elements after the proposed elements need removing, back by one
		int m;
		for (m = rmvIndex; m < lastIndex + 1; ++m)
		{
			_buffer[m] = _buffer[m + 1];
		}
		_logging._info("Items after index 'rmvIndex' have been shifted up by one place ");
		lastIndex = m - 2;
		_logging._info("Last Index decremented by 1 ");
	}
	_logging._sLog("End: DynArray<Type>::remove(int rmvIndex)");
}

///inserts element into th proposed index
///done by inserting element and then moving all other elements down by one
template <class Type>
void DynArray<Type>::insert(Type newItem, int index)
{
	expandBuffer();
	Type temp;
	int i;
	for (i = index; i < lastIndex + 1; ++i)
	{
		temp = _buffer[i];
		_buffer[i] = newItem;
		newItem = temp;
	}
	_buffer[i] = newItem;
	lastIndex += 1;
	expandBuffer();
};

///copies everything from external array into this array
template <class Type>
DynArray<Type> DynArray<Type>::operator=(const DynArray& tbc)
{
	copy(tbc);
	return *this;
};

///compare external array with this array based on its elements and its properties. 
///All have to match for it to be true
template <class Type>
bool DynArray<Type>::operator==(const DynArray& compArray)
{
	bool comparison = false;
	if (lastIndex == compArray.lastIndex)
	{
		for (int i = 0; i < lastIndex; ++i)
		{
			if (_buffer[i] == compArray._buffer[i])
			{
				comparison = true;
			}
		}
	}
	return comparison;
}

///shrinks array size to its last element
template <class Type>
void DynArray<Type>::shrink()
{
	///creates a temporary smaller buffer, and copies everything from current buffer to this buffer
	Type * Tempbuffer = new Type[lastIndex + 1];
	for (int i = 0; i <= lastIndex; i++)
	{
		Tempbuffer[i] = _buffer[i];
	}
	///creates new buffer based on temporary buffer's size 
	///copies everything from temp buffer to current buffer
	_bufferCapacity += lastIndex;
	_buffer = new Type[_bufferCapacity + 1];
	for (int i = 0; i <= _bufferCapacity; i++)
	{
		_buffer[i] = Tempbuffer[i];
	}

	delete[] Tempbuffer;
}
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////[PRIMIUM FUNCTIONALITIES]//////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///can be used to return index element requested, or even change the index element requested
template <class Type>
Type &DynArray<Type>::operator[](int Index)
{
	if ((Index < lastIndex) && (Index >= 0))
	{
		return _buffer[Index-1];
	}
};

//adds on additional elements from the external array into this array
template <class Type>
DynArray<Type>  DynArray<Type>::operator+=(const DynArray& newArray)
{
	for (int i = 0; i < newArray.lastIndex; ++i)
	{
		this->push_back(newArray._buffer[i]);
	}
	return *this;
};

///replaces an element in the front
template <class Type>
void DynArray<Type>::insertFront(Type newItem)
{
	_buffer[0] = newItem;
};

///removes the element in the front
template <class Type>
void DynArray<Type>::removeFront()
{
	remove(0);
};

//Displays all element of the array
template <class Type>
void DynArray<Type>::showAll()
{
	for (int i = 0; i <= lastIndex; ++i)
	{
		cout << _buffer[i] << "  ";
	}
};