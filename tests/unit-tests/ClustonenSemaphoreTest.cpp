/**
 * Copyright (C) 2007  Andi Drebes <hackbert@drebesium.org>
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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ClustonenSemaphore.h"
#include "ClustonenThread.h"
#include "ClustonenMutex.h"

using namespace std;
#define SEMA_VALUE 10
#define NUM_THREADS 10

#include <iostream>

class ConsumerThread : public ClustonenThread
{
	public:
		ConsumerThread(ClustonenMutex* crit_mutex, ClustonenSemaphore* crit_sema_in, ClustonenSemaphore* crit_sema_out, int* crit_num)
			: crit_mutex(crit_mutex), crit_sema_in(crit_sema_in), crit_sema_out(crit_sema_out), crit_num(crit_num)
		{
		}
		
		void run(void* param)
		{
			//try to enter critical region
			crit_sema_in->down();

			//increase the number of threads currently in the critical region
			crit_mutex->lock();
				(*crit_num)++;
			crit_mutex->unlock();
			
			//wait for the controller thread to let all the threads out
			crit_sema_out->down();

			//restore semaphore state
			crit_sema_in->up();

			//decrease the number of threads currently in the critical region
			crit_mutex->lock();
				(*crit_num)--;
			crit_mutex->unlock();
		}

	protected:
		ClustonenMutex* crit_mutex;
		ClustonenSemaphore* crit_sema_in;
		ClustonenSemaphore* crit_sema_out;
		int* crit_num;
};

class ControllerThread : public ClustonenThread
{
	public:
		ControllerThread(ClustonenMutex* crit_mutex, ClustonenSemaphore* crit_sema_in, ClustonenSemaphore* crit_sema_out, int* crit_num)
			: crit_mutex(crit_mutex), crit_sema_in(crit_sema_in), crit_sema_out(crit_sema_out), crit_num(crit_num)
		{
		}
	
		void run(void* param)
		{
			//Wait for all consumers to enter the critical region
			while(true)
			{
				crit_mutex->lock();
					if(*crit_num == NUM_THREADS)
					{
						crit_mutex->unlock();
						goto let_threads_out;
					}
				crit_mutex->unlock();
			}
		
let_threads_out:
			CPPUNIT_ASSERT(*crit_num == NUM_THREADS);
			
			//Let all the threads out of the critical region
			for(int i = 0; i < NUM_THREADS; ++i)
				crit_sema_out->up();

			//Wait for all consumers to leave in the critical region
			while(true)
			{
				crit_mutex->lock();
					if(*crit_num == 0)
					{
						crit_mutex->unlock();
						return;
					}
				crit_mutex->unlock();
			}
		}
	
	protected:
		ClustonenMutex* crit_mutex;
		ClustonenSemaphore* crit_sema_in;
		ClustonenSemaphore* crit_sema_out;
		int* crit_num;
};

class ClustonenSemaphoreTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (ClustonenSemaphoreTest);
	CPPUNIT_TEST (initTest);
	CPPUNIT_TEST (updownTest);
	CPPUNIT_TEST (tryDownTest);
	CPPUNIT_TEST (criticalRegionTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void initTest (void);
		void updownTest (void);
		void tryDownTest (void);
		void criticalRegionTest (void);
		
	private:
		ClustonenSemaphore* sema;
};

CPPUNIT_TEST_SUITE_REGISTRATION (ClustonenSemaphoreTest);

void ClustonenSemaphoreTest::setUp(void)
{
	CPPUNIT_ASSERT_NO_THROW(sema = new ClustonenSemaphore(SEMA_VALUE));
}

void ClustonenSemaphoreTest::tearDown(void)
{
	CPPUNIT_ASSERT_NO_THROW(delete sema);
}

/**
 * Tests wether a semaphore's value is initialized correctly.
 */
void ClustonenSemaphoreTest::initTest(void)
{
	CPPUNIT_ASSERT(sema->getValue() == SEMA_VALUE);
}

/**
 * Tests wether up() and down() have the right
 * behaviour (single threaded).
 */
void ClustonenSemaphoreTest::updownTest(void)
{
	CPPUNIT_ASSERT_NO_THROW(sema->down());
	CPPUNIT_ASSERT(sema->getValue() == SEMA_VALUE-1);
	CPPUNIT_ASSERT_NO_THROW(sema->down());
	CPPUNIT_ASSERT(sema->getValue() == SEMA_VALUE-2);
	
	CPPUNIT_ASSERT_NO_THROW(sema->up());
	CPPUNIT_ASSERT(sema->getValue() == SEMA_VALUE-1);
	CPPUNIT_ASSERT_NO_THROW(sema->up());
	CPPUNIT_ASSERT(sema->getValue() == SEMA_VALUE);
}

/**
 * Tests wether tryDown() works (single threaded).
 */
void ClustonenSemaphoreTest::tryDownTest(void)
{
	for(unsigned int i = 0; i < SEMA_VALUE; ++i)
		CPPUNIT_ASSERT_NO_THROW(sema->down());
	
	CPPUNIT_ASSERT(sema->getValue() == 0);
	CPPUNIT_ASSERT(!sema->tryDown());
	CPPUNIT_ASSERT_NO_THROW(sema->up());
	CPPUNIT_ASSERT(sema->tryDown());
	
	for(unsigned int i = 0; i < SEMA_VALUE; ++i)
		CPPUNIT_ASSERT_NO_THROW(sema->up());
}

/**
 * Tests if a (non-binary) semaphore lets several independent
 * threads enter a critical region.
 */
void ClustonenSemaphoreTest::criticalRegionTest(void)
{
	ClustonenMutex crit_mutex;
	ClustonenSemaphore crit_sema_in(NUM_THREADS);
	ClustonenSemaphore crit_sema_out(0);
	int crit_num = 0;
	ConsumerThread* threads[NUM_THREADS];
	ControllerThread* controller;
	
	for(int i = 0; i < NUM_THREADS; ++i) {
		threads[i] = new ConsumerThread(&crit_mutex, &crit_sema_in, &crit_sema_out, &crit_num);
		threads[i]->start(NULL);
	}

	controller = new ControllerThread(&crit_mutex, &crit_sema_in, &crit_sema_out, &crit_num);
	controller->start(NULL);
	controller->join();
	delete controller;
	
	for(int i = 0; i < NUM_THREADS; ++i) {
		threads[i]->join();
		delete threads[i];
	}
}
