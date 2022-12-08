#ifndef __LEXER_H_
#define __LEXER_H_

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#define WAVEDROM_DICT_SIZE 8
#define DOT_DICT_SIZE 9

using namespace std;

int read_file(fstream &fp, string extension, list<string> &lexFile);
string get_element(fstream &fp, string extension, int &it);

#endif