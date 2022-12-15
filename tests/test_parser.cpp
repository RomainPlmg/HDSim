#include "lexer.h"
#include "parser.h"

void show_list(list<string> &li);

int main(int argc, char const *argv[])
{
    string filePath = "./res/and_xor.dot";
    string extension = "dot";
    fstream fp (filePath);

    list<string> lexList;

    // Call lexer
    int lexErr = read_file(fp, extension, lexList);
    if (lexErr)
    {
        cout << "lex error code: " << lexErr << endl;
        return 1;
    }
    show_list(lexList);

    vector<string> nodesName;
    // Call parser
    int parseErr = dot_parser(lexList, nodesName);
    if (parseErr)
    {
        cout << "parse error code: " << parseErr << endl;
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