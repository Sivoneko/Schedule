#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Hours
{
	Hours()
	{
		hour = 0;
		minute = 0;
	}
	int hour;
	int minute;

	Hours& operator=(const Hours& hours)
	{
		hour = hours.hour;
		minute = hours.minute;
		return *this;
	}
	Hours& operator+(const Hours& hours)
	{
		hour += hours.hour;
		minute += hours.minute;

		if (minute >= 60)
		{
			hour++;
			minute -= 60;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& os, Hours& hours)
	{
		os << hours.hour << ":" << hours.minute;
		return os;
	}
	friend istream& operator>>(istream& is, Hours& hours)
	{
		is >> hours.hour >> hours.minute;
		return is;
	}
};

struct ReadFile
{
	string Date;

	Hours japanese;
	Hours english;
	Hours programing;
	Hours math;

	ReadFile* left;
	ReadFile* right;
};

class TIME
{
protected:
	ReadFile* readfile;
	string date;

	Hours* ForTree = new Hours[4];
	Hours* ForAllTime = new Hours[4];
public:
	TIME()
	{
		readfile = NULL;
	}
	void AddInTree()
	{
		ReadFile* pv = readfile, *prew;
		bool found = false;
		if (pv == NULL)
		{
			pv = new ReadFile;

			pv->Date = date;
			pv->japanese = ForTree[0];
			pv->english = ForTree[1];
			pv->programing = ForTree[2];
			pv->math = ForTree[3];
			pv->left = NULL;
			pv->right = NULL;
			readfile = pv;
			return;
		}
		else
		{
			while (pv && !found)
			{
				prew = pv;
				if (pv->Date == date)found = true;
				else if (date > pv->Date) pv = pv->right;
				else pv = pv->left;
			}
			if (found)
			{
				pv->japanese = ForTree[0];
				pv->english = ForTree[1];
				pv->programing = ForTree[2];
				pv->math = ForTree[3];
				return;
			}
			ReadFile* pnew = new ReadFile;
			pnew->Date = date;
			pnew->japanese = ForTree[0];
			pnew->english = ForTree[1];
			pnew->programing = ForTree[2];
			pnew->math = ForTree[3];
			pnew->left = 0;
			pnew->right = 0;

			if (date < prew->Date)
				prew->left = pnew;
			else
				prew->right = pnew;
			return;
		}

	}
	ReadFile* GetTree()
	{
		return readfile;
	}
	void PrintTree(ReadFile* readfile, ostream& out)
{
	if (readfile)
	{
		TIME::PrintTree(readfile->left,out);

		out << readfile->Date << endl;
		out << readfile->japanese << endl;
		out << readfile->english << endl;
		out << readfile->programing << endl;
		out << readfile->math << endl;

		TIME::PrintTree(readfile->right, out);
	}
}
	
	void SetTime(string Date,Hours japanese,Hours english,Hours programming, Hours math)
	{
		date = Date;
		ForTree[0] = japanese;
		ForTree[1] = english;
		ForTree[2]= programming;
		ForTree[3] = math;
	}
	void FindInTree(string D)
	{
		ReadFile* pv = readfile;
		bool found = false;
		while (pv && !found)
		{
			if (pv->Date == D)found = true;
			else if (D > pv->Date) pv = pv->right;
			else pv = pv->left;
		}
		if (found)
		{
			cout <<"Японский:        "<< pv->japanese << endl;
			cout <<"Английский:      " << pv->english << endl;
			cout <<"Программрование: " << pv->programing << endl;
			cout <<"Математика:      " << pv->math << endl;
			return;
		}
	}
	void FindInTreeComplex(string firstDate, string secondDate)
	{
		ReadFile* pv = readfile;
		bool found = false;
		while (pv && !found)
		{
			if (pv->Date == firstDate)found = true;
			else if (firstDate > pv->Date) pv = pv->right;
			else pv = pv->left;
		}
		if (found)
		{
			while (pv != NULL && pv->Date <= secondDate)
			{
				cout <<"***************"<<pv->Date<<"*******************"<<endl;
				cout << "Японский:        " << pv->japanese << endl;
				cout << "Английский:      " <<pv->english << endl;
				cout << "Программрование: " <<pv->programing << endl;
				cout << "Математика:      " << pv->math << endl;

				if (secondDate > pv->Date) pv = pv->right;
				else pv = pv->left;
			}
			return;
		}

	}
	
	void SetTimeAll(ReadFile* readfile)
	{
		
		if (readfile)
		{
			TIME::SetTimeAll(readfile->left);
			ForAllTime[0] = ForAllTime[0] + readfile->japanese;
			ForAllTime[1] = ForAllTime[1] + readfile->english;
			ForAllTime[2] = ForAllTime[2] + readfile->programing;
			ForAllTime[3] = ForAllTime[3] + readfile->math;
			TIME::SetTimeAll(readfile->right);
		}
	}
	Hours GetJapanese()
	{
		return ForAllTime[0];
	}
	Hours GetEnglish()
	{
		return ForAllTime[1];
	}
	Hours GetProgramming()
	{
		return ForAllTime[2];
	}
	Hours GetMath()
	{
		return ForAllTime[3];
	}
};
