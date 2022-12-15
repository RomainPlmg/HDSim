#include "parser.h"

/*
    ERROR CODES :
        1 -> Syntax error
        2 -> Missing bracket
        3 -> Declaration
*/

int wavedrom_parser(list<string> &waveFile)
{
    list<string>::iterator it = waveFile.begin();

    if(wave_header(it)) 
    {
        cout << "ERROR: Incorrect start of wavedrom file" << endl;
        return wave_header(it);
    }

    while (it != waveFile.end())
    {
        if (*it == "{") it++;
        if (*it == "name")
        {
            it++;
            if (*it != ":") return 1;
            it++;
            if (*it != "\'") return 1;
            it++;
            if (!isItName(it)) return 1;
            if (find(nodesName.begin(), nodesName.end(), *it) != nodesName.end())
            {
                cout << "ERROR: Multiple definition of node \"" << *it << "\"" << endl;
                return 1;
            }
            string signalName = *it;
            nodesName.push_back(signalName);
            it++;
            if (*it != "\'") return 1;
            it++;
            if (*it != "}")
            {
                if (*it != ",") return 1;
                it++;
                if (*it != "wave") return 1;
                it++;
                if (*it != ":") return 1;
                it++;
                if (*it != "\'") return 1;
                it++;
                if (signal_parser(signalName, *it)) return 3;
                it++;
                if (*it != "\'") return 1;
                it++;
            }
            else
            {
                cout << "ERROR: You need to declare a bit stream for the input \"" << signalName << "\"" << endl;
                return 1;
            }
        }
            if (*it != "}") return 2;
            it++;
            while (*it == ",") it++;
            if (*it == "]") break;
            else if (*it != "{") return 2;
    }
    it++;
    if (*it != "}") return 2;
    return 0;
}


int dot_parser(list<string> &dotFile)
{
    bool isVariable;
    list<string>::iterator it = dotFile.begin();
    int offset = nodesName.size();

    // DEBUG
    int check = 0;

    // Check the header of the dot file
    if(dot_header(it)) return dot_header(it);

    while (it != dotFile.end())
    {
        if (isItName(it))
        {
            it++;
            if (*it == "[") // If this is a declaration
            {
                // Store node's name into the list
                it--;
                if (find(nodesName.begin() + offset, nodesName.end(), *it) != nodesName.end())
                {
                    cout << "ERROR: Multiple definition of node \"" << *it << "\"" << endl;
                    return 1;
                }
                nodesName.push_back(*it);
                advance(it, 2);
                if (*it != "label") return 4;
                it++;
                if (*it != "=") return 5;
                it++;
                if (*it != "\"") return 6;
                it++;

                // Store node's type into the list
                switch (resolveStructure(*it))
                {
                case S_Input:
                    nodesName.pop_back();
                    break;
                case S_Output:
                    v_node.push_back(new Output(nodesName.back()));
                    outputSignals.push_back(v_node.back());
                    break;
                case S_And:
                    v_node.push_back(new And(nodesName.back()));
                    break;
                case S_Or:
                    v_node.push_back(new Or(nodesName.back()));
                    break;
                case S_Xor:
                    v_node.push_back(new Xor(nodesName.back()));
                    break;
                case S_Not:
                    v_node.push_back(new Not(nodesName.back()));
                    break;
                case S_Nand:
                    v_node.push_back(new Nand(nodesName.back()));
                    break;
                case S_Nor:
                    v_node.push_back(new Nor(nodesName.back()));
                    break;
                case S_Xnor:
                    v_node.push_back(new Xnor(nodesName.back()));
                    break;
                case S_Mux:
                    v_node.push_back(new Mux(nodesName.back()));
                    break;
                case S_FF:
                    v_node.push_back(new FlipFlop(nodesName.back()));
                    break;
                default:
                    cout << "ERROR: Unknown label \"" << *it << "\"" << endl;
                    return 7;
                    break;
                }
                it++;
                if (*it != "\"") return 1;
                it++;
                if (*it != "]") return 2;
                it++;
                if (*it == ";") it++;
            }
            else if (*it == "->")
            {
                linkChild(it);
            }
            if (*it == "}") it++;
        }
    }
    return 0;
}


int wave_header(list<string>::iterator &it)
{
    // Header
    if (*it != "{") return 1;
    it++;
    if (*it != "signal") return 1;
    it++;
    if (*it != ":") return 1;
    it++;
    if (*it != "[") return 2;
    it++;
    return 0;
}


int dot_header(list<string>::iterator &it)
{
    bool isName;
    if (*it != "digraph") return 1;
    it++;
    if (*it != "{")
    {
        for (int i = 0; i < (*it).length(); i++)
        {
            // If each element is alpha, digit or _ (underscore)
            if (isalpha((*it).at(i)) || isdigit((*it).at(i)) || (*it).at(i) == '_') { isName = true; it++; }
            else { isName = false; break; }
        }
        if (!isName)
        {
            cout << "ERROR: Digraph name is in the wrong format" << endl;
            return 1;
        }
    }
    if (*it != "{") return 2;
    it++;
    return 0;
}


int signal_parser(string &name, string &signal) {
    for (int i = 0; i < signal.length(); i++)
    {
        if (signal[i] == '.' && i == 0)
        {
            cout << "ERROR: Bit stream \"" << name << "\" can't start with a \".\"" << endl;
            return 1;
        }
        else if (signal[i] == '.') signal[i] = signal[i-1];
    }

    if (find(nodesName.begin(), nodesName.end(), name) != nodesName.end())
    {
        v_node.push_back(new Input(name, signal));
        inputSignals.push_back(v_node.back());
        return 0;
    }
    return 1;
}


Structure resolveStructure(string str)
{
    if (str == "OUTPUT")    return S_Output;
    if (str == "INPUT")     return S_Input;
    if (str == "AND2")      return S_And;
    if (str == "OR2")       return S_Or;
    if (str == "XOR2")      return S_Xor;
    if (str == "NOT")       return S_Not;
    if (str == "NAND2")     return S_Nand;
    if (str == "NOR2")      return S_Nor;
    if (str == "XNOR2")     return S_Xnor;
    if (str == "MUX")       return S_Mux;
    if (str == "FF")        return S_FF;
    else                    return MISSING;
}


int getIndex(vector<string> l, string str)
{
    auto it = find(l.begin(), l.end(), str);
    if (it != l.end()) return it - l.begin();
    else return -1;
}


bool isItName(list<string>::iterator &it)
{
    for (int i = 0; i < (*it).length(); i++)
    {
        // If each element is alpha, digit or _ (underscore)
        if (isalpha((*it).at(i)) || isdigit((*it).at(i)) || (*it).at(i) == '_') return true;
    }
    return false;
}


int linkChild(list<string>::iterator &it)
{
    // it start at the symbol "->"
    it++; // it is now a node
    auto n = find(nodesName.begin(), nodesName.end(), *it);
    if (n == nodesName.end()) // If the node has not been created before
    {
        cout << "ERROR: Node \"" << *it << "\" has not been declared before" << endl;
        return 3;
    }
    else // If the node has been created before
    {
        int nodePos = getIndex(nodesName, *it); // Get the relative index of the node
        // DEBUG
        cout << "Node is: " << v_node[nodePos]->getName() << endl;
        advance(it, -2);

        int childPos = getIndex(nodesName, *it); // Get the relative index of the associated child
        v_node[nodePos]->addChild(v_node[childPos]); // Link the child to his parent
        // DEBUG
        cout << "Child is: " << v_node[childPos]->getName() << endl;
        advance(it, 3);
        if (*it == ";") it++;
        else it--;
    }
    return 0;
}