#pragma once
#include"Line.h"

class DynArr
{
public:
	DynArr();
	DynArr(const DynArr&);
	DynArr& operator=(const DynArr&);
	~DynArr();

	int GetSize() const;

	void insert(const Line&); // insert a line
	void remove(int); // remove a line
	Line& operator[](int);

	void MakeHeading(int newFirst);
	void MakeItalic(int lineIndex, int from, int to);
	void MakeBold(int lineIndex, int from, int to);
	void MakeCombine(int lineIndex, int from, int to);

private:
	void copy(const DynArr&);
	void free();
	void resize();

private:
	Line* data;
	int size;
	int capacity;
};

