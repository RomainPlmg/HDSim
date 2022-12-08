#include "parser.h"

int wavedrom_parser(list<string> &waveFile)
{
    list<string>::iterator it;

    // Header
    it = waveFile.begin();
    if (*it != "{") {return 1; }
    waveFile.pop_back();
    if (*it != "signal") {return 1; }
    waveFile.pop_back();
    if (*it != ":") {return 1; }
    waveFile.pop_back();
    if (*it != "[") {return 1; }
    waveFile.pop_back();

    if (*it == "{")
    {
        
    }
    


    return 0;
}

int signal_parser(list<string> &waveFile, vector<bool> &signal) {
    
}