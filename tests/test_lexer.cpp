#include "lexer.h"

void show_list(list<string> &li);

int main(int argc, char const *argv[])
{
    string filePath = "./res/Inputs.json";
    string extension = "json";
    fstream fp (filePath);

    list<string> lexList;

    int err = read_file(fp, extension, lexList);
    if (err == 0)
    {
        show_list(lexList);
    }
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