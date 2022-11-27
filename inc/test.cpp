#include <iostream>
#include "defs.h"

int main() {

	struct Node in1(1, {}, {1}), in2(1, {}, {1});
	struct Node and2(2, {&in1, &in2}, {});
	struct Node out(0, {&and2}, {});

	computeOut(&and2);
	computeOut(&out);
	cout << "out = " << out.values.back() << "\n";

	return 0;
}