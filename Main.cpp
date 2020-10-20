#include <iostream>
#include <fstream>
#include "Line.h"
#include "DynArr.h"

const int maxFileNameSize = 256;
const int maxFileLineLength = 1024;
const int maxCommandSize = 12;

void ReadFileName(char*& fName)
{
	fName = new char[maxFileNameSize];
	if(!fName)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	std::cout << "Enter the name of the file you want to open -> ";
	std::cin.getline(fName, maxFileNameSize);
}

void ChangeFileName(char*& fName)
{
	int len = strlen(fName);

	char* newName = new (std::nothrow)char[len]; // without '\0'
	if (!newName)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	
	for (int i = 0; i < len; ++i)
	{
		newName[i] = fName[i];
		if (fName[i] == '.') break;
	}

	newName[len - 3] = 'm';
	newName[len - 2] = 'd';
	newName[len - 1] = '\0';

	delete[] fName;
	
	fName = newName;
}

int main()
{
	char* fileName;
	ReadFileName(fileName);
	
	std::ifstream in(fileName);
	if (!in)
	{
		std::cerr << "Could not open " << fileName << "!\n";
		exit(1);
	}

	DynArr arr;
	Line l;

	char* buffer = new char[maxFileLineLength];
	if (!buffer)
	{
		std::cerr << "Not enough memory!\n";
		return 1;
	}

	while (in.getline(buffer, maxFileLineLength))
	{
		l.SetText(buffer);
		arr.insert(l);
	}
	
	in.close();

	std::cout << "Enter commands :\n";
	
	while (true)
	{
		char command[maxCommandSize];
		std::cin >> command;

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else if (strcmp(command, "makeHeading") == 0)
		{
			int lineNumb;
			std::cin >> lineNumb;
			arr.MakeHeading(lineNumb);
		}
		else if (strcmp(command, "makeItalic") == 0)
		{
			int lineNumb, from, to;
			std::cin >> lineNumb >> from >> to;
			arr.MakeItalic(lineNumb, from, to);
		}
		else if (strcmp(command, "makeBold") == 0)
		{
			int lineNumb, from, to;
			std::cin >> lineNumb >> from >> to;
			arr.MakeBold(lineNumb, from, to);
		}
		else if (strcmp(command, "makeCombine") == 0)
		{
			int lineNumb, from, to;
			std::cin >> lineNumb >> from >> to;
			arr.MakeCombine(lineNumb, from, to);
		}
		else if (strcmp(command, "addLine") == 0)
		{
			char newLine[maxFileLineLength];
			std::cin.ignore();
			std::cin.getline(newLine, maxFileLineLength);
			l.SetText(newLine);
			arr.insert(l);
		}
		else if (strcmp(command, "remove") == 0)
		{
			int lineNumb;
			std::cin >> lineNumb;
			arr.remove(lineNumb);
		}
	}

	ChangeFileName(fileName);

	std::ofstream out(fileName);
	if (!out)
	{
		std::cerr << "Could not save to " << fileName << "!\n";
	}

	for (int i = 0; i < arr.GetSize(); i++)
	{
		out << arr[i].GetText() << std::endl;
	}

	out.close();
	delete[] buffer;
	delete[] fileName;

	system("pause");
	return 0;
}