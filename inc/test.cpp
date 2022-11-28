#include <iostream>
#include "defs.h"

int main() {

	/* FULL ADDER schematic */
	struct Input in1({0}), in2({0}), cin({0});
	struct Xor xor2_1({&in1, &in2}), xor2_2({&xor2_1, &cin});
	struct And and2_1({&in1, &in2}), and2_2({&xor2_1, &cin});
	struct Or or2({&and2_1, &and2_2});
	struct Output out({&xor2_2});
	struct Output c_out({&or2});
	
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(1);
	in2.setValue(0);
	cin.setValue(0);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(0);
	in2.setValue(1);
	cin.setValue(0);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(1);
	in2.setValue(1);
	cin.setValue(0);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(0);
	in2.setValue(0);
	cin.setValue(1);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(1);
	in2.setValue(0);
	cin.setValue(1);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(0);
	in2.setValue(1);
	cin.setValue(1);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	in1.setValue(1);
	in2.setValue(1);
	cin.setValue(1);
	out.computeOut();
	cout << "out = " << out.getValue() << "\n";
	return 0;
}
