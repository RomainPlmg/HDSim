#include <iostream>
#include "defs.h"

int main() {

	/* FULL ADDER schematic */
	struct Input in1({0, 1, 0, 1, 0, 1, 0, 1}), in2({0, 0, 1, 1, 0, 0, 1, 1}), cin({0, 0, 0, 0, 1, 1, 1, 1});
	struct Xor xor2_1({&in1, &in2}), xor2_2({&xor2_1, &cin});
	struct And and2_1({&in1, &in2}), and2_2({&xor2_1, &cin});
	struct Or or2({&and2_1, &and2_2});
	struct Output out({&xor2_2});
	struct Output c_out({&or2});
	
	for(int i=0; i < 8; i++) {
		out.computeOut(i);
		cout << "out = " << out.getValue(i) << "\n";
	}

	return 0;
}
