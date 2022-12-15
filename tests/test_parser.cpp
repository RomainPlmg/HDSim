#include "lexer.h"
#include "parser.h"

void show_list(list<string> &li);

int main(int argc, char const *argv[])
{
    string waveFilePath = "./res/Inputs.json";
    string dotFilePath = "./res/and_xor.dot";
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