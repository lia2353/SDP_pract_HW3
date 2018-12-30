#include <iostream>
#include "OperationParser.h"
#include "generate.h"

using namespace std;

int main()
{
    //creates file with students
    //createStudentsFile();
    //cout << "ready\n";

    OperationParser parser;

    //asks for operation (sequentialSearch, buildIndex, search, exit)
    cin >> parser;

    //asks the user to enter an operation till entering exit
    while (parser.getOperation() != "exit")
	{
		parser.doOperation();
		//asks for operation (sequentialSearch, buildIndex, search, exit)
		cin >> parser;
	}
    return 0;
}

