#pragma once
#include <iostream>

class Line
{
public:
	Line();
	Line(const Line&);
	Line& operator=(const Line&);
	~Line();

	void SetText(char*);
	char* GetText() const;
	int GetSize() const;

	int GetWordCount() const;

	Line& MakeHead();
	Line& MakeItl(int from, int to);
	Line& MakeBld(int from, int to);
	Line& MakeCmb(int from, int to);

private:
	void copy(const Line&);
	void free();

private:
	char* text;
	int size;
};

