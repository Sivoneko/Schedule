#pragma once
#include <iostream>
#include <string>
using namespace std;
struct Hours
{
	Hours();
	int hour;
	int minute;

	Hours& operator=(const Hours&);
	Hours& operator+(const Hours&);
	friend ostream& operator<<(ostream&, Hours);
	friend istream& operator>>(istream&, Hours);
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
	ReadFile * readfile;
	string date;
	Hours* ForTree;
	Hours* ForAllTime;
public:
	TIME();

	void AddInTree();
	ReadFile* GetTree();
	void PrintTree(ReadFile*, ostream&);

	void SetTime(string, Hours, Hours, Hours, Hours);
	void FindInTree(string);
	void FindInTreeComplex(string, string);

	void SetTimeAll(ReadFile*);
	Hours GetJapanese();
	Hours GetEnglish();
	Hours GetProgramming();
	Hours GetMath();
};