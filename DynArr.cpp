#include "DynArr.h"

DynArr::DynArr()
	:data(nullptr),
	size(0),
	capacity(0)
{
}

DynArr::DynArr(const DynArr& other)
{
	copy(other);
}

DynArr& DynArr::operator=(const DynArr& rhs)
{
	if (this != &rhs)
	{
		free();
		copy(rhs);
	}
	return *this;
}

DynArr::~DynArr()
{
	free();
}

int DynArr::GetSize() const
{
	return size;
}

void DynArr::insert(const Line& value)
{
	if (size == capacity)
		resize();

	data[size++] = value;
}

void DynArr::remove(int pos)
{
	if (pos < 0 || pos > size)
		return;

	for (int i = pos - 1; i < size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	size--;
}

Line& DynArr::operator[](int pos)
{
	return data[pos];
}

void DynArr::MakeHeading(int newFirst)
{
	if (newFirst > size || newFirst < 1) return;

	Line tmp = data[newFirst - 1]; // the line we want to make heading

	for (int i = newFirst - 1; i > 0; --i)
	{
		data[i] = data[i - 1];	// we shift the elements of the array so that we "erase"
	}							// the line we want to make heading
	
	data[0] = tmp; // making the heading line in first place

	data[0].MakeHead();
}

void DynArr::MakeItalic(int lineIndex, int from, int to)
{
	data[--lineIndex].MakeItl(from, to);
}

void DynArr::MakeBold(int lineIndex, int from, int to)
{
	data[--lineIndex].MakeBld(from, to);
}

void DynArr::MakeCombine(int lineIndex, int from, int to)
{
	data[--lineIndex].MakeCmb(from, to);
}


void DynArr::copy(const DynArr& other)
{
	data = new Line[other.capacity]; // allocating memory
	if (!data)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	for (int i = 0; i < other.size; ++i) // copying the element
	{
		data[i] = other.data[i];
	}

	size = other.size;
	capacity = other.capacity;
}

void DynArr::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

void DynArr::resize()
{
	if (capacity == 0)
		capacity = 1;

	Line* newData = new Line[capacity * 2]; // allocating new array
	if (!newData)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	capacity *= 2;
	for (int i = 0; i < size; ++i) // copying the elements
	{
		newData[i] = data[i];
	}
	delete[] data; // deleting the old array
	data = newData; // assigning pointer
}