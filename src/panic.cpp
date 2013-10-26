/*
 * panic.cpp
 * Copyright (C) 2013 DLab <DLaboratory@126.com>
 * 
 * Crakular is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Crakular is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You shoud have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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