#include <iostream>
#include <vector>

using namespace std;

struct Node {
protected:
	vector<Node*> children;
	vector<bool> value;
public:
	Node(vector<Node*> _children = {}) : children(_children) {}
	Node(vector<bool> _value = {}) : value(_value) {}
	
	virtual bool computeOut(int i) = 0;

	void addChild(Node* N) { children.push_back(N); }
	bool getValue(int i) { return value[i]; }
};

struct Output : public Node {

	Output(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(children.back()->computeOut(i));
		return value[i];
	}
};

struct Input : public Node {

	Input(vector<bool> _value = {}) : Node(_value) {}

	bool computeOut(int i) {
		return this->getValue(i);
	}
};

struct And : public Node {

	And(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(children.front()->computeOut(i) && children.back()->computeOut(i));
		return value[i];
	}
};

struct Or : public Node {

	Or(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(children.front()->computeOut(i) || children.back()->computeOut(i));
		return value[i];
	}
};

struct Xor : public Node {

	Xor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(children.front()->computeOut(i) ^ children.back()->computeOut(i));
		return value[i];
	}
};

struct Not : public Node {

	Not(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(~(children.front()->computeOut(i)));
		return value[i];
	}
};

struct Nand : public Node {

	Nand(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(~(children.front()->computeOut(i) && children.back()->computeOut(i)));
		return value[i];
	}
};

struct Nor : public Node {

	Nor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(~(children.front()->computeOut(i) || children.back()->computeOut(i)));
		return value[i];
	}
};

struct Xnor : public Node {

	Xnor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back(~(children.front()->computeOut(i) ^ children.back()->computeOut(i)));
		return value[i];
	}
};

struct Mux : public Node {

	Mux(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut(int i) {
		value.push_back((children.at(0)->computeOut(i) && children.back()->computeOut(i)) || (children.at(1)->computeOut(i) && ~(children.back()->computeOut(i))));
		return value[i];
	}
};
