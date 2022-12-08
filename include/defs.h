#include <iostream>
#include <string>
#include "dynamic_bitset.h"

using namespace std;
using namespace sul;

// Abstract structure for Node representation
struct Node {
protected:
	vector<Node*> children; // Vector of Node* represents the input nodes
	dynamic_bitset<> value; // Output vector of values
public:
	Node(vector<Node*> _children = {}) : children(_children) {}
	Node(string _value) : value(_value) {}
	
	virtual bool computeOut(int i) = 0; // Virtual method to be overcharged in derived structures to compute output value

	void addChild(Node* N) { children.push_back(N); }
	bool getValue(int i) { return value[i]; } // Causes segfault if trying to access non initialized value
};

// Node is then derived to every sub-type which overcharge the computeOut method with corresponding logic formula

struct Signal : public Node {

	Signal(string _name, vector<Node*> _children = {}) : name(_name), Node(_children) {}
	Signal(string _name, string _value) : name(_name), Node(_value) {}

	virtual string getName() = 0;
	virtual size_t getSize() = 0;

protected:
	string name;
};

struct Output : public Signal {

	Output(string _name, vector<Node*> _children = {}) : Signal(_name, _children) {}

	bool computeOut(int i) {
		value.push_back(children.back()->computeOut(i));
		return value[i];
	}

	string getName() { return name; }
	size_t getSize() { return value.size(); }
};

struct Input : public Signal {

	Input(string _name, string _value) : Signal(_name, _value) {}

	bool computeOut(int i) {
		return value[i];
	}

	string getName() { return name; }
	size_t getSize() { return value.size(); }
};

struct And : public Node {

	And(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(children.front()->computeOut(i) & children.back()->computeOut(i));
		return value[i];
	}
};

struct Or : public Node {

	Or(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(children.front()->computeOut(i) | children.back()->computeOut(i));
		return value[i];
	}
};

struct Xor : public Node {

	Xor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(children.front()->computeOut(i) ^ children.back()->computeOut(i));
		return value[i];
	}
};

struct Not : public Node {

	Not(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i)));
		return value[i];
	}
};

struct Nand : public Node {

	Nand(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) & children.back()->computeOut(i)));
		return value[i];
	}
};

struct Nor : public Node {

	Nor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) | children.back()->computeOut(i)));
		return value[i];
	}
};

struct Xnor : public Node {

	Xnor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back(~(children.front()->computeOut(i) ^ children.back()->computeOut(i)));
		return value[i];
	}
};


// Mux has strict in-order inputs : first and second are data, third is selection
struct Mux : public Node {

	Mux(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		if(i >= value.size())
			value.push_back((children.at(0)->computeOut(i) & children.back()->computeOut(i)) | (children.at(1)->computeOut(i) & ~(children.back()->computeOut(i))));
		return value[i];
	}
};
