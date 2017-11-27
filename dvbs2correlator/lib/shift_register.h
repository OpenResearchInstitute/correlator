// shift_register.h
#include <gnuradio/gr_complex.h>
#include <vector>
using namespace std;


gr_complex[] SOF;
 
class Shift_register {
	int length; 
	int start;
	int end;
	std::vector<gr_complex> register_name; 
   public:
	Shift_register(); //a constructor 
	Shift_register(int my_length, int my_start, int my_end); //fully specified constructor

	int getLength(); //get the length of the register
	void setStart(int my_start); //set the index of the start
	int getStart(); //get the index of the start
	void setEnd(int my_end); //set the index of the end
	int getEnd(); //get the index of the end

	void shift_in(gr_complex); //shift value into shift register
	gr_complex value(int my_index); //get single value
	
};


