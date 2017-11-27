// shift_register_unit_test.h

/*
class ComplexNumberTest : public CppUnit::TestCase { 
public: 
  ComplexNumberTest( std::string name ) : CppUnit::TestCase( name ) {}
  
  void runTest() {
    CPPUNIT_ASSERT( Complex (10, 1) == Complex (10, 1) );
    CPPUNIT_ASSERT( !(Complex (1, 1) == Complex (2, 2)) );
  }
};
*/

#include "shift_register.h"
#include <cppunit/TestCase.h>

class Shift_registerTest : public CppUnit::TestCase {
public:
	Shift_registerTest(std::string name) : CppUnit::TestCase(name) {}

    void runTest() {
	//Shift_register shiftreg = Shift_register(10);
	//shiftreg.shift_in(1+1j);
	CPPUNIT_ASSERT( shiftreg.value(0).real() == 1.0 ); 
	CPPUNIT_ASSERT( shiftreg.value(0).imag() == 1.0 );
}
};
