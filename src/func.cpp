/*
 * func.cpp
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
#include <fstream>
#include <cstdlib>
using namespace std;
#include "panic.h"

void finish(bool success, const char *pwd, const int pastTime)
{
    system("clear");
    if(success)
    {
        printf("correct password :\"%s\"\n", pwd);
        if(pastTime > 0)
    		printf("Time elapsed %02d:%02d:%02d\n", pastTime/3600, pastTime%3600/60, pastTime%60);
        exit(0);
    }
    else
    {
        printf("Correct password not found.\n");
		if(pastTime > 0)
    		printf("Time elapsed %02d:%02d:%02d", pastTime/3600, pastTime%3600/60, pastTime%60);
        exit(1);
    }
}


bool readConfig(const char *filename, int &n, int &start, int &end, const int base, string &pwd)
{
	ifstream fin;
	try
	{
		fin.open(filename);
		if(!fin)
			terminate("Wrong file path.", 2, false);
		fin >> n >> start >> end >> pwd;
		fin.close();
	}
	catch(...)
	{
		terminate("Illegal path.", 2, false);
	}
	
	if(n < 1 || start < 0 || end < start || end > base)
		terminate("Incorrect config file.", 2, false);
	if(pwd.length() != 32)
		terminate("Incorrect MD5 string inputed.", 2, false);
	return true;
}

bool readDictionary(const char *filename, const string pwd)
{
	ifstream fin;
	try
	{
		fin.open(filename);
		if(!fin)
			terminate("Wrong file path.", 2, false);
	}
	catch(...)
	{
		terminate("Illegal path.", 2, false);
	}

	string in_md5, in_word;
	while(fin)
	{
		fin >> in_md5 >> in_word;
		if(in_md5.size() != 32 || in_word.size() == 0)
			terminate("Illegal dictionary", 3, false);
		if(in_md5 == pwd)
		{
			fin.close();
			finish(true, pwd.c_str(), 0);
		}
	}
	fin.close();
	finish(false, "", 0);
	return true;
}
