// shift_register_TestRunner.cc

#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "shift_register_unit_test.h"

using namespace std;

int main() {
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	
	cout << "Creating Awesome Test Suites:" << endl;
	runner.addTest( registry.makeTest() );

	cout << "Running the Unit Tests. " << endl;

	runner.run();
	return 0;	
	//bool wasSuccessful = runner.run( "", false );
	//return !wasSuccessful;
}
