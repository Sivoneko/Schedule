// Граффик.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "MyTime.h"
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

void Menu();

template<typename T>
void AddTime(T*);

string CreateDate();

inline string MakeTodayDate();

int main()
{
	setlocale(LC_ALL, "Russian");

	TIME first;
	string Date = MakeTodayDate();

	ifstream in("Everyday.txt", ios::in);
	string DateInFile;
	Hours* SubjectsStruct = new Hours[4];
	while (!in.eof())
	{
		getline(in, DateInFile);
		if (DateInFile.length() >= 8)
		{
			in >> SubjectsStruct[0] >> SubjectsStruct[1] >> SubjectsStruct[2] >> SubjectsStruct[3];
			first.SetTime(DateInFile, SubjectsStruct[0], SubjectsStruct[1], SubjectsStruct[2], SubjectsStruct[3]);
			first.AddInTree();
		}
	}
	in.close();
	ofstream out;
	char answer;
	do
	{
		char* Subjects[4] = { "Японский","Английский", "Программирование","Математика"};
		Menu();
		cout << "Введите вариант: ";
		cin >> answer;
		
		switch (answer)
		{
		case '1':
		{
			for (int i(0); i < 4; i++)
			{
				cout << "Введите время для " << Subjects[i] << ": " << endl;
				AddTime(&SubjectsStruct[i]);
			}
			first.SetTime(Date, SubjectsStruct[0], SubjectsStruct[1], SubjectsStruct[2], SubjectsStruct[3]);
			first.AddInTree();
			
			
			break;
		}
		case '2':
		{
			string SomeDay;
			SomeDay = CreateDate();
			for (int i(0); i < 4; i++)
			{
				cout << "Введите время для " << Subjects[i] << ": " << endl;
				AddTime(&SubjectsStruct[i]);
			}
			first.SetTime(SomeDay, SubjectsStruct[0], SubjectsStruct[1], SubjectsStruct[2], SubjectsStruct[3]);
			first.AddInTree();
			break;
		}
		case '3':
		{
			string DateForSearch;
			DateForSearch = CreateDate();
			cout << "Ищем по дате: " << DateForSearch << endl;
			first.FindInTree(DateForSearch);
			break;
		}
		case '4':
		{
			string DateForSearch1, DateForSearch2;

			DateForSearch1 = CreateDate();
			DateForSearch2 = CreateDate();

			first.FindInTreeComplex(DateForSearch1, DateForSearch2);
			break;
		}
		case '5':
		{
			first.SetTimeAll(first.GetTree());

			cout << "Японский:         " <<	first.GetJapanese()		<< endl;
			cout << "Английский:       " << first.GetEnglish()		<< endl;
			cout << "Программирование: " << first.GetProgramming()	<< endl;
			cout << "Математика:       " << first.GetMath()			<< endl;
			break;
		}
		default:
			break;
		}

	} while (answer != 'o');

	out.open("Everyday.txt", ios::out);
	first.PrintTree(first.GetTree(), out);
	out.close();
	_getch();
    return 0;
}

void Menu()
{
	cout << "1 - Внести время за сегодня \n";
	cout << "2 - Ввести время за указанный день\n";
	cout << "3 - Вывести время за определенный день\n";
	cout << "4 - Вывести время за определенный период\n";
	cout << "5 - Вывести все потраченное время\n";
	cout << "o - Выход" << endl;
}

template<typename T>
void AddTime(T* time)
{
	cout << "Enter Hours and Minutes: ";
	cin >> time->hour >> time->minute;
}

string CreateDate()
{
	string DateForSearch;
	int month, day, year;
	cout << "Введите дату: " << endl;
	cout << "День: " << endl;
	cin >> day;
	cout << "Месяц: ";
	cin >> month;
	cout << "Год: " << endl;
	cin >> year;

	DateForSearch = to_string(day) + "." + to_string(month) + "." + to_string(year);
	return DateForSearch;
}

inline string MakeTodayDate()
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	string Date = to_string(timeinfo->tm_mday) + "." + to_string(timeinfo->tm_mon + 1) + "." + to_string(1900 + timeinfo->tm_year);
	return Date;
}