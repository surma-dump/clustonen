 
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
#include "strhelper.h"
#include <iostream>

using namespace std;

class strhelperTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (strhelperTest);
	CPPUNIT_TEST (trimTest);
	CPPUNIT_TEST (replacestrTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void trimTest (void);
		void replacestrTest (void);

	private:
		
};

CPPUNIT_TEST_SUITE_REGISTRATION (strhelperTest);

void strhelperTest::setUp(void)
{

}

void strhelperTest::tearDown(void)
{

}

/*
 * Checks if trim() works correctly
 */
void strhelperTest::trimTest(void)
{
	std::string a = "    a              		";
	trim(a);
	CPPUNIT_ASSERT(a == "a");
	
	a = "    a a             		";
	trim(a);
	CPPUNIT_ASSERT(a != "aa");
	
	a = "teststring";
	trim(a);
	CPPUNIT_ASSERT(a == "teststring");
	
	a = "teststring";
	trim(a, "tg");
	CPPUNIT_ASSERT(a == "eststrin");
}

/*
 * Checks if replacestr() works correctly
 */
void strhelperTest::replacestrTest(void)
{
	std::string a = "aaa";
	
	replacestr("a", "b", a);
	CPPUNIT_ASSERT(a == "bbb");
	
	a = "aaa";
	replacestr("aa", "b", a);
	CPPUNIT_ASSERT(a == "ba");
	
	a = "That is a test.";
	replacestr("is", "was", a);
	CPPUNIT_ASSERT(a == "That was a test.");
}

