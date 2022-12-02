#include "lexer.h"

void show_list(list<string>& li);

int main(int argc, char const *argv[]) {
    fstream fp ("./res/Inputs.json");

    list<string> lexList;

    int err = read_file(fp, lexList);
    show_list(lexList);
    return 0;
}

void show_list(list<string>& li) {
    list<string>::iterator ptr;
    for (ptr = li.begin(); ptr != li.end(); ptr++) {
        cout << *ptr << endl;
    }
}