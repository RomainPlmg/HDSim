#include "vectors.h"
#include "lexer.h"
#include "parser.h"
#include "simulator.h"

vector<Node*> v_node;
vector<string> nodesName;
vector<Node*> inputSignals;
vector<Node*> outputSignals;

void show_list(list<string> &li);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "ERROR: Incorrect number of argument \n" << endl;
        cout << "./HDSim <pathOfWavedromFile> <pathOfDotFile>" << endl;
        return 1;
    }

    string waveFilePath = argv[1];
    string dotFilePath = argv[2];
    fstream waveFile (waveFilePath);
    fstream dotFile (dotFilePath);

    list<string> wavelexList;
    list<string> dotlexList;

    // Call lexer
    int wavelexErr = read_file(waveFile, "json", wavelexList);
    if (wavelexErr)
    {
        cout << "wave lex error code: " << wavelexErr << endl;
        return 1;
    }

    int dotlexErr = read_file(dotFile, "dot", dotlexList);
    if (dotlexErr)
    {
        cout << "dot lex error code: " << dotlexErr << endl;
        return 1;
    }

    // Call parser
    int parseErr = wavedrom_parser(wavelexList);
    if (parseErr)
    {
        cout << "wavedrom parse error code: " << parseErr << endl;
        return 1;
    }
    parseErr = dot_parser(dotlexList);
    if (parseErr)
    {
        cout << "dot parse error code: " << parseErr << endl;
        return 1;
    }

    // Call simulator
    int simErr = simulate();
}

void show_list(list<string> &li)
{
    list<string>::iterator ptr;
    for (ptr = li.begin(); ptr != li.end(); ptr++)
    {
        cout << *ptr << endl;
    }
    cout << "\n" <<endl;
}