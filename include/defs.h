#include <iostream>
#include <string>
#include "dynamic_bitset.h"

using namespace std;
using namespace sul;

// Abstract structure for Node representation
struct Node {
protected:
	string name;
	vector<Node*> children; // Vector of Node* represents the input nodes
	dynamic_bitset<> value; // Output vector of values
public:
	Node(string _name, vector<Node*> _children = {}) : name(_name), children(_children) {}
	Node(string _name, string _value) : name(_name), value(_value) {}
	
	virtual dynamic_bitset<> computeOut() = 0; // Virtual method to be overcharged in derived structures to compute output value

	void addChild(Node* N) { children.push_back(N); }
	string getValue() { return value.to_string(); }
	string getName() { return name; }
	size_t getSize() { return value.size(); }
};

// Node is then derived to every sub-type which overcharge the computeOut method with corresponding logic formula

struct Output : public Node {

	Output(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		value = children.front()->computeOut();
		return value;
	}
};

struct Input : public Node {

	Input(string _name, string _value) : Node(_name, _value) {}

	dynamic_bitset<> computeOut() {
		return value;
	}
};

struct And : public Node {

	And(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value &= children[i]->computeOut();
			}
		}
		return value;
	}
};

struct Or : public Node {

	Or(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value |= children[i]->computeOut();
			}
		}
		return value;
	}
};

struct Xor : public Node {

	Xor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value ^= children[i]->computeOut();
			}
		}
		return value;
	}
};

struct Not : public Node {

	Not(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = ~(children.front()->computeOut());
		}
		return value;
	}
};

struct Nand : public Node {

	Nand(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value &= children[i]->computeOut();
			}
		}
		return ~value;
	}
};

struct Nor : public Node {

	Nor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value |= children[i]->computeOut();
			}
		}
		return ~value;
	}
};

struct Xnor : public Node {

	Xnor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = children.front()->computeOut();
			for(size_t i = 1; i < children.size(); i++) {
				value ^= children[i]->computeOut();
			}
		}
		return ~value;
	}
};


// Mux has strict in-order inputs : first and second are data, third is selection
struct Mux : public Node {

	Mux(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	dynamic_bitset<> computeOut() {
		if(value.size() == 0) {
			value = (children[0]->computeOut() & children.back()->computeOut()) | (children[1]->computeOut() & ~(children.back()->computeOut()));
		}
		return value;
	}
};
