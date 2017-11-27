#include "shift_register.h"
#include <iostream>
#include <stdio.h>

int main()
{
	Shift_register test_register;
	
	printf("test register info:\n");
	printf("length is %d\n", test_register.getLength());
	printf("start is %d\n", test_register.getStart());
	printf("end is %d\n", test_register.getEnd());
	
	printf("contents are:\n");

	test_register.shift_in(0+1j);	
	test_register.shift_in(0+1j);
	test_register.shift_in(0-1j);
	test_register.shift_in(0-1j);

	
	for (int i = 0; i < test_register.getLength(); i++) {
		printf("%d\n", i);
		printf("%f %fj\n", test_register.value(i).real(), test_register.value(i).imag());
	}

	printf("test register info:\n");
	printf("length is %d\n", test_register.getLength());
	printf("start is %d\n", test_register.getStart());
	printf("end is %d\n", test_register.getEnd());

	gr_complex searcher_result = 
	

	return 0;
}
