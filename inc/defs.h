#include <iostream>
#include <vector>

using namespace std;

struct Node {
	vector<Node*> children;
	vector<bool> values;

	Node(vector<Node*> _children = {}) : children(_children) {}
	Node(vector<bool> _values = {}) : values(_values) {}
	virtual bool computeOut() = 0;

	bool getValue() { return values.back(); }
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