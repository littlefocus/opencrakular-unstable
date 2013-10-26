#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void panic(string msg)
{
    cout << endl;
    cout << "\033[31mopenCrakular core panic!" << endl;
    cout << "debug information: " << msg << "\033[m" << endl;
    exit(0xFF);
}

void terminate(string msg, int ret, bool cancontinue)
{
	cout << msg << endl;
	/*if(cancontinue)
	{
		char choice = '\0';
		cout << "Continue?[Y/n]";
		cin >> choice;
		if(choice == 'Y')
			return;
		else
			exit(ret);
	}*/
	exit(ret);
}