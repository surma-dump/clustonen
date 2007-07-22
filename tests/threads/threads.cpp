/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <cstdio>
#include "ClustonenThread.h" 

class TestThread : public ClustonenThread
{
public:
	TestThread() ;
	void run(void* param) ;
};

TestThread::TestThread() : ClustonenThread()
{}

void TestThread::run(void* param)
{
	int *k = (int *)param;
	for (int i = 0; i < 10; i++)
		printf("Thread(%dsec int): %d\n", *k, i), fflush(stdout), sleep(*k)  ;
	printf ("Thread(%dsec int): finished!\n", *k) ;
	fflush(stdout) ;
}





int main()
{
	int int1=3,int2=2 ;
	TestThread t1, t2 ;
	t1.start(&int1) ;
	t2.start(&int2) ;
	t1.join() ;
	t2.join() ;
}
