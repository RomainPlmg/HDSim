#include <algorithm>
#include "defs.h"

bool Node::detectCycle() {

    vector<Node*> visited;
    vector<Node*> recStack;
    visited.push_back(this);
    recStack.push_back(this);
    for(size_t i = 0; i < children.size(); i++) {
        if(!(find(visited.begin(), visited.end(), children[i]) != visited.end()) && children[i]->utilCycle(visited, recStack))
            return true;
    }

    return false;
}

bool Node::utilCycle(vector<Node*> &visited, vector<Node*> &recStack) {

    vector<Node*>::iterator it = find(visited.begin(), visited.end(), this);
    if(it == visited.end()) {

        visited.push_back(this);
        recStack.push_back(this);

        for(size_t i = 0; i < children.size(); i++) {
            if(!(find(visited.begin(), visited.end(), children[i]) != visited.end()) && children[i]->utilCycle(visited, recStack))
                return true;
            else if(find(recStack.begin(), recStack.end(), children[i]) != recStack.end())
                return true;
        }
    }
    recStack.erase(find(recStack.begin(), recStack.end(), this));
    return false;
}