/*
 * main.cpp
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

#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
using namespace std;
#include "md5lib.h"
#include "panic.h"
#include "func.h"
#include "Glb.h"
#include "try.h"

int dbg = 0, feat = 0;
string pwd;
int n, start, end;

int main(int argc, char** argv)
{
	srand(time(NULL));
	printf("%s%s%s\n", ver, aut, bld);

	//opencrakular try ./crakular-config
	//opencrakular dict ./crakular-config ./dictionary
	if(argc < 3)
		terminate("Wrong arguments.\nPlease read user manual to get more information.\n", 1, false);
	
	if(strcmp(argv[1], "try") == 0)
		feat = FEAT_TRY;
	else if(argc >= 4 && strcmp(argv[1], "dict") == 0)
		feat = FEAT_READ_DICT;
	else if(argc >= 4 && strcmp(argv[1], "build-dict") == 0)
		feat = FEAT_BUILD_DICT;
	else
		terminate("Wrong arguments.\nPlease read user manual to get more information.\n", 1, false);
	
	if(argc >= 4 && strcmp(argv[3], "--dbg") == 0)
		dbg = 1;

	switch(feat)
	{
		case FEAT_TRY:
			readConfig(argv[2], n, start, end, base, pwd);
			if(n > 12)
				terminate("More than 12 Bits are not supported yet.", 1, false);
			nmFeatTry::featTryMain();
			break;
		case FEAT_READ_DICT:
			readConfig(argv[2], n, start, end, base, pwd);
			readDictionary(argv[3], pwd);
			break;
		default:
			panic("no feature started.");
	}
	
    return 0;
}
