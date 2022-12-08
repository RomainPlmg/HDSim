#include "lexer.h"
#include "parser.h"

void show_list(list<string> &li);

int main(int argc, char const *argv[])
{
    string filePath = "./res/Inputs.json";
    string extension = "json";
    fstream fp (filePath);

    list<string> lexList;

    int lexErr = read_file(fp, extension, lexList);
    int parseErr = wavedrom_parser(lexList);
    show_list(lexList);

    cout << "lexErr = " << lexErr << endl;
    cout << "parseErr = " << parseErr << endl;
    return 0;
}

void show_list(list<string> &li)
{
    list<string>::iterator ptr;
    for (ptr = li.begin(); ptr != li.end(); ptr++)
    {
        cout << *ptr << endl;
    }
}