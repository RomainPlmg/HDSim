#ifndef __LEXER_H_
#define __LEXER_H_

#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

int read_file(fstream& fp, list<string> &lexFile);
string get_wavedrom_element(fstream& fp, int& it);

#endif