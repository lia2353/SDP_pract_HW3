#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class Student
{
private:
    unsigned long long FN;
    char FirstName[257], LastName[257];
    int Grade;
public:
    Student(unsigned long long =0, char* = "\0", char* = "\0", int = 0);

    unsigned long long getFN() const;
    const char* getFirstName() const;
    const  char* getLastName() const;
	int getGrade() const;

	friend ostream& operator<<(ostream&, Student&);
	friend istream& operator>>(istream&, Student&);
};

Student::Student(unsigned long long fn, char* fname, char* lname, int grade)
{
	FN = fn;
	strcpy(FirstName, fname);
	strcpy(LastName, lname);
	Grade = grade;
}

unsigned long long Student::getFN() const
{
    return FN;
}

const char* Student::getFirstName() const
{
	return FirstName;
}

const char* Student::getLastName() const
{
	return LastName;
}

int Student::getGrade() const
{
	return Grade;
}


ostream & operator<<(ostream & os, Student & obj)
{
	os << obj.FN << ' ' << obj.FirstName << ' ' << obj.LastName << ' ' << obj.Grade << '\n';
	return os;
}


istream& operator>>(istream& is, Student& obj)
{
	is >> obj.FN >> obj.FirstName >> obj.LastName >> obj.Grade;
	return is;
}



struct IndexFacNum
{
    unsigned long long FN;
    unsigned int index;

    IndexFacNum(unsigned long long newFN = 0, unsigned int newIndex = 0): FN(newFN), index(newIndex) {}

    friend ostream& operator<<(ostream&, IndexFacNum&);
};

ostream & operator<<(ostream & os, IndexFacNum & obj)
{
	os << obj.FN << ' ' << obj.index << '\n';
	return os;
}

#endif // STUDENT_H_INCLUDED
