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

	if(out.detectCycle() || c_out.detectCycle())
		cout << "Cycle detection error" << endl;

	struct And A1("a1"), A2("a2"), A3("a3");
	A1.addChild(&A2);
	A2.addChild(&A3);
	A3.addChild(&A1);

	if(A3.detectCycle())
		cout << "Cycle detected" << endl;
	else
		cout << " Error: cycle not detected" << endl;

	return 0;
}