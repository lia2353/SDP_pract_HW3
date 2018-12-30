#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include"Student.h"
#include<fstream>
#include<cstring>

using namespace std;

unsigned int MIN_NUMBER_STUDENTS = 1000001;


void merge(IndexFacNum* arr, long left, long middle, long right)
{
    //temp arrays for sorting left and right sides of the array
    long sizeL = middle-left+1, sizeR =  right-middle;
    IndexFacNum* L = new IndexFacNum[sizeL];
    IndexFacNum* R = new IndexFacNum[sizeR];

    for(long i=0; i<sizeL; ++i)
        L[i] = arr[left+i];
    for(long i=0; i<sizeR; ++i)
        R[i] = arr[middle+1+i];

    long l = 0, r = 0, m = left;
    while(l<sizeL && r<sizeR)
    {
        if(L[l].FN <= R[r].FN)
            arr[m++] = L[l++];
        else
            arr[m++] = R[r++];
    }
    while(l<sizeL)
        arr[m++] = L[l++];
    while(r<sizeR)
        arr[m++] = R[r++];

    delete[] L;
    delete[] R;
}
void mergeSort(IndexFacNum* arr, long left, long right)
{
    if(right <= left)
        return;
    long middle = left+(right-left)/2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle+1, right);

    merge(arr, left, middle, right);
}

long binarySearch(ifstream& file, streampos left, streampos right, unsigned long long facNum)
{
    if(left > right)
    {
        return -1;
    }
    //temp object to store the pivot(middle of the file)
    IndexFacNum temp;
    streampos middle = (right+left)/2;
    file.seekg(middle*sizeof(IndexFacNum),ios::beg);
    file.read((char*)&temp, sizeof(IndexFacNum));

    if(temp.FN == facNum)
        return temp.index;
    if(temp.FN < facNum)
    {
        binarySearch(file, middle+1, right, facNum);
    }
    else
    {
        binarySearch(file, left, middle-1, facNum);
    }
}



void sequentialSearch()
{
    ifstream file;
    file.open("StudentsGrades.db", ios::in|ios::binary);
    if(!file)
    {
        cerr  << "ERROR: can't open this file\n";
        return;
    }

    //asks for the faculty number of the student whom the user wants to find
    unsigned long long facNum;
    cin >> facNum;

    //reads every student(line) from file in currStudent and checks whether it matches the searched faculty number
    Student currStudent;
    while (!file.eof())
	{
	    file.read((char*)&currStudent, sizeof(Student));
		if (currStudent.getFN() == facNum)
		{
			cout << currStudent;
			file.close();
			return;
		}
	}
	cout << "Record not found!\n";
	file.close();
}


void buildIndex()
{
    ifstream file;
    file.open("StudentsGrades.db", ios::in|ios::binary);
    //index file where objects{faculty number, index of student in StudentsGrades file} are stored
    ofstream indexFile;
    indexFile.open("FacultyNumber.ids", ios::out|ios::trunc|ios::binary);
    if(!file && !indexFile)
    {
        cerr  << "ERROR: can't open this files\n";
        return;
    }

    IndexFacNum* studentsArr = new IndexFacNum [MIN_NUMBER_STUDENTS];
    unsigned int capacity = MIN_NUMBER_STUDENTS, size = 0;
    //reads every student(line) from file in currStudent
    Student currStudent;
    while (!file.eof())
	{
	    file.read((char*)&currStudent, sizeof(Student));
		if(size >= capacity)
        {
            capacity *= 2;
            IndexFacNum* temp = studentsArr;
            studentsArr = new IndexFacNum[capacity];
            for(unsigned int i=0; i<size; i++)
                studentsArr[i] = temp[i];
            delete[] temp;
        }
        studentsArr[size] = IndexFacNum(currStudent.getFN(), size);
        ++size;
	}

    //sorts the array - n.log(n)
    --size;
    mergeSort(studentsArr, 0, size-1);

    //copies all IndexFacNum objects in the index-file
    for(unsigned int i=0; i<size; ++i)
    {
        indexFile.write((char*)&studentsArr[i], sizeof(IndexFacNum));
    }

    cout << "Index is built!\n";
    indexFile.close();
	file.close();
}


void search()
{
    ifstream indexFile;
    indexFile.open("FacultyNumber.ids", ios::in|ios::binary);
    //if the file doesn't exist, create it by calling bulidIndex()
    if(!indexFile)
    {
        buildIndex();
        indexFile.open("FacultyNumber.ids", ios::in|ios::binary);
    }

    //asks for the faculty number of the student whom the user wants to find
    unsigned long long facNum;
    cin >> facNum;

    //binary search of the faculty number in the sorted index file - log(n)
    streampos left, right;
    indexFile.seekg(0,ios::end);
	right = indexFile.tellg()/sizeof(IndexFacNum);
    indexFile.seekg(0,ios::beg);
	left = indexFile.tellg();
    long position = binarySearch(indexFile, left, right, facNum);

    //binerySearch function return -1 if searched faculty num doesn't exit
	if(position < 0)
    {
       cout << "Record not found!\n";
    }
    else
    {
        //if such faculty number exists, the function returns its position in StudentsGrades file
        //and the information for the student is read in constant time
        ifstream file;
        file.open("StudentsGrades.db", ios::in|ios::binary);
        file.seekg(position*sizeof(Student),ios::beg);
        Student searchedStudent;
        file.read((char*)&searchedStudent, sizeof(Student));
        cout << searchedStudent;

        file.close();
    }

	indexFile.close();
    return;
}

#endif // COMMAND_H_INCLUDED
