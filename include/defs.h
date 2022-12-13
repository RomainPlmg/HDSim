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
	
	virtual bool computeOut(int i) = 0; // Virtual method to be overcharged in derived structures to compute output value

	void addChild(Node* N) { children.push_back(N); }
	bool getValue(int i) { return value[i]; }
	string getName() { return name; }
	size_t getSize() { return value.size(); }
};

// Node is then derived to every sub-type which overcharge the computeOut method with corresponding logic formula

struct Output : public Node {

	Output(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		value.push_back(children.back()->computeOut(i));
		return value[i];
	}
};

struct Input : public Node {

	Input(string _name, string _value) : Node(_name, _value) {}

	bool computeOut(int i) {
		return value[i];
	}

	string getName() { return name; }
	size_t getSize() { return value.size(); }
};

struct And : public Node {

	And(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size()) {
			value.push_back(children[0]->computeOut(i));
			for(size_t s = 1; s < children.size(); s++) {
				value[i] &= children[s]->computeOut(i);
			}
		}
		return value[i];
	}
};

struct Or : public Node {

	Or(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(children.front()->computeOut(i) | children.back()->computeOut(i));
		return value[i];
	}
};

struct Xor : public Node {

	Xor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(children.front()->computeOut(i) ^ children.back()->computeOut(i));
		return value[i];
	}
};

struct Not : public Node {

	Not(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i)));
		return value[i];
	}
};

struct Nand : public Node {

	Nand(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) & children.back()->computeOut(i)));
		return value[i];
	}
};

struct Nor : public Node {

	Nor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) | children.back()->computeOut(i)));
		return value[i];
	}
};

struct Xnor : public Node {

	Xnor(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) ^ children.back()->computeOut(i)));
		return value[i];
	}
};


// Mux has strict in-order inputs : first and second are data, third is selection
struct Mux : public Node {

	Mux(string _name, vector<Node*> _children = {}) : Node(_name, _children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back((children.at(0)->computeOut(i) & children.back()->computeOut(i)) | (children.at(1)->computeOut(i) & ~(children.back()->computeOut(i))));
		return value[i];
	}
};
