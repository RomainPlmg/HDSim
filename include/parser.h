#ifndef __PARSER_H_
#define __PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int wavedrom_parser(list<string> &waveFile);
int signal_parser(list<string> &waveFile, vector<bool> &signal);
int dot_parser(list<string> &dotFile);

#endif