#include "write_wave.h"

int main() {

	/* FULL ADDER schematic */
	struct Input in1("A", {0, 1, 0, 1, 0, 1, 0, 1}), in2("B", {0, 0, 1, 1, 0, 0, 1, 1}), cin("Cin", {0, 0, 0, 0, 1, 1, 1, 1});
	struct Xor xor2_1({&in1, &in2}), xor2_2({&xor2_1, &cin});
	struct And and2_1({&in1, &in2}), and2_2({&xor2_1, &cin});
	struct Or or2({&and2_1, &and2_2});
	struct Output out("S", {&xor2_2}), c_out("Cout", {&or2});

	vector<Signal*> signals({&in1, &in2, &cin, &out, &c_out});

	for(size_t i = 0; i < in1.getSize(); i++) {
		out.computeOut(i);
		c_out.computeOut(i);
		cout << "out = " << out.getValue(i) << "  c_out = " << c_out.getValue(i) << endl;
	}

	create_file(signals);

	return 0;
}