#include "Line.h"

bool isEndOfWord(char c)
{
	return c == ' ' ||
		c == '.' ||
		c == '!' ||
		c == '?' ||
		c == ',';
}

bool isPunctuationMark(char c)
{
	return c == '.' ||
		c == '!' ||
		c == '?' ||
		c == ',';
}

Line::Line() : text(nullptr), size(0) // default ctor
{
}

Line::Line(const Line& other) // copy ctor
{
	copy(other);
}

Line & Line::operator=(const Line& rhs) // =
{
	if (this != &rhs)
	{
		free();
		copy(rhs);
	}
	return *this;
}

Line::~Line() // destructor
{
	free();
}

void Line::SetText(char* newText)
{
	if (text) free();

	size = strlen(newText) + 1; // strlen + '\0'

	text = new (std::nothrow) char[size];
	if (!text)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strncpy(text, newText, size);
}

char* Line::GetText() const
{
	return text;
}

int Line::GetSize() const
{
	return size;
}

void Line::copy(const Line& other)
{
	size = other.size;

	text = new (std::nothrow) char[size];
	if (!text)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strncpy(text, other.text, size);
}

void Line::free()
{
	delete[] text;
	size = 0;
}

int Line::GetWordCount() const
{
	int cnt = 0;
	for (int i = 0; i < size; ++i)
	{
		if (isEndOfWord(GetText()[i]))
		{
			if (text[i] == ' ' && isPunctuationMark(GetText()[i - 1]))
				continue;

			cnt++;
		}
	}

	return cnt;
}

Line& Line::MakeHead()
{
	bool sizeFlag = false;

	if (text[0] == '#')
	{
		size = size + 1; // if we have '#' as the first symbol we need just one '#'
	}
	else
	{
		size = size + 2; // if we have something else we need '#' + ' '
		sizeFlag = true;
	}

	char* newText = new (std::nothrow) char[size];
	if (!newText)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strncpy(newText, GetText(), size - 2);

	newText[size - 1] = '\0';
	
	if (sizeFlag) // if the size is increased by 2
	{
		for (int i = size - 1; i > 1; --i)
		{
			newText[i] = newText[i - 2];
		}
		newText[0] = '#';
		newText[1] = ' ';
	}
	else // if the size is increased by 1
	{
		for (int i = size - 2; i > 0; --i)
		{
			newText[i] = newText[i - 1];
		}
		newText[0] = '#';
	}

	SetText(newText);

	return *this;
}

Line& Line::MakeItl(int from, int to)
{
	if (from > to || from < 1) return *this;

	int wordCnt = GetWordCount();

	if (to > wordCnt) return *this;

	int difference = to - from; // calculate the words we have to make italic

	size = size + 2; // changing size.................|
					 //								  ->
	char* newText = new (std::nothrow) char[size]; // because of 2 more stars 
	if (!newText)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strncpy(newText, GetText(), size - 3); // copying the old text in the new array, without '\0'

	newText[size - 1] = '\0'; // making the end of the array

	int cnt = 0; // counter that will count the symbols to the first star

	int starPlace = 0;

	for (int i = 0; i < size, from > 0; ++i) // iterate untill the the beginning of the word,
	{										 // from which starts the italic font
		if (newText[i] == ' ')
			from--;

		cnt++;
	}

	if (newText[cnt] == '*') // if it is already Italic we free used resources
	{						 // and do nothing to the line
		delete[] newText;
		return *this;
	}

	for (int i = size - 2; i > cnt; --i) // moving the symbols one position forward to
	{									 // make room for one star
		newText[i] = newText[i - 1];	
	}

	newText[cnt] = '*'; // putting the first * in the right place

	int cnt1 = 0; // counter that will count the symbols to the closing star

	for (int i = cnt; i < size, difference >= 0; ++i)
	{
		if (isEndOfWord(newText[i])) // if it is end of a word => we decrease the difference
		{
			// if it's space after punctuation mark => continue because we have already
			// counted the previous symbol for end of a word, but still
			// we count that as a symbol, viz. cnt1++
			if (newText[i] == ' ' && isPunctuationMark(newText[i - 1]))
			{
				cnt1++;
				continue;
			}

			difference--;
		}

		cnt1++;
	}

	for (int i = size - 2; i >= cnt + cnt1; --i) // Moving the symbols one position forward 
	{											 // to make room for the closing star
		newText[i] = newText[i - 1];
	}

	if (isPunctuationMark(newText[cnt1 + cnt])) // putting the closing star in place
	{
		newText[cnt1 + cnt] = '*';
	}
	else
	{
		newText[cnt1 + cnt - 1] = '*'; 
	}
	
	SetText(newText); // set the new text

	delete[] newText; // free the resource

	return *this; // returning the object
}

Line& Line::MakeBld(int from, int to)
{
	if (from > to || from < 1) return *this;

	int wordCnt = GetWordCount();

	if (to > wordCnt) return *this;

	int difference = to - from; // calculate the words we have to make bold

	size = size + 4; // changing size

	char* newText = new (std::nothrow) char[size]; // because of 4 more stars 
	if (!newText)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strncpy(newText, GetText(), size - 5); // copying the old text in the new array, without '\0'

	newText[size - 1] = '\0'; // making the end of the array

	int cnt = 0; // counter that will count the symbols to the first star

	for (int i = 0; i < size, from > 0; ++i) // iterate untill the the beginning of the word,
	{										 // from which starts the bold font
		if (newText[i] == ' ')
			from--;

		cnt++;
	}

	if (newText[cnt] == '*' && newText[cnt + 1] == '*') // if it is already Bold, deallocate
	{													// and do nothing :)
		delete[] newText;
		return *this;
	}

	for (int i = size - 4; i > cnt + 1; --i) // moving the symbols two position forward to
	{										 // make room for two stars
		newText[i] = newText[i - 2];
	}

	newText[cnt] = '*'; // putting the first * in the right place
	newText[cnt + 1] = '*'; // putting the second *

	int cnt1 = 0; // counter that will count the symbols to the closing stars

	for (int i = cnt + 1; i < size, difference >= 0; ++i)
	{
		if (isEndOfWord(newText[i])) // if it is end of a word => we decrease the difference
		{
			// if it's space after punctuation mark => continue because we have already
			// counted the previous symbol as an end of a word, but still
			// we count that as a symbol, viz. cnt1++
			if (newText[i] == ' ' && isPunctuationMark(newText[i - 1]))
			{
				cnt1++;
				continue;
			}

			difference--;
		}
		cnt1++;
	}

	for (int i = size - 2; i >= cnt + cnt1; --i) // Moving the symbols two position forward 
	{											 // to make room for the closing stars
		newText[i] = newText[i - 2];
	}

	if (isPunctuationMark(newText[cnt1 + cnt + 2])) // putting the closing stars in place
	{
		newText[cnt1 + cnt] = newText[cnt1 + cnt + 2];
		newText[cnt1 + cnt + 2] = '*';
		newText[cnt1 + cnt + 1] = '*';
	}
	else
	{
		newText[cnt1 + cnt + 1] = '*';
		newText[cnt1 + cnt] = '*';
	}

	SetText(newText); // set the new text

	delete[] newText; // free the resource

	return *this; // returning the object
}

Line& Line::MakeCmb(int from, int to)
{
	MakeItl(from, to);
	MakeBld(from, to);
	return *this;

	//if (from > to || from < 1) return *this;

	//int wordCnt = GetWordCount();

	//if (to > wordCnt) return *this;

	//int difference = to - from; // calculate the words we have to make combine

	//size = size + 6; // changing size

	//char* newText = new (std::nothrow) char[size]; // because of 6 more stars 
	//if (!newText)
	//{
	//	std::cerr << "Not enough memory!\n";
	//	exit(1);
	//}
	//strncpy(newText, GetText(), size - 7); // copying the old text in the new array, without '\0'

	//newText[size - 1] = '\0'; // making the end of the array

	//int cnt = 0; // counter that will count the symbols to the first star

	//for (int i = 0; i < size, from > 1; ++i) // iterate untill the the beginning of the word,
	//{										 // from which starts the combine font
	//	if (newText[i] == ' ')
	//		from--;

	//	cnt++;
	//}

	//for (int i = size - 5; i > cnt + 2; --i) // moving the symbols three position forward to
	//{										 // make room for three stars
	//	newText[i] = newText[i - 3];
	//}

	//newText[cnt] = '*'; // putting the first * in the right place
	//newText[cnt + 1] = '*'; // putting the second *
	//newText[cnt + 2] = '*'; // putting the third *

	//int cnt1 = 0; // counter that will count the symbols to the closing stars

	//for (int i = cnt + 1; i < size, difference >= 0; ++i)
	//{
	//	if (isEndOfWord(newText[i])) // if it is end of a word => we decrease the difference
	//	{
	//		// if it's space after punctuation mark => continue because we have already
	//		// counted the previous symbol as an end of a word, but still
	//		// we count that as a symbol, viz. cnt1++
	//		if (newText[i] == ' ' && isPunctuationMark(newText[i - 1]))
	//		{
	//			cnt1++;
	//			continue;
	//		}

	//		difference--;
	//	}
	//	cnt1++;
	//}

	//for (int i = size - 2; i >= cnt + cnt1; --i) // Moving the symbols three position forward 
	//{											 // to make room for the closing stars
	//	newText[i] = newText[i - 3];
	//}

	//if (isPunctuationMark(newText[cnt1 + cnt + 3])) // putting the closing stars in place
	//{
	//	newText[cnt1 + cnt] = newText[cnt1 + cnt + 3];
	//	newText[cnt1 + cnt + 1] = '*';
	//	newText[cnt1 + cnt + 2] = '*';
	//	newText[cnt1 + cnt + 3] = '*';
	//}
	//else
	//{
	//	newText[cnt1 + cnt] = '*';
	//	newText[cnt1 + cnt + 1] = '*';
	//	newText[cnt1 + cnt + 2] = '*';
	//}

	//SetText(newText); // set the new text

	//delete[] newText; // free the resource

	//return *this; // returning the object
}

