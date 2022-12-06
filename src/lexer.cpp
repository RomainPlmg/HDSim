#include "lexer.h"

int read_file(fstream& fp, list<string> &lexFile) {
    if(!fp.is_open()) {
        cout << "Error:File cannot be opened for reading";
        return 1;
    }

    string group;
    fp >> ws; // Remove leading white spaces
    for (int i = 0;!fp.eof(); i++) {
        group = get_wavedrom_element(fp, i);
        if (!group.empty()) {
            lexFile.push_back(group);
        }
    }
    return 0;
}

string get_wavedrom_element(fstream& fp, int& it) {
    fp.seekg(it); // Place the pointer to "it" position
    string word;
    char element = fp.peek();

    if (element == ' ' || element == '\n' || element < 0) { return ""; }

    if (isalpha(element) || isdigit(element) || element == '.') {
        while(isalpha(element) || isdigit(element) || element == '.') {
            word.push_back(element);

            it++;
            fp.seekg(it);
            element = fp.peek();
        }
        it--;
        return word;
    } else {
        word.push_back(element); // Convert char to string
        return word;
    }
}