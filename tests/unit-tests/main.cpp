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

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestRunner.h>

int main (int argc, char* argv[])
{
	CPPUNIT_NS::TestResult testresult;
	CPPUNIT_NS::TestResultCollector collectedresults;
	CPPUNIT_NS::BriefTestProgressListener progress;
	
	testresult.addListener (&collectedresults);
	testresult.addListener (&progress);

	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);
	
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write();
	
	return collectedresults.wasSuccessful () ? 0 : 1;
}
