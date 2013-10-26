/*
 * try.cpp
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

extern string pwd;
extern int n, start, end;
extern int dbg;

namespace nmFeatTry
{
	int pastTime, remainTime;
	float progress;

	unsigned char cpwd[33];
	long long countNow = 0, countAll = 0, countMem = 0;
	char s[20];
	MD5 md5;

	void print_status()
	{
		system("clear");
		//fflush(stdout);
		pastTime++;
		progress = (float)(countNow*1.0/countAll)*100;
		if(progress >= 0.00001) //要不然除以零了
			remainTime = (int)(pastTime*100/progress) - pastTime;
		else
			remainTime = 0;
		printf("%s%s%s\n", ver, aut, bld);
		printf("Bits    : %d \n", n);
		printf("Range   : %d <= c1 < %d\n", start, end);
		printf("MD5     : %s\n", cpwd);

		if(dbg)
		{
			printf("pastTime, remainTime:%d, %d\n", pastTime, remainTime);
			printf("countNow, countAll:%lld, %lld\n", countNow, countAll);
		}

		printf("Progress: %lf%%\n", progress);
		printf("Speed   : %lld KP/s\n\n", (countNow-countMem)/1000);
		printf("Time remaining %02d:%02d:%02d\n", remainTime/3600, remainTime%3600/60, remainTime%60);
		countMem = countNow;
	}

	void dfs(int p)
	{
		if(p == n)
		{
		    ++countNow;
			md5.init();
			md5.update((unsigned char*)s, n);
			md5.finalize();
		    if(md5.hex_digest() == pwd)
		        finish(true, s, pastTime);
		}
		else
		{
		    for(int i = 0; i < base; i++)
		    {
		        s[p] = map[i];
		        dfs(p+1);
		    }
		}
	}

	void featTryMain()
	{
		countAll = pow(base, n-1) * (end-start);
		int p = getpid(), i = 0;

		if(fork() == 0)
		{
		    while(true)
		    {
		        kill(p, SIGUSR1);
		        sleep(1);
		    }
		    exit(0);
		}
		else
		{
			memcpy(cpwd, pwd.c_str(), pwd.length());
		    if(signal(SIGUSR1, (void(*)(int))print_status) == SIG_ERR)
				panic("Signal registry failed.");
		    for(i = start; i < end; i++)
			{
				s[0] = map[i];
				dfs(1);
			}
			finish(false, "", 0);
		}
	}

} //namespace nmFeatTry