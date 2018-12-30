#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

#include<iostream>
#include<fstream>
#include<cstdlib>
#include <algorithm>

#include "Student.h"

const int MAX = 100000;

void createStudentsFile()
{
    ofstream file;
    file.open("StudentsGrades.db", ios::trunc|ios::binary);
    unsigned long long* FN = new unsigned long long [MAX];

    char alphanum[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    for(int i = 0; i<MAX; ++i)
    {
        unsigned long x;
        x = rand();
        x <<= 15;
        x ^= rand();
        x %= 100000001;
        x = (i < 700000)? x + rand() * 10000 : x + rand() * 1060000;
        FN[i] = (i==0)? 1+x : FN[i-1] + x;
    }
    random_shuffle(&FN[0], &FN[MAX-1]);
    random_shuffle(&FN[0], &FN[MAX-1]);


    for(int i=0; i<MAX; i++)
    {
        char firstName[21], secondName[21];
        for (int j=0; j<20; ++j)
        {
            firstName[j] = alphanum[rand() % 51];
            secondName[j] = alphanum[rand() % 51];
        }
        firstName[20] = '\0';
        secondName[20] = '\0';
        int grade = (rand() % (6 + 1 - 2)) + 2;

        Student temp(FN[i], firstName, secondName, grade);
        file.write((char*)&temp, sizeof(Student));
    }

    delete[] FN;
    file.close();
}
#endif // GENERATE_H_INCLUDED
