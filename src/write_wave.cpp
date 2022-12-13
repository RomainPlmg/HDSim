#include "write_wave.h"

string BoolToString(Node* &N) {

    string boolString = N->getValue();
    string output;

    if(boolString.front() == '0')
        output.push_back('0');
    else
        output.push_back('1');

    for(size_t i = 1; i < boolString.size(); i++) {
        if(boolString[i] == boolString[i-1])
            output.push_back('.');
        else if(boolString[i] == '0')
            output.push_back('0');
        else
            output.push_back('1');
    }

    return output;
}

int create_file(vector<Node*> &signals) {

    ofstream fp("Results.json");
    if (!fp.is_open())
    {
        cout << "Error:File cannot be written";
        return 1;
    }

    fp << "{signal: [" << endl;
    for(size_t i = 0; i < signals.size(); i++) {
        fp << "  {name: '" << signals[i]->getName() << "', wave: '" << BoolToString(signals[i]) << "'}," << endl;
    }
    fp << "]}" << endl;

    return 0;
}