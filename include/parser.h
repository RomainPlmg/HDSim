#ifndef __PARSER_H_
#define __PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "vectors.h"

#define NODES_DICT_SIZE 10

using namespace std;

enum Structure {
    S_Output,
    S_Input,
    S_And,
    S_Or,
    S_Xor,
    S_Not,
    S_Nand,
    S_Nor,
    S_Xnor,
    S_Mux,
    S_FF,
    MISSING,
};

int wavedrom_parser(list<string> &waveFile);
int signal_parser(string &name, string &signal);
int dot_parser(list<string> &dotFile);
int dot_header(list<string>::iterator &it);
int wave_header(list<string>::iterator &it);
int getIndex(vector<string> l, string str);
int linkChild(list<string>::iterator &it);
bool isItName(list<string>::iterator &it);
Structure resolveStructure(string str);

#endif