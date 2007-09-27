 
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
#include "ClustonenMessage.h"

using namespace std;

class ClustonenMessageTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (ClustonenMessageTest);
	CPPUNIT_TEST (initTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void initTest (void);
		void wrongValueTest (void);
		void nonexistentFileTest(void);

	private:
		
};

CPPUNIT_TEST_SUITE_REGISTRATION (ClustonenMessageTest);

void ClustonenMessageTest::setUp(void)
{

}

void ClustonenMessageTest::tearDown(void)
{

}

/*
 * Initializes a message with a name and data and checks
 * if the data is parsed correctly
 */
void ClustonenMessageTest::initTest(void)
{
	ClustonenMessage *msg = new ClustonenMessage("a_message", "foo='bar'; "
		"longer='baz doz'; "
		"fieldwithapostroph='apostroph\\''; "
		"moreapostrophes='\'\'\'';");
	
	CPPUNIT_ASSERT(msg->getName() == "a_message");
	CPPUNIT_ASSERT(msg->getField("foo") == "bar");
	CPPUNIT_ASSERT(msg->getField("longer") == "baz doz");
	
	CPPUNIT_ASSERT(msg->getField("fieldwithapostroph") == "apostroph'");
	CPPUNIT_ASSERT(msg->getField("moreapostrophes") == "'''");
		
	delete msg;
}
