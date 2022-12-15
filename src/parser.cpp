#include "parser.h"

int wavedrom_parser(list<string> &waveFile)
{
    list<string>::iterator it;

    // Header
    it = waveFile.begin();
    if (*it != "{") {return 1; }
    waveFile.pop_back();
    if (*it != "signal") {return 1; }
    waveFile.pop_back();
    if (*it != ":") {return 1; }
    waveFile.pop_back();
    if (*it != "[") {return 1; }
    waveFile.pop_back();

    if (*it == "{")
    {
        
    }



    return 0;
}

int signal_parser(list<string> &waveFile, dynamic_bitset<> &signal) {
    return 0;
}

int dot_parser(list<string> &dotFile, vector<string> &nodesName)
{
    bool isVariable;
    list<string>::iterator it;
    vector<Node*> v_node;

    // Header
    it = dotFile.begin();
    if (*it != "digraph") return 1;
    it++;

    if (*it != "{")
    {
        for (int i = 0; i < (*it).length(); i++)
        {
            // If each element is alpha, digit or _ (underscore)
            if (isalpha((*it).at(i)) || isdigit((*it).at(i)) || (*it).at(i) == '_') { isVariable = true; it++; }
            else { isVariable = false; break; }
        }
        if (!isVariable)
        {
            cout << "ERROR: Digraph name is in the wrong format" << endl;
            return 2;
        }
    }

    if (*it != "{") return 3;
    it++;

    int check = 0;
    while (it != dotFile.end())
    {
        // Name detection
        for (int i = 0; i < (*it).length(); i++)
        {
            // If each element is alpha, digit or _ (underscore)
            if (isalpha((*it).at(i)) || isdigit((*it).at(i)) || (*it).at(i) == '_') isVariable = true;
            else
            {
                isVariable = false;
                break;
            }
        }

        // Nodes declaration
        if (isVariable)
        {
            it++;
            if (*it == "[")
            {
                // Store node's name into the list
                it--;
                nodesName.push_back(*it);
                it++;

                it++;
                if (*it != "label") return 4;
                it++;
                if (*it != "=") return 5;
                it++;
                if (*it != "\"") return 6;
                it++;

                // Store node's type into the list
                switch (resolveStructure(*it))
                {
                case S_Output:
                    v_node.push_back(new Output(nodesName.back()));
                    break;
                case S_And:
                    v_node.push_back(new And(nodesName.back()));
                    break;
                case S_Xor:
                    v_node.push_back(new Xor(nodesName.back()));
                    break;
                case S_Input:
                    if(!check) { v_node.push_back(new Input(nodesName.back(), "011011100")); check++; }
                    else if(check == 1) { v_node.push_back(new Input(nodesName.back(), "110111111")); check++; }
                    else v_node.push_back(new Input(nodesName.back(), "110000111"));

                    // *************************** DEBUG *************************** //
                    cout << "Input " << nodesName.back() << " : wave \"";
                    for (int i = 0; i < v_node.back()->getSize(); i++)
                    {
                        cout << v_node.back()->getValue(i);
                    }
                    cout << "\"" << endl;
                    
                    break;
                default:
                    cout << "ERROR: Unknown label \"" << *it << "\"" << endl;
                    return 7;
                    break;
                }

                it++;
                if (*it != "\"") return 8;
                it++;
                if (*it != "]") return 9;
                it++;
                if (*it == ";") it++;
            }
            else if (*it == "->")
            {
                it++;
                auto n = find(nodesName.begin(), nodesName.end(), *it);
                if (n == nodesName.end()) // If the node *it has not been created before
                {
                    cout << "ERROR: Node \"" << *it << "\" has not been declared before" << endl;
                    return 10;
                }
                else // If the node *it has been created before
                {
                    int nodePos = getIndex(nodesName, *it);
                    cout << "Node is: " << v_node[nodePos]->getName() << endl;
                    it --;
                    it--;
                    int childPos = getIndex(nodesName, *it);
                    v_node[nodePos]->addChild(v_node[childPos]);
                    cout << "Child is: " << v_node[childPos]->getName() << endl;
                    it++;
                    it++; // Return to the actual node
                    it++;
                    if (*it == ";") it++;
                    else it--;
                }
            }
            if (*it == "}") it++;
        }
    }
    cout << v_node[5]->getName() << endl;
    cout << v_node[0]->getSize() << endl;
    for(int i = 0; i < v_node[0]->getSize(); i++) {
		v_node[5]->computeOut(i);
		cout << "out = " << v_node[5]->getValue(i) << endl;
	}
    return 0;
}


Structure resolveStructure(string str)
{
    if (str == "OUTPUT")    return S_Output;
    if (str == "INPUT")     return S_Input;
    if (str == "AND2")      return S_And;
    if (str == "XOR2")      return S_Xor;
    else                    return MISSING;
}


int getIndex(vector<string> l, string str)
{
    auto it = find(l.begin(), l.end(), str);
    if (it != l.end()) return it - l.begin();
    else return -1;
}