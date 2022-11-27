#include <iostream>
#include <vector>

using namespace std;

#define OUTPUT 0
#define INPUT  1
#define AND    2
#define OR	   3
#define XOR    4
#define NOT    5
#define NAND   6
#define NOR    7
#define XNOR   8
#define MUX    9
#define FF     10

struct Node {
	unsigned int type;
	vector<Node*> children;
	vector<bool> values;

	Node(unsigned int _type, vector<Node*> _children = {}, vector<bool> _values = {}) : type(_type), children(_children), values(_values) {}
};

void computeOut(Node* N) {
	switch (N->type)
	{
	case OUTPUT :
		N->values.push_back(N->children.back()->values.back());
		break;
	case INPUT :
		break;
	case AND :
		N->values.push_back(N->children.at(0)->values.back() && N->children.at(1)->values.back());
		break;
	default :
		break;
	}
}