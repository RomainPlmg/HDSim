#include "lexer.h"

string wavedrom_dict[WAVEDROM_DICT_SIZE] = {"{", "}", "[", "]", ":", ",", "'", "."};
string dot_dict[DOT_DICT_SIZE] = {"{", "}", "[", "]", "\"", "=", "->", "<-", ";"};

int read_file(fstream &fp, string extension, list<string> &lexFile)
{
    if (!fp.is_open())
    {
        cout << "Error:File cannot be opened for reading";
        return 1;
    }

    string group;
    int horizontale_pos = 1, vertical_pos = 1;
    fp >> ws; // Remove leading white spaces
    for (int i = 0; !fp.eof(); i++) // Browse the file
    {
        group = get_element(fp, extension, i);

        if (group == "ERROR")
        {
            cout << "ERROR:Incorrect syntax at line " << vertical_pos << ",position [" << horizontale_pos << "]" << endl;
            return 1;
        }
        else if (!group.empty())
        {
            if (group == " ") { horizontale_pos++; }
            else if (group == "\n") {
                vertical_pos++; 
                horizontale_pos = 1;
            }
            else { 
                lexFile.push_back(group);
                horizontale_pos += group.length();
            }
        }
    }
    return 0;
}

string get_element(fstream &fp, string extension, int &it)
{
    fp.seekg(it); // Place the pointer to "it" position
    string word;
    char element = fp.peek();

    if (element == '\r' || element == '\n') { return "\n"; }
    else if (element == ' ') { return " "; }
    else if (element < 0) { return ""; }
    else if (isalpha(element) || isdigit(element) || element == '_')
    {
        while (isalpha(element) || isdigit(element) || element == '_')
        {
            word.push_back(element); // Convert char to string

            it++;
            fp.seekg(it);
            element = fp.peek();
        }
        it--;
        return word;
    }
    else
    {
        word.push_back(element); // Convert char to string
        if (extension == "json")
        {
            for (int i = 0; i < WAVEDROM_DICT_SIZE; i++)
            {
                if (word == wavedrom_dict[i])
                {
                    return word;
                }
            }
        } else if (extension == "dot") {
            if (word == "-")
            {
                it++;
                fp.seekg(it);
                element = fp.peek();
                word.push_back(element);
            }
            
            for (int i = 0; i < DOT_DICT_SIZE; i++)
            {
                if (word == dot_dict[i])
                {
                    return word;
                }
            }
        }
        return "ERROR";
    }
}