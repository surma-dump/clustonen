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
#include "ConfigFileParser.h"

using namespace std;

class ConfigFileParserTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (ConfigFileParserTest);
	CPPUNIT_TEST (valueTest);
	CPPUNIT_TEST(multiValueTest);
	CPPUNIT_TEST (wrongValueTest);
	CPPUNIT_TEST (nonexistentFileTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void valueTest (void);
		void multiValueTest (void);
		void wrongValueTest (void);
		void nonexistentFileTest(void);

	private:
		ConfigFileParser *a;
};

CPPUNIT_TEST_SUITE_REGISTRATION (ConfigFileParserTest);

void ConfigFileParserTest::setUp(void)
{
	CPPUNIT_ASSERT_NO_THROW(a = new ConfigFileParser("./testdata/testconfiguration"));
	CPPUNIT_ASSERT_NO_THROW(a->parse());
}

void ConfigFileParserTest::tearDown(void)
{
	delete a;
}

/*
 * Reads values from the config file and checks if they are right
 */
void ConfigFileParserTest::valueTest(void)
{
	CPPUNIT_ASSERT(a->getValue("foo") == "bar");
	CPPUNIT_ASSERT(a->getValue("sense_of_life") == "42");
	CPPUNIT_ASSERT(a->getValue("linux") == "great");
}

/*
 * Reads multivalues from the config file and checks if they are right
 */
void ConfigFileParserTest::multiValueTest(void)
{
	ConfigFileParser* b;
	CPPUNIT_ASSERT_NO_THROW(b = new ConfigFileParser("./testdata/testconfiguration_multi"));
	b->addMultiValueToken("load");
	CPPUNIT_ASSERT_NO_THROW(b->parse());

	CPPUNIT_ASSERT(b->getNumValues() == 2);
	CPPUNIT_ASSERT(b->getValue("aname") == "avalue");

	std::vector<std::string> vec = b->getMultiValue("load");
	CPPUNIT_ASSERT(vec.size() == 4);

	CPPUNIT_ASSERT(find(vec.begin(), vec.end(), "foo.so") != vec.end());
	CPPUNIT_ASSERT(find(vec.begin(), vec.end(), "bar.so") != vec.end());
	CPPUNIT_ASSERT(find(vec.begin(), vec.end(), "baz.so") != vec.end());
	CPPUNIT_ASSERT(find(vec.begin(), vec.end(), "doz.so") != vec.end());
	delete b;
}

/*
 * Tries to read values that are nonexistent and checks if
 * the value of nondeclared symbols is ""
 */
void ConfigFileParserTest::wrongValueTest(void)
{
	//existent name, but wrong value
	CPPUNIT_ASSERT(a->getValue("foo") != "bazdoz");
	CPPUNIT_ASSERT(a->getValue("foo") != "");
	
	//non-existent name
	CPPUNIT_ASSERT(a->getValue("yetanothervalue") == "");
	CPPUNIT_ASSERT(a->getValue("notdeclared") == "");
}

/*
 * Tries to parse a nonexistent file and checks for an exception
 */
void ConfigFileParserTest::nonexistentFileTest(void)
{
	ConfigFileParser *tmp = new ConfigFileParser("./testdata/nofile");
	CPPUNIT_ASSERT_THROW(tmp->parse(), ConfigFileParserException);
	delete tmp;
}
