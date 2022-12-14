#ifndef __PARSER_H_
#define __PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "defs.h"

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
    MISSING,
};

int wavedrom_parser(list<string> &waveFile);
int signal_parser(list<string> &waveFile, vector<bool> &signal, vector<string> &nodesName);
int dot_parser(list<string> &dotFile, vector<string> &nodesName);
Structure resolveStructure(string input);
int getIndex(vector<string> l, string str);

#endif