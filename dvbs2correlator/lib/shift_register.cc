// shift_register.cc

#include "shift_register.h"

//Member function definitions

//Default constructor. We provide length. Start and end are 0 and length-1.
Shift_register::Shift_register() {
	length = 25;
	start = 0;
	end = length - 1; 
	register_name = std::vector<gr_complex>(length);
}	

Shift_register::Shift_register(int length, int start, int end) {
	int my_length = length;
	int my_start = start;
	int my_end = end;
	register_name = std::vector<gr_complex>(length);
}

void Shift_register::shift_in(gr_complex sample) {
	register_name[start] = sample;
	start = (start+1)%length;
	end = (end+1)%length;
}


int Shift_register::getLength() {
	return length;
}


void Shift_register::setStart(int new_start) {
	start = new_start;	
}

int Shift_register::getStart() {
	return start;
}

void Shift_register::setEnd(int new_end) {
	end = new_end;
}

int Shift_register::getEnd() {
	return end;
}

gr_complex Shift_register::value(int my_index) {
	gr_complex value;	
	value = register_name[my_index];
	return value;
}
