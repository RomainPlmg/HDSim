#include <iostream>
#include "defs.h"

int main() {

	struct Input in1({1}), in2({1});
	struct And and2({&in1, &in2});
	struct Output out({&and2});
	out.computeOut();
	cout << "out = " << out.values.back() << "\n";

	return 0;
}