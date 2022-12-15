#include "write_wave.h"

int main() {

	/* FULL ADDER schematic */
	struct Input in1("A", "01010101"), in2("B", "00110011"), cin("Cin", "00001111");
	struct Xor xor2_1("xor1", {&in1, &in2}), xor2_2("xor2", {&xor2_1, &cin});
	struct And and2_1("and", {&in1, &in2}), and2_2("and2", {&xor2_1, &cin});
	struct Or or2("or1", {&and2_1, &and2_2});
	struct Output out("S", {&xor2_2}), c_out("Cout", {&or2});

	vector<Node*> signals({&in1, &in2, &cin, &out, &c_out});

	out.computeOut();
	c_out.computeOut();

	cout << "out = " << out.getValue() << "  c_out = " << c_out.getValue() << endl;

	create_file(signals);

	return 0;
}