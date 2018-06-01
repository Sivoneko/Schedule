#include "stdafx.h"
#include "MyTime.h"


//---------------------------------------------------------------------
//Hours struct

Hours::Hours()
{
	hour = 0;
	minute = 0;
}
Hours& Hours::operator=(const Hours& hours)
{
	hour = hours.hour;
	minute = hours.minute;
	return *this;
}
Hours& Hours::operator+(const Hours& hours)
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

ostream& operator<<(ostream& os, Hours hours)
{
	os << hours.hour << ":" << hours.minute;
	return os;
}
istream& operator>>(istream& is, Hours hours)
{
	is >> hours.hour >> hours.minute;
	return is;
}

//----------------------------------------------------------------------
//TIME class

TIME::TIME()
{
	readfile = NULL;
	ForTree = new Hours[4];
	ForAllTime = new Hours[4];
}

void TIME::AddInTree()
{
	ReadFile* pv = readfile, *prew = NULL;
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
ReadFile* TIME::GetTree()
{
	return readfile;
}
void TIME::PrintTree(ReadFile* readfile, ostream& out)
{
	if (readfile)
	{
		TIME::PrintTree(readfile->left, out);

		out << readfile->Date << endl;
		out << readfile->japanese << endl;
		out << readfile->english << endl;
		out << readfile->programing << endl;
		out << readfile->math << endl;

		TIME::PrintTree(readfile->right, out);
	}
}

void TIME::SetTime(string Date, Hours japanese, Hours english, Hours programming, Hours math)
{
	date = Date;
	ForTree[0] = japanese;
	ForTree[1] = english;
	ForTree[2] = programming;
	ForTree[3] = math;
}
void TIME::FindInTree(string D)
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
		cout << "唢铐耜栝:        " << pv->japanese << endl;
		cout << "理汶栝耜栝:      " << pv->english << endl;
		cout << "橡钽疣祆痤忄龛�: " << pv->programing << endl;
		cout << "锑蝈爨蜩赅:      " << pv->math << endl;
		return;
	}
}
void TIME::FindInTreeComplex(string firstDate, string secondDate)
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
			cout << "***************" << pv->Date << "*******************" << endl;
			cout << "唢铐耜栝:        " << pv->japanese << endl;
			cout << "理汶栝耜栝:      " << pv->english << endl;
			cout << "橡钽疣祆痤忄龛�: " << pv->programing << endl;
			cout << "锑蝈爨蜩赅:      " << pv->math << endl;

			if (secondDate > pv->Date) pv = pv->right;
			else pv = pv->left;
		}
		return; 
	}

}

void TIME::SetTimeAll(ReadFile* readfile)
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
Hours TIME::GetJapanese()
{
	return ForAllTime[0];
}
Hours TIME::GetEnglish()
{
	return ForAllTime[1];
}
Hours TIME::GetProgramming()
{
	return ForAllTime[2];
}
Hours TIME::GetMath()
{
	return ForAllTime[3];
}
