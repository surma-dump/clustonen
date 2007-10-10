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
#include "ClustonenThread.h"

using namespace std;

class ClustonenThreadTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (ClustonenThreadTest);
	CPPUNIT_TEST (killTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void killTest (void);

	private:
		
};

class KillThread : public ClustonenThread
{
	void run(void* param)
	{
		while(true) { ;; }
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (ClustonenThreadTest);

void ClustonenThreadTest::setUp(void)
{

}

void ClustonenThreadTest::tearDown(void)
{

}

void ClustonenThreadTest::killTest(void)
{
	KillThread* thr;
	CPPUNIT_ASSERT_NO_THROW(thr = new KillThread());
	CPPUNIT_ASSERT(!thr->isRunning());
	thr->start(NULL);

	CPPUNIT_ASSERT(thr->isRunning());
	CPPUNIT_ASSERT_NO_THROW(thr->kill());
	CPPUNIT_ASSERT(!thr->isRunning());

	//The thread runs an infinity loop. So if
	//kill() was successful, then join() doesn't
	//wait
	thr->join();
	CPPUNIT_ASSERT_NO_THROW(delete thr);
}
