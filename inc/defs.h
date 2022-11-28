#include <iostream>
#include <vector>

using namespace std;

struct Node {
protected:
	vector<Node*> children;
	vector<bool> values;
public:
	Node(vector<Node*> _children = {}) : children(_children) {}
	Node(vector<bool> _values = {}) : values(_values) {}
	virtual bool computeOut() = 0;

	bool getValue() { return values.back(); }
	void setValue(bool value) { values.push_back(value); }
};

struct Output : public Node {

	Output(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(children.back()->computeOut());
		return values.back();
	}
};

struct Input : public Node {

	Input(vector<bool> _values = {}) : Node(_values) {}

	bool computeOut() {
		return this->getValue();
	}
};

struct And : public Node {

	And(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(children.front()->computeOut() && children.back()->computeOut());
		return values.back();
	}
};

struct Or : public Node {

	Or(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(children.front()->computeOut() || children.back()->computeOut());
		return values.back();
	}
};

struct Xor : public Node {

	Xor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(children.front()->computeOut() ^ children.back()->computeOut());
		return values.back();
	}
};

struct Not : public Node {

	Not(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(~(children.front()->computeOut()));
		return values.back();
	}
};

struct Nand : public Node {

	Nand(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(~(children.front()->computeOut() && children.back()->computeOut()));
		return values.back();
	}
};

struct Nor : public Node {

	Nor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(~(children.front()->computeOut() || children.back()->computeOut()));
		return values.back();
	}
};

struct Xnor : public Node {

	Xnor(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back(~(children.front()->computeOut() ^ children.back()->computeOut()));
		return values.back();
	}
};

struct Mux : public Node {

	Mux(vector<Node*> _children = {}) : Node(_children) {}

	bool computeOut() {
		values.push_back((children.at(0)->computeOut() && children.back()->computeOut()) || (children.at(1)->computeOut() && ~(children.back()->computeOut())));
		return values.back();
	}
};
